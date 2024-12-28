/*
 * stm32f407xx_rcc_driver.c
 *
 *  Created on: Mar 29, 2019
 *      Author: admin
 */


#include "stm32f103xx_rcc_driver.h"


void RCC_AFIOControl(uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		AFIO_PCLK_ENABLE();
	}else
	{
		AFIO_PCLK_DISABLE();
	}
}

uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint8_t APB1_PreScaler[4] = { 2, 4 , 8, 16};
uint8_t PLLMUL[6] = {4, 5 , 6, 7, 8, 9};


uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1,SystemClk;

	uint8_t clksrc,temp,ahbp,apb1p;

	clksrc = ((RCC_BASEPTR->CFGR >> 2) & 0x3);
	
	SystemClk = 8000000;
	if (clksrc == 2)
	{
		SystemClk = RCC_GetPLLOutputClock();
	}else
	{
		// error
	}

	//for ahb
	temp = ((RCC_BASEPTR->CFGR >> 4 ) & 0xF);

	if(temp < 8)
	{
		ahbp = 1;
	}else
	{
		ahbp = AHB_PreScaler[temp-8];
	}



	//apb1
	temp = ((RCC_BASEPTR->CFGR >> 8 ) & 0x7);

	if(temp < 4)
	{
		apb1p = 1;
	}else
	{
		apb1p = APB1_PreScaler[temp-4];
	}

	pclk1 =  (SystemClk / ahbp) /apb1p;

	return pclk1;
}



/*********************************************************************
 * @fn      		  - RCC_GetPCLK2Value
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
uint32_t RCC_GetPCLK2Value(void)
{
	uint32_t SystemClock=0,tmp,pclk2;
	uint8_t clk_src = ( RCC_BASEPTR->CFGR >> 2) & 0x3;

	uint8_t ahbp,apb2p;

	SystemClock = 8000000;
	if(clk_src == 2)
	{
		SystemClock = RCC_GetPLLOutputClock();
	}else
	{
		// error
	}
	tmp = (RCC_BASEPTR->CFGR >> 4 ) & 0xF;

	if(tmp < 0x08)
	{
		ahbp = 1;
	}else
	{
       ahbp = AHB_PreScaler[tmp-8];
	}

	tmp = (RCC_BASEPTR->CFGR >> 11 ) & 0x7;
	if(tmp < 0x04)
	{
		apb2p = 1;
	}else
	{
		apb2p = APB1_PreScaler[tmp-4];
	}

	pclk2 = (SystemClock / ahbp )/ apb2p;

	return pclk2;
}

uint32_t  RCC_GetPLLOutputClock(void)
{
	uint32_t pllClock = 8000000U, temp, temp2;
	temp = (RCC_BASEPTR->CFGR >> 16)&0x1;
	if(!temp) pllClock /= 2;
	temp = (RCC_BASEPTR->CFGR >> 17)&0x1;
	temp2 = RCC_BASEPTR->CFGR2 & 0xf;
	temp = (RCC_BASEPTR->CFGR >> 18) & 0x7;
	if(temp2 == 0 && temp == 1)
	{
		pllClock /= 2;
	}
	if(temp >= 2 && temp <= 7)
	{
		pllClock *= PLLMUL[temp - 2];
	}else if(temp == 13)
	{
		pllClock *= 6.5;
	}
	return pllClock;
}