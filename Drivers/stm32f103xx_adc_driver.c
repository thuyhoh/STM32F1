#include "stm32f103xx_adc_driver.h"

static uint8_t ADC_GetFlag(ADC_RegDef_t *pADCx, uint8_t ADC_Flagname)
{
	if(pADCx->SR & ADC_Flagname) return FLAG_SET;
	return FLAG_RESET;
}



void ADC_PinConfig(uint8_t ADC_INx)
{
	GPIO_Handle_t GPIOHandle;
	if(ADC_INx >= ADC_IN0 && ADC_INx <= ADC_IN7)
	{
		GPIOHandle.pGPIOx = GPIOA_BASEPTR;
		GPIOHandle.GPIO_Config.GPIO_PinNumber = ADC_INx;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_INPUT_ANALOG_MODE;
	}else if(ADC_INx >= ADC_IN8 && ADC_INx <= ADC_IN9)
	{
		GPIOHandle.pGPIOx = GPIOB_BASEPTR;
		GPIOHandle.GPIO_Config.GPIO_PinNumber = ADC_INx - 8;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_INPUT_ANALOG_MODE;
	}
	else if(ADC_INx >= ADC_IN10 && ADC_INx <= ADC_IN16)
	{
		GPIOHandle.pGPIOx = GPIOA_BASEPTR;
		GPIOHandle.GPIO_Config.GPIO_PinNumber = ADC_INx - 10;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_INPUT_ANALOG_MODE;
	}else
	{
		// error
	}
	GPIO_Init(&GPIOHandle);
}


void ADC_PeriClockControl(ADC_RegDef_t *pADCx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		if(pADCx == ADC1_BASEPTR)
		{
			ADC1_PCLK_ENABLE();
		}
		else if(pADCx == ADC2_BASEPTR)
		{
			ADC2_PCLK_ENABLE();
		}else
		{ /* error */ }
	}else
	{
		if(pADCx == ADC1_BASEPTR)
		{
			ADC1_PCLK_ENABLE();
		}
		else if(pADCx == ADC2_BASEPTR)
		{
			ADC2_PCLK_ENABLE();
		}else
		{ /* error */ }
	}
}

//
void ADC_Init(ADC_Handle_t *pADCHandle)
{
	
}

void ADC_PeripheralControl(ADC_RegDef_t *pADCx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		pADCx->CR2 |= (1 << ADC_CR2_ADON);
		SysTick_Delayus(1);
		pADCx->CR2 |= (1 << ADC_CR2_ADON);
	}else
	{
		pADCx->CR2 &= (uint32_t)~(1 << ADC_CR2_ADON);
		SysTick_Delayus(1);
		pADCx->CR2 &= (uint32_t)~(1 << ADC_CR2_ADON);
	}
}


void ADC_IRQConfig(ADC_RegDef_t *pADCx , uint8_t Priority, uint8_t ENorDI)
{
	
}





void ADC_IRQHandle(ADC_Handle_t *pADCHandle)
{

}

