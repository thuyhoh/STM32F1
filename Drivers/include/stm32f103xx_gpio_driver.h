#ifndef _STM32F103XX_GPIO_DRIVE_H
#define _STM32F103XX_GPIO_DRIVE_H


#include "stm32f103xx.h"

/* Macro */
#define LOW 				0
#define HIGH				1

#define SET					HIGH
#define RESET				LOW

#define GPIO_PIN_SET		HIGH
#define GPIO_PIN_RESET		LOW

#define ENABLE			SET
#define DISABLE			RESET

/* structure */

typedef struct 
{
	uint8_t GPIO_PinNumber;  /* <! the number of pin in GPIO @GPIO_PinNumber > */
	uint8_t GPIO_PinMode;		/* <! the number of pin in GPIO @GPIO_PinMode > */
	uint8_t GPIO_PinLock;		/* <! the number of pin in GPIO @GPIO_PinLock > */
}GPIO_Config_t;

typedef struct
{
	GPIO_RegDef_t *pGPIOx;
	GPIO_Config_t GPIO_Config;
}GPIO_Handle_t;

/* @GPIO_NUMBER
 * the number of pin in GPIO
 */
#define GPIO_PIN_0				0
#define GPIO_PIN_1				1
#define GPIO_PIN_2				2
#define GPIO_PIN_3				3
#define GPIO_PIN_4				4
#define GPIO_PIN_5				5
#define GPIO_PIN_6				6
#define GPIO_PIN_7				7
#define GPIO_PIN_8				8
#define GPIO_PIN_9				9
#define GPIO_PIN_10				10
#define GPIO_PIN_11				11
#define GPIO_PIN_12				12
#define GPIO_PIN_13				13
#define GPIO_PIN_14				14
#define GPIO_PIN_15				15



/* @GPIO_PinMode
 * the mode of pin in GPIO
 */																				       // CNF   MODE
/* INPUT MODE */	
#define GPIO_INPUT_ANALOG_MODE						0x0U   // 00     00
#define GPIO_INPUT_FLOAT_MODE							0x4U   // 01     00
#define GPIO_INPUT_PU_PD									0x8U   // 10     00

/* OUTPUT MODE */
#define GPIO_OUTPUT_10MHZ_GP_PP_MODE			0x1U   // 00      01
#define GPIO_OUTPUT_10MHZ_GP_OD_MODE			0x5U   // 01      01
#define GPIO_OUTPUT_10MHZ_AF_PP_MODE			0x9U   // 10      01
#define GPIO_OUTPUT_10MHZ_AF_OD_MODE			0xDU   // 11      01

#define GPIO_OUTPUT_2MHZ_GP_PP_MODE				0x2U   // 00      10
#define GPIO_OUTPUT_2MHZ_GP_OD_MODE				0x6U   // 01      10
#define GPIO_OUTPUT_2MHZ_AF_PP_MODE				0xAU   // 10      10
#define GPIO_OUTPUT_2MHZ_AF_OD_MODE				0xEU   // 11      10

#define GPIO_OUTPUT_50MHZ_GP_PP_MODE			0x3U   // 00      11
#define GPIO_OUTPUT_50MHZ_GP_OD_MODE			0x7U   // 01      11
#define GPIO_OUTPUT_50MHZ_AF_PP_MODE			0xBU   // 10      11
#define GPIO_OUTPUT_50MHZ_AF_OD_MODE			0xFU   // 11      11

/* INTERRUPT MODE */
#define GPIO_IT_FT_MODE										0x1FU		/* Interrupt */
#define GPIO_IT_RT_MODE										0x2FU		/**/
#define GPIO_IT_FRT_MODE									0x3FU		/**/

/* @GPIO_PinLock
 * the mode of pin in GPIO
 */
 
/* Macro of Pin Status */ 
#define GPIO_PIN_LOCK			ENABLE
#define GPIO_PIN_UNLOCK		DISABLE


/*  */
#define GPIO_BASEADDR_TO_CODE(x)	( ((x) == GPIOA_BASEPTR) ?0:\
																		((x) == GPIOB_BASEPTR) ?1:\
																		((x) == GPIOC_BASEPTR) ?2:3 )

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIO, uint8_t EnorDis);

/* GPIO Init and DeInit */
void GPIO_Init(GPIO_Handle_t *pGPIO_Handle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIO);

void GPIO_DigitalInput(GPIO_RegDef_t *pGPIO, uint8_t PinNumber);
void GPIO_DigitalOutput(GPIO_RegDef_t *pGPIO, uint8_t PinNumber);
/* Read From Input Pin */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIO);

/* Write To Output Pin */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber, uint8_t PinState);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIO, uint16_t PortState);

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber);

void GPIO_SetPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber);
void GPIO_ResetPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber);

/* IRQ Configuration and ISR handling */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t Priority, uint8_t EnorDi);
void GPIO_IRQHandler(uint8_t PinNumber);


#endif
