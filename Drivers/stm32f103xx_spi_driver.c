#include "stm32f103xx_spi_driver.h"

void SPI_Init(SPI_Handle_t *SPI_Handle)
{
	// Enable Clock for SPI
	SPI_PeriClockControl(SPI_Handle->pSPIx, ENABLE);
	
	// Pin Confic
	SPI_PinConfig(SPI_Handle->pSPIx, SPI_Handle->SPI_Config.SPI_Mode);
	uint32_t tmpReg = 0;
	
	// Configure SPI Mode
	tmpReg |= (uint32_t)(SPI_Handle->SPI_Config.SPI_Mode<<2);
	
	// Configure SPI Bus Config
	if(SPI_Handle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		tmpReg &= (uint32_t)~(1<<15);
	}else if(SPI_Handle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		tmpReg |= (uint32_t)(1<<15);
	}else if(SPI_Handle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		tmpReg &= (uint32_t)~(1<<15);
		tmpReg &= (uint32_t)~(1<<14);
	}else
	{
		// errror
	}
	
	tmpReg |= (uint32_t)((SPI_Handle->SPI_Config.SPI_BaudRate 			<< 3)  | 		/**/
											 (SPI_Handle->SPI_Config.SPI_FrameFormat 	<< 7)    |		/*MSB or LSB first*/
											 (SPI_Handle->SPI_Config.SPI_DFF 					<< 11)   |		/**/
											 (SPI_Handle->SPI_Config.SPI_CPOL 					<< 1)  |		/**/
										   (SPI_Handle->SPI_Config.SPI_CPHA  				<< 0 ))  |
											 (SPI_Handle->SPI_Config.SPI_SSM					<< 9)		 ;	  /**/
	
	// restore in SPI_CR1 register
	SPI_Handle->pSPIx->CR1 |= tmpReg;				
}
void SPI_Deinit(SPI_RegDef_t *pSPIx)
{
	// reset SPIx Register
	// Disable Clock for SPI
}



static uint8_t SPI_GetFlag(SPI_RegDef_t *pSPIx,uint32_t SPI_Flag)
{
	if(pSPIx->SR &= SPI_Flag) return FLAG_SET;
	else return FLAG_RESET;
}

/* Transmit data */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len)
{
	while(len)
	{
		while(SPI_GetFlag(pSPIx, SPI_BUSY_FLAG) == FLAG_SET){}
		if(pSPIx->CR1 & (1<<SPI_CR1_DFF))
		{ // DFF 16bits
			pSPIx->DR = *((uint16_t *)pTxBuffer);
			len = len - 2;
			(uint16_t *)pTxBuffer++;
		}else
		{	// DFF 8bits
			pSPIx->DR = *pTxBuffer;
			len = len - 1;
			pTxBuffer++;
		}
	}
}

/* Receive data */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t len)
{
	while(len)
	{
		while(SPI_GetFlag(pSPIx, SPI_RXNE_FLAG) == FLAG_SET);
		if(pSPIx->SR & SPI_CR1_DFF)
		{ // 16bits
			*((uint16_t *)pRxBuffer) = pSPIx->DR;
			len -= 2;
			pRxBuffer++; pRxBuffer++;
		}else
		{ // 8bits
			*pRxBuffer = pSPIx->DR;
			len -= 1;
		}
	}
}

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pBuffer, uint32_t len)
{
	uint8_t State = pSPIHandle->RxState;
	if(State != SPI_BUSY_IN_RX)
	{
		// save data 
		pSPIHandle->pTxBuffer = pBuffer;
		pSPIHandle->Txlen = len;
		pSPIHandle->TxState = SPI_BUSY_IN_TX;
		
		//enable interrupt
		pSPIHandle->pSPIx->CR2 |= (1<< SPI_CR2_TXEIE);
	}	
	return State;
}

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pBuffer, uint32_t len)
{
	uint8_t State = pSPIHandle->TxState;
	if(State != SPI_BUSY_IN_TX)
	{
		// save data 
		pSPIHandle->pRxBuffer = pBuffer;
		pSPIHandle->Rxlen = len;
		pSPIHandle->RxState = SPI_BUSY_IN_RX;
		
		//enable interrupt
		pSPIHandle->pSPIx->CR2 |= (1<< SPI_CR2_TXEIE);
	}	
	return State;	
}


