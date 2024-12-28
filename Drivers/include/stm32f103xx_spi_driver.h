#ifndef __STM32F103XX_SPI_DRIVER_H_
#define __STM32F103XX_SPI_DRIVER_H_

#include "stm32f103xx.h"
/* MACROS */


typedef struct
{
	uint8_t SPI_Mode;					/* @SPI_MODE */
	uint8_t SPI_BusConfig;		/* @SPI_BUSCONFIG */
	uint8_t SPI_BaudRate;			/* @SPI_BAUDRATE */
	uint8_t SPI_CPOL;					/* @SPI_CPOL */
	uint8_t SPI_CPHA;					/* @SPI_CPHA */
	uint8_t SPI_FrameFormat;	/* @SPI_Transmit_FrameFormat */
	uint8_t SPI_DFF;					/* @SPI_DFF */
	uint8_t SPI_SSM;					/* @SPI_SSM */
}SPI_Config_t;

typedef struct
{
	uint8_t *pBuffer;
	uint32_t len;
	uint8_t  State;
}Data_Manage_t;

typedef struct
{
	SPI_RegDef_t *pSPIx;
	SPI_Config_t SPI_Config;
	uint8_t *pTxBuffer;
	uint32_t Txlen;
	uint8_t  TxState;
	uint8_t *pRxBuffer;
	uint32_t Rxlen;
	uint8_t  RxState;
}SPI_Handle_t;

/* @SPI_MODE */
#define SPI_SLAVE_MODE				0
#define SPI_MASTER_MODE				1

/* @SPI_BUSCONFIG */
#define SPI_BUS_CONFIG_FD							1
#define SPI_BUS_CONFIG_HD							2
#define SPI_BUS_CONFIG_SD_RXONLY			3

/* @SPI_BAUDRATE */
#define SPI_BAUDRATE_PCLK_DIV2				0
#define SPI_BAUDRATE_PCLK_DIV4				1
#define SPI_BAUDRATE_PCLK_DIV8				2
#define SPI_BAUDRATE_PCLK_DIV16				3
#define SPI_BAUDRATE_PCLK_DIV32				4
#define SPI_BAUDRATE_PCLK_DIV64				5
#define SPI_BAUDRATE_PCLK_DIV128			6
#define SPI_BAUDRATE_PCLK_DIV256			7

/* @SPI_CPOL */
#define SPI_CPOL_HIGH									1
#define SPI_CPOL_LOW									0

/* @SPI_CPHA */
#define SPI_CPHA_FIST_EDGE							1
#define SPI_CPHA_SECOND_EDGE						0

/* @SPI_DFF */
#define SPI_DFF_8BITS									0
#define SPI_DFF_16BITS								1

/* @SPI_Transmit_FrameFormat */
#define SPI_FF_LSBFIRST								0
#define SPI_FF_MSBFIRST								1

/* @SPI_SSM */
#define SPI_SSM_EN								1
#define SPI_SSM_DI								0



#define SPI_SR_BUSY						7
#define SPI_SR_TXE						1
#define SPI_SR_RXE						0

/* @SPI_FLAG */
#define SPI_BUSY_FLAG					(1<<SPI_SR_BUSY)
#define SPI_TXE_FLAG					(1<<SPI_SR_TXE)
#define SPI_RXNE_FLAG					(1<<SPI_SR_RXE)

/* SPI_STATE*/
#define SPI_BUSY_IN_RX			2
#define SPI_BUSY_IN_TX			1
#define SPI_READY						0

/* SPI Application events */
#define SPI_EVENT_TX_CMPLT		1
#define SPI_EVENT_RX_CMPLT		2
#define SPI_EVENT_OVR_ERR			3

/* @SPI_BIT_POSITION */
#define SPI_CR1_DFF						11
#define SPI_CR1_SSM						9
#define SPI_CR1_MSTR					2
#define SPI_CR2_TXEIE				7
#define SPI_CR2_RXNEIE			6
#define SPI_CR2_ERRIE				5
#define SPI_CR2_SSOE				3

#define SPI_SR_RXNE					0	
#define SPI_SR_TXE					1
#define SPI_SR_MODF					5
#define SPI_SR_OVR					6	
#define SPI_SR_CRCERR				4

/********************************************************************************************

********************************************************************************************/

/* Init and De-Init */
void SPI_Init(SPI_Handle_t *SPI_Handle);
void SPI_Deinit(SPI_RegDef_t *pSPI);

/* Transmit data */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pBuffer, uint32_t len);
/* Receive data */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pBuffer, uint32_t len);

/*IRQ fuction*/
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t len);
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t len);


/* IRQ Configure and IRQ handling */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);

/*
 * other API
 */
/* Enable Clock for SPIx */
static void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t ENorDi);

/* Configure Pin for SPI */
_weak void SPI_PinConfig(SPI_RegDef_t *pSPIx, uint8_t SPI_Mode);
/* Enable SPIx Peripheral */
void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t ENorDIS);

static uint8_t SPI_GetFlag(SPI_RegDef_t *pSPIx,uint32_t SPI_Flag);

void SPI_SSI(SPI_RegDef_t *pSPIx, uint8_t ENorDI);
void SPI_SSOE(SPI_RegDef_t *pSPIx, uint8_t ENorDI);

void SPI_CloseReceiption(SPI_Handle_t *pSPIHandle);
_weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEv);

static void SPI_TXEIRQ_Handle(SPI_Handle_t *pSPIHandle);
static void SPI_RXEIRQ_Handle(SPI_Handle_t *pSPIHandle);
static void SPI_OVR_Handle(SPI_Handle_t *pSPIHandle);
static void SPI_MODF_Handle(SPI_Handle_t *pSPIHandle);
#endif	/* __STM32F103XX_SPI_DRIVER_H_ */
