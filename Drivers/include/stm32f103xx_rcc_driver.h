#ifndef _STM32F103XX_RCC_DRIVE_H
#define _STM32F103XX_RCC_DRIVE_H

#include "stm32f103xx.h"
#include "stdint.h"

/* Macro */
#define CLOCK_ENABLE				1
#define CLOCK_DISABLE				0

/* Bit position */
// RCC_CR
#define RCC_CR_HSION			0
#define RCC_CR_HSIRDY			1
#define RCC_CR_HSEON			16
#define RCC_CR_HSERDY			17
#define RCC_CR_HSEBYP			18
#define RCC_CR_CSSON			19
#define RCC_CR_PLLON			24
#define RCC_CR_PLLRDY			25

// RCC_CFGR
#define RCC_CFGR_PLLSRC		16
#define RCC_CFGR_PLLPLL		17
#define RCC_CFGR_USBPRE		22

// RCC_CIR
#define RCC_CIR_LSIRDYF				0
#define RCC_CIR_LSERDYF				1
#define RCC_CIR_HSIRDYF				2
#define RCC_CIR_HSERDYF				3
#define RCC_CIR_PLLRDYF				4
#define RCC_CIR_CSSF					7
#define RCC_CIR_LSIRDYIE			8
#define RCC_CIR_LSERDYIE			9
#define RCC_CIR_HSIRDYIE			10
#define RCC_CIR_HSERDYIE			11
#define RCC_CIR_PLLRDYIE			12
#define RCC_CIR_LSIRDYC				16
#define RCC_CIR_LSERDYC				17
#define RCC_CIR_HSIRDYC				18
#define RCC_CIR_HSERDYC				19
#define RCC_CIR_PLLRDYC				20
#define RCC_CIR_CSSC					23

// RCC_APB2RSTR
#define RCC_APB2RSTR_AFIORST			0
#define RCC_APB2RSTR_IOPARST			2
#define RCC_APB2RSTR_IOPBRST			3
#define RCC_APB2RSTR_IOPCRST			4
#define RCC_APB2RSTR_ADC1RST			9
#define RCC_APB2RSTR_ADC2RST			10
#define RCC_APB2RSTR_TIM1RST			11
#define RCC_APB2RSTR_SPI1RST			12
#define RCC_APB2RSTR_TIM8RST			13
#define RCC_APB2RSTR_USART1RST		14
#define RCC_APB2RSTR_TIM9RST			19
#define RCC_APB2RSTR_TIM10RST			20
#define RCC_APB2RSTR_TIM11RST			21	

// RCC_APB1RSTR
#define RCC_APB1RSTR_DACRST				29
#define RCC_APB1RSTR_PWRRST				28
#define RCC_APB1RSTR_BKPRST 			27
#define RCC_APB1RSTR_CANRST				25
#define RCC_APB1RSTR_USBRST				23
#define RCC_APB1RSTR_I2C2RST			22
#define RCC_APB1RSTR_I2C1RST			21
#define RCC_APB1RSTR_USART3RST		18
#define RCC_APB1RSTR_USART2RST		17
#define RCC_APB1RSTR_SPI2RST			14
#define RCC_APB1RSTR_WWDGRST			11
#define RCC_APB1RSTR_TIM14RST			8
#define RCC_APB1RSTR_TIM13RST			7
#define RCC_APB1RSTR_TIM12RST			6
#define RCC_APB1RSTR_TIM7RST			5
#define RCC_APB1RSTR_TIM6RST			4
#define RCC_APB1RSTR_TIM5RST			3
#define RCC_APB1RSTR_TIM4RST			2
#define RCC_APB1RSTR_TIM3RST			1
#define RCC_APB1RSTR_TIM2RST			0


// RCC_AHBENR
#define RCC_AHBENR_DMA1EN				0
#define RCC_AHBENR_DMA2EN				1
#define RCC_AHBENR_SRAMEN				2
#define RCC_AHBENR_FLITFEN			4
#define RCC_AHBENR_CRCEN				6
#define RCC_AHBENR_FSMCEN				8
#define RCC_AHBENR_SDIOEN				10