/* IRQ Configure and IRQ handling */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)
{
	NVIC_IRQConfig(IRQNumber, EnorDi);
	NVIC_IRQPriorityConfig(IRQNumber, IRQPriority);
}
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{
	uint32_t temp1, temp2;
	// RXNE
	temp1 = pSPIHandle->pSPIx->SR & (1<< SPI_SR_RXNE);
	temp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE);
	if(temp1 && temp2)
	{
		SPI_RXEIRQ_Handle(pSPIHandle);
	}
	// TXE
	temp1 = pSPIHandle->pSPIx->SR & (1<< SPI_SR_TXE);
	temp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_TXEIE);
	if(temp1 && temp2)
	{
		SPI_TXEIRQ_Handle(pSPIHandle);
	}
	temp1 = pSPIHandle->pSPIx->SR & (1<< SPI_SR_OVR);
	temp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_ERRIE);
	if(temp1 && temp2)
	{
		SPI_OVR_Handle(pSPIHandle);
	}
	temp1 = pSPIHandle->pSPIx->SR & (1<< SPI_SR_MODF);
	if(temp1 && temp2)
	{
		SPI_MODF_Handle(pSPIHandle);
	}
	
}

/*
 * other API
 */

static void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t ENorDi)
{
	if(ENorDi == CLOCK_ENABLE)
	{
		if(pSPIx == SPI1_BASEPTR)
		{
			SPI1_PCLK_ENABLE();
		}else if (pSPIx == SPI2_BASEPTR)
		{
			SPI2_PCLK_ENABLE();
		}else if(pSPIx == SPI3_BASEPTR)
		{
			SPI3_PCLK_ENABLE();
		}else
		{
			// error
		}
	}else
	{
		if(pSPIx == SPI1_BASEPTR)
		{
			SPI1_PCLK_DISABLE();
		}else if (pSPIx == SPI2_BASEPTR)
		{
			SPI2_PCLK_DISABLE();
		}else if(pSPIx == SPI3_BASEPTR)
		{
			SPI3_PCLK_DISABLE();
		}else
		{
			// error
		}
	}
}

/*
											master												slave
	SCK				 Alternate function push-pull					Input floating 
	MOSI			 Alternate function push-pull					Input floating /Input pull-up
	MISO			 Input floating / Input pull-up				Alternate function push-pull
	NSS				 Software, GPIO												Input floating/ Input pull-up / Input pull-down

SPI1
SCK	:	PA5
MISO:	PA6
MOSI:	PA7
NSS	:	PA4

SPI2
SCK	:	PB13
MISO:	PB14
MOSI:	PB15
NSS	:	PB12
*/

_weak void SPI_PinConfig(SPI_RegDef_t *pSPIx, uint8_t SPI_Mode)
{
	GPIO_Handle_t GPIO_Handle;
	// enable AFIO 
	RCC_AFIOControl(ENABLE);
	if(SPI_Mode == SPI_MASTER_MODE)
	{	// Master Mode
		if(pSPIx == SPI2_BASEPTR)
		{
			GPIO_Handle.pGPIOx = GPIOB_BASEPTR;
			GPIOB_PCLK_ENABLE();
			GPIO_Handle.pGPIOx->CR[1] &= (uint32_t)~(0xffff << 16);
			// SCK_Pin
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_13;
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
			GPIO_Init(&GPIO_Handle);
			// MISO_Pin
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_14;
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_INPUT_PU_PD;
			GPIO_Init(&GPIO_Handle);
			// MOSI_Pin
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_15;
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
			GPIO_Init(&GPIO_Handle);
			// NSS_Pin -> HardWare
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_12; 
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_GP_PP_MODE;
			GPIO_Init(&GPIO_Handle);
			GPIO_SetPin(GPIO_Handle.pGPIOx, GPIO_Handle.GPIO_Config.GPIO_PinNumber);
		}
		else if(pSPIx == SPI1_BASEPTR)
		{
			GPIO_Handle.pGPIOx = GPIOA_BASEPTR;
			GPIOA_PCLK_ENABLE();
			GPIO_Handle.pGPIOx->CR[0] &= (uint32_t)~(0xffff << 16);
			// SCK_Pin
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_5;
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
			GPIO_Init(&GPIO_Handle);
			// MISO_Pin
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_6;
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_INPUT_PU_PD;
			GPIO_Init(&GPIO_Handle);
			// MOSI_Pin
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_7;
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
			GPIO_Init(&GPIO_Handle);
			// NSS_Pin -> HardWare
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_4; 
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_GP_PP_MODE;
			GPIO_Init(&GPIO_Handle);
			GPIO_SetPin(GPIO_Handle.pGPIOx, GPIO_Handle.GPIO_Config.GPIO_PinNumber);
		}
		else
		{
			// error
		}
	}else 
	{	// Slave Mode
		// to do
	}
}

