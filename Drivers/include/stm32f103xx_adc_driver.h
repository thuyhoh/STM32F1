#ifndef __STM32F103XX_ADC_DRIVER_H_
#define __STM32F103XX_ADC_DRIVER_H_

#include "stm32f103xx.h"

typedef enum
{
	ADC_IN0 = 0,							// PA0
	ADC_IN1,              // PA1
	ADC_IN2,              // PA2
	ADC_IN3,              // PA3
	ADC_IN4,              // PA4
	ADC_IN5,              // PA5
	ADC_IN6,              // PA6
	ADC_IN7,              // PA7
	ADC_IN8,              // PB0
	ADC_IN9,              // PB1
	ADC_IN10,             // PC0
	ADC_IN11,             // PC1
	ADC_IN12,             // PC2
	ADC_IN13,             // PC3
	ADC_IN14,             // PC4
	ADC_IN15,             // PC5
	ADC_IN16
}ADC_CHANNELx;

typedef struct 
{
	
}ADC_Init_t;

typedef struct
{
	ADC_RegDef_t *pADCx;
	ADC_Init_t ADC_Init;
}ADC_Handle_t;

/* @BIT_POSITION */
// CR1
#define ADC_CR1_AWDIE						6
#define ADC_CR1_WDEN
#define ADC_CR1_SCAN
#define ADC_CR1_DISCEN
#define ADC_CR1_DISCNUM
#define ADC_CR1_AWDEN						23
#define ADC_CR1_JAWDEN					24
// CR2
#define ADC_CR2_SWSTART 	22
#define ADC_CR2_JSWSTART 	21
#define ADC_CR2_EXTTRIG
#define ADC_CR2_CONT 			1
#define ADC_CR2_ADON 			0

/*  */

static void ADC_PinConfigure(ADC_Handle_t *pADCHandle);
void ADC_Init(ADC_Handle_t *pADCHandle);

void ADC_IRQConfig(ADC_RegDef_t *pADCx , uint8_t Priority, uint8_t ENorDI);
void ADC_IRQHandle(ADC_Handle_t *pADCHandle);


void ADC_GetValuefromChannel(ADC_Handle_t *pADCHandle);
void ADC_SelectChannel(ADC_Handle_t *pADCHandle);
void ADC_SelectSampleTime(ADC_Handle_t *pADCHandle);

/***************************************************************************
* Other API
****************************************************************************/
void ADC_PeriClockControl(ADC_RegDef_t *pADCx, uint8_t ENorDI);

static uint8_t ADC_GetFlag(ADC_RegDef_t *pADCx, uint8_t ADC_Flagname);



#endif	/* __STM32F103XX_ADC_DRIVER_H_ */