// RCC_APB2ENR
#define RCC_APB2ENR_AFIOEN						0
#define RCC_APB2ENR_IOPAEN            2
#define RCC_APB2ENR_IOPBEN            3
#define RCC_APB2ENR_IOPCEN            4
#define RCC_APB2ENR_ADC1EN            9
#define RCC_APB2ENR_ADC2EN            10
#define RCC_APB2ENR_TIM1EN            11
#define RCC_APB2ENR_SPI1EN            12
#define RCC_APB2ENR_TIM8EN            13
#define RCC_APB2ENR_USART1EN          14
#define RCC_APB2ENR_TIM9EN            19
#define RCC_APB2ENR_TIM10EN           20
#define RCC_APB2ENR_TIM11EN           21

// RCC_APB1ENR
#define RCC_APB1ENR_DACEN				29
#define RCC_APB1ENR_PWREN				28
#define RCC_APB1ENR_BKPEN 			27
#define RCC_APB1ENR_CANEN				25
#define RCC_APB1ENR_USBEN				23
#define RCC_APB1ENR_I2C2EN			22
#define RCC_APB1ENR_I2C1EN			21
#define RCC_APB1ENR_USART3EN		18
#define RCC_APB1ENR_USART2EN		17
#define RCC_APB1ENR_SPI2EN			14
#define RCC_APB1ENR_WWDGEN			11
#define RCC_APB1ENR_TIM14EN			8
#define RCC_APB1ENR_TIM13EN			7
#define RCC_APB1ENR_TIM12EN			6
#define RCC_APB1ENR_TIM7EN			5
#define RCC_APB1ENR_TIM6EN			4
#define RCC_APB1ENR_TIM5EN			3
#define RCC_APB1ENR_TIM4EN			2
#define RCC_APB1ENR_TIM3EN			1
#define RCC_APB1ENR_TIM2EN			0

// RCC_BDCR
#define RCC_BDCR_LSEON			0
#define RCC_BDCR_LSERDY			1
#define RCC_BDCR_LSELSE			2
#define RCC_BDCR_RTCEN			15
#define RCC_BDCR_BDRST			16

// RCC_CSR
#define RCC_CSR_LSION				0
#define RCC_CSR_LSIRDY			1
#define RCC_CSR_RMVF				24
#define RCC_CSR_PINRSTF			26
#define RCC_CSR_PORRSTF			27
#define RCC_CSR_SFTRSTF			28
#define RCC_CSR_IWDGRSTF		29
#define RCC_CSR_WWDGRSTF		30
#define RCC_CSR_LPWRRSTF		31


/* Peripheral Clock Enable */
#define GPIOA_PCLK_ENABLE()				RCC_BASEPTR->APB2ENR |= (1<<2)
#define GPIOB_PCLK_ENABLE()				RCC_BASEPTR->APB2ENR |= (1<<3)
#define GPIOC_PCLK_ENABLE()				RCC_BASEPTR->APB2ENR |= (1<<4)

#define AFIO_PCLK_ENABLE()				RCC_BASEPTR->APB2ENR |= (1<<0)

#define SPI1_PCLK_ENABLE()				RCC_BASEPTR->APB2ENR |= (1<<12)
#define SPI2_PCLK_ENABLE()				RCC_BASEPTR->APB1ENR |= (1<<14)
#define SPI3_PCLK_ENABLE()				RCC_BASEPTR->APB1ENR |= (1<<15)

/* Peripheral Clock Disable */
#define GPIOA_PCLK_DISABLE()				RCC_BASEPTR->APB2ENR &= (uint32_t)~(1<<2)
#define GPIOB_PCLK_DISABLE()				RCC_BASEPTR->APB2ENR &= (uint32_t)~(1<<3)
#define GPIOC_PCLK_DISABLE()				RCC_BASEPTR->APB2ENR &= (uint32_t)~(1<<4)

#define AFIO_PCLK_DISABLE()				  RCC_BASEPTR->APB2ENR &= (uint32_t)~(1<<0)

#define SPI1_PCLK_DISABLE()				RCC_BASEPTR->APB2ENR &= (uint32_t)~(1<<12)
#define SPI2_PCLK_DISABLE()				RCC_BASEPTR->APB1ENR &= (uint32_t)~(1<<14)
#define SPI3_PCLK_DISABLE()				RCC_BASEPTR->APB1ENR &= (uint32_t)~(1<<15)

