#ifndef __STM32F103XX_H_
#define __STM32F103XX_H_

#include "stdint.h"
#include "stddef.h"
#include "CortexMx.h"

#define _weak 	__attribute__((weak))   

/* Macro */
#define HIGH		1
#define LOW			0

#define FLAG_SET				1
#define FLAG_RESET			0


/* base addresses of Flash and SRAM memories */
#define FLASH_MEM_BASEADDR            0x08000000UL /*!< FLASH BASEADDR address in the alias region */
#define FLASH_MEM_BANK1_END       		0x0801FFFFUL /*!< FLASH END address of bank1 */

	
// bus base Address
#define APB1_BASEADDR							 PERI_BASEADDR
#define APB2_BASEADDR							(PERI_BASEADDR + 0x10000)
#define AHB_BASEADDR							(PERI_BASEADDR + 0x18000)

/* Peripheral base address of APB1 */

#define SPI2_BASEADDR			(0x40003800U)
#define SPI3_BASEADDR			(0x40003C00U)

/* Peripheral base address of APB2 */
#define GPIOA_BASEADDR  	(APB2_BASEADDR + 0x0800)
#define GPIOB_BASEADDR  	(APB2_BASEADDR + 0x0C00)
#define GPIOC_BASEADDR  	(APB2_BASEADDR + 0x1000)

#define AFIO_BASEADDR		  (APB2_BASEADDR + 0x000)

#define EXTI_BASEADDR		  (0x40010400U)

#define SPI1_BASEADDR			(0x40013000U)

#define USART1_BASEADDR		(0x40013800)
#define USART2_BASEADDR		(0x40004400)
#define USART3_BASEADDR		(0x40004800) 

#define TIMER1_BASEADDR		(0x40012C00) 
#define TIMER2_BASEADDR		(0x40000000)
#define TIMER3_BASEADDR		(0x40000400)
#define TIMER4_BASEADDR		(0x40000800)

#define ADC1_BASEADDR			(0x40012400)
#define ADC2_BASEADDR			(0x40012800) 

/* Peripheral base address of AHB */
#define RCC_BASEADDR		(0x40021000U)
#define FLASH_BASEADDR	(0x40022000U)

/* STRUCTURE OF PERIPHERAL */
typedef struct
{
	_vo uint32_t CR[2];
	_vo uint32_t IDR;
	_vo uint32_t ODR;
	_vo uint32_t BSRR;
	_vo uint32_t BRR;
	_vo uint32_t LCKR;
}GPIO_RegDef_t;

typedef struct
{
	_vo uint32_t EVCR;
	_vo uint32_t MAPR;
	_vo uint32_t EXTICR[4];
	_vo uint32_t MAPR2;
}AFIO_RegDef_t;

typedef struct 
{
	_vo uint32_t IMR;
	_vo uint32_t EMR;
	_vo uint32_t RTSR;
	_vo uint32_t FTSR;
	_vo uint32_t SWIER;
	_vo uint32_t PR;
}EXTI_RegDef_t;

typedef struct
{
	_vo uint32_t CR;
	_vo uint32_t CFGR;
	_vo uint32_t CIR;
	_vo uint32_t APB2RSTR;
	_vo uint32_t APB1RSTR;
	_vo uint32_t AHBENR;
	_vo uint32_t APB2ENR;
	_vo uint32_t APB1ENR;
	_vo uint32_t BDCR;
	_vo uint32_t CSR;
	_vo uint32_t AHBSTR;
	_vo uint32_t CFGR2;
}RCC_RegDef_t;

typedef struct
{
	_vo uint32_t ACR;
	_vo uint32_t KEYR;
	_vo uint32_t OPTKEYR;
	_vo uint32_t SR;
	_vo uint32_t CR;
	_vo uint32_t AR;
	uint32_t Reserved;
	_vo uint32_t OBR;
	_vo uint32_t WRPR;
}FLASH_RegDef_t;

typedef struct
{
	_vo uint32_t CR1;
	_vo uint32_t CR2;
	_vo uint32_t SR;
	_vo uint32_t DR;
	_vo uint32_t CRCPR;
	_vo uint32_t RXCRCR;
	_vo uint32_t TXCRCR;
	_vo uint32_t I2SCFGR;
	_vo uint32_t I2SPR;
}SPI_RegDef_t;

typedef struct
{
	_vo uint32_t	SR;
	_vo uint32_t	DR;
	_vo uint32_t	BRR;
	_vo uint32_t	CR1;
	_vo uint32_t	CR2;
	_vo uint32_t	CR3;
	_vo uint32_t	GTPR;
}USART_RegDef_t;

typedef struct
{
	_vo uint32_t SR;
	_vo uint32_t CR1;
	_vo uint32_t CR2;
	_vo uint32_t SMPR1;
	_vo uint32_t SMPR2;
	_vo uint32_t JOFR[4];
	_vo uint32_t HTR;
	_vo uint32_t LTR;
	_vo uint32_t SQR[3];
	_vo uint32_t JSQR;
	_vo uint32_t JDR[4];
	_vo uint32_t DR;
}ADC_RegDef_t;

