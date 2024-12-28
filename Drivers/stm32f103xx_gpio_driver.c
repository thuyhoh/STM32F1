#include "stm32f103xx_gpio_driver.h"

/****************************************************************************
 * @fn	  				-  GPIO_PeriClockControl

 * @brief  				-  GPIO Peripheral Clock setup 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIO, uint8_t EnorDis)
{
	if(EnorDis == ENABLE)
	{
		if(pGPIO == GPIOA_BASEPTR)
		{
			GPIOA_PCLK_ENABLE();
		}else if(pGPIO == GPIOB_BASEPTR)
		{
			GPIOB_PCLK_ENABLE();
		}else if(pGPIO == GPIOC_BASEPTR)
		{
			GPIOC_PCLK_ENABLE();
		}else 
		{
			// error
		}
	}else
	{
		if(pGPIO == GPIOA_BASEPTR)
		{
			GPIOA_PCLK_DISABLE();
		}else if(pGPIO == GPIOB_BASEPTR)
		{
			GPIOB_PCLK_DISABLE();
		}else if(pGPIO == GPIOC_BASEPTR)
		{
			GPIOC_PCLK_DISABLE();
		}else
		{
			// error
		}
	}
}

/****************************************************************************
 * @fn	  				-			GPIO_Init

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIO_Handle)
{
	GPIO_PeriClockControl(pGPIO_Handle->pGPIOx,ENABLE);
	 
	if(pGPIO_Handle->GPIO_Config.GPIO_PinMode <= GPIO_OUTPUT_50MHZ_AF_OD_MODE) // Base mode
	{
		uint8_t tmp1 = pGPIO_Handle->GPIO_Config.GPIO_PinNumber / 8;
		uint8_t tmp2 = pGPIO_Handle->GPIO_Config.GPIO_PinNumber % 8;
		uint32_t tmp = (uint32_t)(pGPIO_Handle->GPIO_Config.GPIO_PinMode << (tmp2*4));
		pGPIO_Handle->pGPIOx->CR[tmp1] |= tmp;
	}else		// IRQ mode
	{
		/* 1. Configure Pin -> Input Mode */
		GPIO_Handle_t tmp;
		tmp.GPIO_Config.GPIO_PinNumber = pGPIO_Handle->GPIO_Config.GPIO_PinNumber;
		tmp.GPIO_Config.GPIO_PinMode   = GPIO_INPUT_PU_PD;
		tmp.pGPIOx				          = pGPIO_Handle->pGPIOx;
		GPIO_Init(&tmp);
		
		/* 2. AFIO clock enable */
		AFIO_PCLK_ENABLE();
		
		/* 3. Configure the GPIO port select in AFIO_EXTICR */
		// find position of the EXTICR[]
		uint8_t AFIO_EXTICR_offset  = pGPIO_Handle->GPIO_Config.GPIO_PinNumber / 4;
		uint8_t AFIO_EXTICR_section = pGPIO_Handle->GPIO_Config.GPIO_PinMode % 4;
		
		uint8_t PortCode = GPIO_BASEADDR_TO_CODE(pGPIO_Handle->pGPIOx);
		
		AFIO_BASEPTR->EXTICR[AFIO_EXTICR_offset] |=  (uint32_t)(PortCode<<(AFIO_EXTICR_section * 8));
		
		/* 4. Configure the trigger edge selection  of EXTI_FTSR EXTI_RTSR*/  
		if(pGPIO_Handle->GPIO_Config.GPIO_PinMode == GPIO_IT_FT_MODE) /* Falling trigger */
		{		/* Falling trigger */
			// Configure EXTI_FTSR
			EXTI_BASEPTR->FTSR |= (1<<pGPIO_Handle->GPIO_Config.GPIO_PinNumber);
			EXTI_BASEPTR->RTSR &= (uint32_t)~(1<<pGPIO_Handle->GPIO_Config.GPIO_PinNumber);
		}
		else if(pGPIO_Handle->GPIO_Config.GPIO_PinMode == GPIO_IT_RT_MODE) 
		{		/* Rising trigger */
			// Configure EXTI_RTSR
			EXTI_BASEPTR->FTSR &= (uint32_t)~(1<<pGPIO_Handle->GPIO_Config.GPIO_PinNumber);
			EXTI_BASEPTR->RTSR |= (1<<pGPIO_Handle->GPIO_Config.GPIO_PinNumber);
		}
		else	
		{		/* Falling and Rising trigger */
			// Configure EXTI_FTSR and EXTI_RTSR
			EXTI_BASEPTR->FTSR |= (1<<pGPIO_Handle->GPIO_Config.GPIO_PinNumber);
			EXTI_BASEPTR->RTSR |= (1<<pGPIO_Handle->GPIO_Config.GPIO_PinNumber);
		}
		
		/* 5.  Configure the mask bits of EXTI_IMR */
		EXTI_BASEPTR->IMR |= (1<<pGPIO_Handle->GPIO_Config.GPIO_PinNumber);
	}
}