void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t ENorDIS)
{
	if(ENorDIS == ENABLE)
	{
		pSPIx->CR1 |= (1<<6);
	}else
	{
		pSPIx->CR1 &= (uint32_t)~(1<<6);
	}
}

void SPI_SSI(SPI_RegDef_t *pSPIx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		pSPIx->CR1 |= (1<<8);
	}else
	{
		pSPIx->CR1&= (uint32_t)~(1<<8);
	}
}

void SPI_SSOE(SPI_RegDef_t *pSPIx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		pSPIx->CR2 |= 1<<2;
	}else
	{
		pSPIx->CR2 &= (uint32_t)~(1<<2);	
	}
}

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= (uint32_t)~(1 << SPI_CR2_TXEIE); 
	pSPIHandle->pTxBuffer = NULL;
	pSPIHandle->Txlen = 0;
	pSPIHandle->TxState = SPI_READY;
}

void SPI_CloseReceiption(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= (uint32_t)~(1 << SPI_CR2_RXNEIE); 
	pSPIHandle->pRxBuffer = NULL;
	pSPIHandle->Rxlen = 0;
	pSPIHandle->RxState = SPI_READY;
}

static void SPI_TXEIRQ_Handle(SPI_Handle_t *pSPIHandle)
{
	if(pSPIHandle->pSPIx->CR1 & (1<< SPI_CR1_DFF))
	{ // 16bit;
		pSPIHandle->pSPIx->DR = *(uint16_t*)(pSPIHandle->pTxBuffer);
		pSPIHandle->pTxBuffer++;
		pSPIHandle->pTxBuffer++;
		pSPIHandle->Txlen -= 2;
	}else
	{ // 8bit
		pSPIHandle->pSPIx->DR = *(pSPIHandle->pTxBuffer);
		pSPIHandle->pTxBuffer++;
		pSPIHandle->Txlen -= 1;
	}
	if(pSPIHandle->Txlen)
	{
		SPI_CloseTransmission(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_TX_CMPLT);
	}
}
static void SPI_RXEIRQ_Handle(SPI_Handle_t *pSPIHandle)
{
	if(pSPIHandle->pSPIx->CR1 & (1<< SPI_CR1_DFF))
	{ // 16bit;
		*(uint16_t*)(pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx->DR;
		pSPIHandle->pRxBuffer++;
		pSPIHandle->pRxBuffer++;
		pSPIHandle->Rxlen -= 2;
	}else
	{ // 8bit
		*(pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx->DR;
		pSPIHandle->pRxBuffer++;
		pSPIHandle->Rxlen -= 1;
	}
	if(pSPIHandle->Rxlen)
	{
		SPI_CloseReceiption(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_CMPLT);
	}
}

static void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
	uint32_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
}

static void SPI_MODF_Handle(SPI_Handle_t *pSPIHandle)
{
	uint32_t temp;
	// MODF bit set by SSI(SW)
	if(pSPIHandle->pSPIx->CR1 & SPI_CR1_SSM)
	{
		// read/write into SR
		temp = pSPIHandle->pSPIx->SR;
		// Write to CR1
		SPI_SSI(pSPIHandle->pSPIx, ENABLE);
	}else
	{// 
		// read/write into SR
		temp = pSPIHandle->pSPIx->SR;
		// ssoe
		SPI_SSOE(pSPIHandle->pSPIx, ENABLE);
	}
	// Mode Master
	pSPIHandle->pSPIx->CR1 |= (1 << SPI_CR1_MSTR);
	// enable  SPI_Peri
	SPI_PeriControl(pSPIHandle->pSPIx, ENABLE);
}

static void SPI_OVR_Handle(SPI_Handle_t *pSPIHandle)
{
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX)
	{
		SPI_ClearOVRFlag(pSPIHandle->pSPIx);
	}
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_OVR_ERR);
}

_weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEv)
{
	
}