/* Pheripheral Register Reset */
#define GPIOA_REG_RESET()						do{RCC_BASEPTR->APB2RSTR |= (1<<2); RCC_BASEPTR->APB2RSTR &= (uint32_t)~(1<<2);}while(0)
#define GPIOB_REG_RESET()						do{RCC_BASEPTR->APB2RSTR |= (1<<3); RCC_BASEPTR->APB2RSTR &= (uint32_t)~(1<<3);}while(0)
#define GPIOC_REG_RESET()						do{RCC_BASEPTR->APB2RSTR |= (1<<4); RCC_BASEPTR->APB2RSTR &= (uint32_t)~(1<<4);}while(0)

#define AFIO_REG_RESET()						do{RCC_BASEPTR->APB2RSTR |= (1<<0); RCC_BASEPTR->APB2RSTR &= (uint32_t)~(1<<0);}while(0)

#define SPI1_REG_RESET()						do{RCC_BASEPTR->APB2RSTR |= (1<<12); RCC_BASEPTR->APB2RSTR &= (uint32_t)~(1<<12);}while(0)
#define SPI2_REG_RESET()						do{RCC_BASEPTR->APB1RSTR |= (1<<14); RCC_BASEPTR->APB1RSTR &= (uint32_t)~(1<<14);}while(0)
#define SPI3_REG_RESET()						do{RCC_BASEPTR->APB1RSTR |= (1<<15); RCC_BASEPTR->APB1RSTR &= (uint32_t)~(1<<15);}while(0)

#define RCC_APB2ENR_AFIOEN	0

//
#define USART1_PCLK_ENABLE()		RCC_BASEPTR->APB2ENR |= 1 << 14;
#define USART2_PCLK_ENABLE()		RCC_BASEPTR->APB1ENR |= 1 << 17;
#define USART3_PCLK_ENABLE()		RCC_BASEPTR->APB1ENR |= 1 << 18;

#define USART1_PCLK_DISABLE()		RCC_BASEPTR->APB2ENR &= (uint32_t)~(1 << 14);
#define USART2_PCLK_DISABLE()   RCC_BASEPTR->APB1ENR &= (uint32_t)~(1 << 17);
#define USART3_PCLK_DISABLE()   RCC_BASEPTR->APB1ENR &= (uint32_t)~(1 << 18);

#define USART1_REG_RESET()			do{RCC_BASEPTR->APB2RSTR &= (uint32_t)~(1 << 14); RCC_BASEPTR->APB2RSTR |= (1 << 14);}while(0)
#define USART2_REG_RESET()			do{RCC_BASEPTR->APB1RSTR &= (uint32_t)~(1 << 17); RCC_BASEPTR->APB1RSTR |= (1 << 17);}while(0)
#define USART3_REG_RESET()			do{RCC_BASEPTR->APB1RSTR &= (uint32_t)~(1 << 18); RCC_BASEPTR->APB1RSTR |= (1 << 18);}while(0)

#define ADC1_PCLK_ENABLE()			RCC_BASEPTR->APB2ENR |= (1 << RCC_APB2ENR_ADC1EN)
#define ADC2_PCLK_ENABLE()			RCC_BASEPTR->APB2ENR |= (1 << RCC_APB2ENR_ADC2EN)

#define ADC1_PCLK_DISABLE()			RCC_BASEPTR->APB2ENR &= (uint32_t)~(1 << RCC_APB2ENR_ADC1EN)
#define ADC2_PCLK_DISABLE()			RCC_BASEPTR->APB2ENR &= (uint32_t)~(1 << RCC_APB2ENR_ADC1EN)

#define ADC1_REG_DISABLE()			do{RCC_BASEPTR->APB2RSTR &= (uint32_t)~(1 << RCC_APB2RSTR_ADC1RST); RCC_BASEPTR->APB2RSTR |= (1 << RCC_APB2RSTR_ADC1RST);}while(0)
#define ADC2_REG_DISABLE()      do{RCC_BASEPTR->APB1RSTR &= (uint32_t)~(1 << RCC_APB2RSTR_ADC2RST); RCC_BASEPTR->APB1RSTR |= (1 << RCC_APB2RSTR_ADC2RST);}while(0)

/******************************************************************************************************************************

******************************************************************************************************************************/
uint32_t RCC_GetPCLK1Value(void);
uint32_t RCC_GetPCLK2Value(void);
uint32_t RCC_GetPLLOutputClock(void);
void RCC_AFIOControl(uint8_t ENorDI);
#endif