void GPIO_DigitalInput(GPIO_RegDef_t *pGPIO, uint8_t PinNumber)
{
	GPIO_Handle_t tmp;
	tmp.GPIO_Config.GPIO_PinNumber = PinNumber;
	tmp.GPIO_Config.GPIO_PinMode   = GPIO_INPUT_PU_PD;
	tmp.pGPIOx				          = pGPIO;
	GPIO_Init(&tmp);
}


void GPIO_DigitalOutput(GPIO_RegDef_t *pGPIO, uint8_t PinNumber)
{
	GPIO_Handle_t tmp;
	tmp.GPIO_Config.GPIO_PinNumber = PinNumber;
	tmp.GPIO_Config.GPIO_PinMode   = GPIO_OUTPUT_50MHZ_GP_PP_MODE;
	tmp.pGPIOx				          = pGPIO;
	GPIO_Init(&tmp);
}

/****************************************************************************
 * @fn	  				- 			GPIO_DeInit

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIO)
{
	if(pGPIO == GPIOA_BASEPTR)
	{
		GPIOA_REG_RESET();
	}else if(pGPIO == GPIOB_BASEPTR)
	{
		GPIOB_REG_RESET();
	}else if(pGPIO == GPIOC_BASEPTR)
	{
		GPIOC_REG_RESET();
	}
}

/****************************************************************************
 * @fn	  				- 			GPIO_ReadFromInputPin

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber)
{
	_vo uint8_t PinState = (uint8_t)(pGPIO->IDR >> PinNumber)&0x1;
	return PinState;
}

/****************************************************************************
 * @fn	  				- 		GPIO_ReadFromInputPort

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/	
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIO)
{
	_vo uint16_t PortState = (uint16_t)pGPIO->IDR;
	return PortState;
}

/****************************************************************************
 * @fn	  				- 			GPIO_WriteToOutputPin

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/	
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber, uint8_t PinState)
{
	if(PinState == SET)
	{
		pGPIO->ODR |= 1<<PinNumber;
	}else
	{
		pGPIO->ODR &= (uint32_t)~(1<<PinNumber);
	}
}

/****************************************************************************
 * @fn	  				- 			GPIO_WriteToOutputPort

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/	
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIO, uint16_t PortState)
{
	pGPIO->ODR |= PortState;
}

/****************************************************************************
 * @fn	  				- 			GPIO_ToggleOutputPin	

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/	
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber)
{
	pGPIO->ODR ^= (1<<PinNumber);
}

/****************************************************************************
 * @fn	  				- 			GPIO_SetPin

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void GPIO_SetPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber)
{
	GPIO_WriteToOutputPin(pGPIO, PinNumber, GPIO_PIN_SET);
}

/****************************************************************************
 * @fn	  				- 			GPIO_ResetPin

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void GPIO_ResetPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber)
{
	GPIO_WriteToOutputPin(pGPIO, PinNumber, GPIO_PIN_RESET);
}

/****************************************************************************
 * @fn	  				- 					GPIO_IRQConfig

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/	
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t Priority, uint8_t EnorDi)
{
	NVIC_IRQConfig(IRQNumber, EnorDi);
	NVIC_IRQPriorityConfig(IRQNumber, Priority);
}
	
/****************************************************************************
 * @fn	  				- 					GPIO_IRQHandler

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/	
void GPIO_IRQHandler(uint8_t PinNumber)
{
	EXTI_BASEPTR->PR |= (1<<PinNumber);
}