typedef struct
{
	_vo uint32_t CR1;
	_vo uint32_t CR2;
	_vo uint32_t SMCR;
	_vo uint32_t DIER;
	_vo uint32_t SR;
	_vo uint32_t EGR;
	_vo uint32_t CCMR1;
	_vo uint32_t CCMR2;
	_vo uint32_t CCER;
	_vo uint32_t CNT;
	_vo uint32_t PSC;
	_vo uint32_t ARR;
	_vo uint32_t RCR;
	_vo uint32_t CCR[4];
	_vo uint32_t BDTR;
	_vo uint32_t DCR;
	_vo uint32_t DMAR;
}TIMER_RegDef_t;

typedef struct
{
	
}bxCan_RegDef_t;

/*!< Peripheral declaration */
#define GPIOA_BASEPTR			((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB_BASEPTR			((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC_BASEPTR			((GPIO_RegDef_t*)GPIOC_BASEADDR)

#define AFIO_BASEPTR			((AFIO_RegDef_t *)AFIO_BASEADDR)

#define EXTI_BASEPTR			((EXTI_RegDef_t *)EXTI_BASEADDR)

#define RCC_BASEPTR				((RCC_RegDef_t *)RCC_BASEADDR)

#define FLASH_BASEPTR			((FLASH_RegDef_t *)FLASH_BASEADDR)

#define SPI1_BASEPTR			((SPI_RegDef_t *)SPI1_BASEADDR)
#define SPI2_BASEPTR			((SPI_RegDef_t *)SPI2_BASEADDR)
#define SPI3_BASEPTR			((SPI_RegDef_t *)SPI3_BASEADDR)

#define USART1_BASEPTR		((USART_RegDef_t *)USART1_BASEADDR)
#define USART2_BASEPTR		((USART_RegDef_t *)USART2_BASEADDR)
#define USART3_BASEPTR		((USART_RegDef_t *)USART3_BASEADDR)

#define TIMER1_BASEPTR		((TIMER_RegDef_t *)TIMER1_BASEADDR)
#define TIMER2_BASEPTR		((TIMER_RegDef_t *)TIMER2_BASEADDR)
#define TIMER3_BASEPTR		((TIMER_RegDef_t *)TIMER3_BASEADDR)
#define TIMER4_BASEPTR		((TIMER_RegDef_t *)TIMER4_BASEADDR)

#define ADC1_BASEPTR			((ADC_RegDef_t *)ADC1_BASEADDR)
#define ADC2_BASEPTR			((ADC_RegDef_t *)ADC2_BASEADDR)

/* INCLUDE */
#include "stm32f103xx_gpio_driver.h"
#include "stm32f103xx_rcc_driver.h"
#include "stm32f103xx_spi_driver.h"
#include "stm32f103xx_i2c_driver.h"
#include "stm32f103xx_uart_driver.h"

/*
 * VECTOR TABLE
 */

#define IRQNO_EXTI0                 IRQ6
#define IRQNO_EXTI1                 IRQ7
#define IRQNO_EXTI2                 IRQ8
#define IRQNO_EXTI3                 IRQ9
#define IRQNO_EXTI4                 IRQ10

#define IRQNO_EXTI9_5               IRQ30
#define IRQNO_EXTI15_10             IRQ40

#define IRQNO_SPI1                 IRQ35
#define IRQNO_SPI2                 IRQ36
#define IRQNO_SPI3                IRQ51
/*
#define                  IRQ0
#define                  IRQ1
#define                  IRQ2
#define                  IRQ3
#define                  IRQ4
#define                  IRQ5

#define                  IRQ11
#define                  IRQ12
#define                  IRQ13
#define                  IRQ14
#define                  IRQ15
#define                  IRQ16
#define                  IRQ17
#define                  IRQ18
#define                  IRQ19
#define                  IRQ20
#define                  IRQ21
#define                  IRQ22
#define                  IRQ23
#define                  IRQ24
#define                  IRQ25
#define                  IRQ26
#define                  IRQ27
#define                  IRQ28
#define                  IRQ29

#define                  IRQ31
#define                  IRQ32
#define                  IRQ33
#define                  IRQ34

#define                  IRQ37
#define                  IRQ38
#define                  IRQ39

#define                  IRQ41
#define                  IRQ42
#define                  IRQ43
#define                  IRQ44
#define                  IRQ45
#define                  IRQ46
#define                  IRQ47
#define                  IRQ48
#define                  IRQ49
#define                  IRQ50

#define                  IRQ52
#define                  IRQ53
#define                  IRQ54
#define                  IRQ55
#define                  IRQ56
#define                  IRQ57
#define                  IRQ58
#define                  IRQ59
#define                  IRQ60
#define                  IRQ61
#define                  IRQ62
#define                  IRQ63
#define                  IRQ64
#define                  IRQ65
#define                  IRQ66
*/
#endif	/* __STM32F103XX_H_ */
