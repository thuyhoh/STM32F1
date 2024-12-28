/*
 *  file name  : stm32f407xx_gpio_driver.h
 *  Created on : Aug 27, 2024
 *  Author     : THUY
 */

#include "stm32f103xx_uart_driver.h"

/*********************************************************************
 * @fn      		  		- USART_PeriClockControl
 *
 * @brief             - Enable Clock for USARTx
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -  

**********************************************************************/
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
	// Enable Clock for AFIO
	RCC_AFIOControl(ENABLE);
	if(EnorDi == ENABLE)
	{	// enable clock
		if(pUSARTx == USART1_BASEPTR)
		{
			USART1_PCLK_ENABLE();
		}else if(pUSARTx == USART2_BASEPTR)
		{
			USART2_PCLK_ENABLE();
		}else if(pUSARTx == USART3_BASEPTR)
		{
			USART3_PCLK_ENABLE();
		}else
		{
			// error
		}
	}
	else
	{ // diable clock
		if(pUSARTx == USART1_BASEPTR)
		{
			USART1_PCLK_DISABLE();
		}else if(pUSARTx == USART2_BASEPTR)
		{
			USART2_PCLK_DISABLE();
		}else if(pUSARTx == USART3_BASEPTR)
		{
			USART3_PCLK_DISABLE();
		}else 
		{
			// error
		}
	}
}


/*********************************************************************
 * @fn      		  		- USART_Init
 *
 * @brief             - Initialization for USARTx
 *
 * @param[pUSARTHandle]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -  

**********************************************************************/
void USART_Init(USART_Handle_t *pUSARTHandle)
{
	// Enable Clock for USART
	USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);

	// Configure Pin for USART
	USART_PinConfig(pUSARTHandle->pUSARTx);
	
	uint32_t temp = 0;
/******************************** Configuration of CR1******************************************/
	if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
	{ // transmission only
		temp |= (1<< USART_CR1_TE);
		temp &= (uint32_t)~(1<< USART_CR1_RE);
	}else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
	{	// receiver only
		temp &= (uint32_t)~(1<< USART_CR1_TE);
		temp |= (1<< USART_CR1_RE);
	}else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
	{ // both tx and rx
		temp |= (1<< USART_CR1_TE);
		temp |= (1<< USART_CR1_RE);
	}
	// WORD LENGHT
	if(pUSARTHandle->USART_Config.USART_WordLength ==		USART_WORDLEN_9BITS)
	{
		temp |= (1 << USART_CR1_M);
	}else
	{
		 temp &= (uint32_t)~(1 << USART_CR1_M);
	}
		// PARITY CONTROL
	if(pUSARTHandle->USART_Config.USART_ParityControl != USART_PARITY_DISABLE)
	{
		// Parity control enable
		temp |= (1 << USART_CR1_PCE); 
		if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD)
		{ // USART_PARITY_EN_ODD
			temp |= (1 << USART_CR1_PS);
		}else
		{ // USART_PARITY_EN_EVEN
			temp &= (uint32_t)~(1 << USART_CR1_PS);
		}
	}else 
	{ // Parity control disable
		temp &= (uint32_t)~(1<<USART_CR1_PCE); 
	}
	
	// store value into CR1
	pUSARTHandle->pUSARTx->CR1 |= temp;
/******************************** Configuration of CR2******************************************/
	temp = 0;
	// STOP BIT
	// clear stop[1:0] in usart_cr2
	temp &= (uint32_t)~(3<<12);
	temp |= pUSARTHandle->USART_Config.USART_NoOfStopBits;

	// store value into CR2
	pUSARTHandle->pUSARTx->CR2 |= temp;
/******************************** Configuration of CR2******************************************/	
	temp = 0;
	if ( pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
		//Implement the code to enable CTS flow control 
		temp |= ( 1 << USART_CR3_CTSE);
		temp &= (uint32_t)~( 1 << USART_CR3_CTSE);

	}else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{
		//Implement the code to enable RTS flow control 
		temp &= (uint32_t)~( 1 << USART_CR3_CTSE);
		temp |= ( 1 << USART_CR3_CTSE);

	}else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		//Implement the code to enable both CTS and RTS Flow control 
		temp |= ( 1 << USART_CR3_CTSE);
		temp |= ( 1 << USART_CR3_CTSE);
	}
	// store value into CR2
	pUSARTHandle->pUSARTx->CR3 |= temp;
	
/******************************** Configuration Baud rate for USART ******************************************/		
//	pUSARTHandle->pUSARTx->BRR |= 0x1D4C;
	 USART_SetBaudRate(pUSARTHandle->pUSARTx,pUSARTHandle->USART_Config.USART_Baud);	
}

/*********************************************************************
 * @fn      		  		- USART_DeInit
 *
 * @brief             - Initialization for USARTx
 *
 * @param[pUSARTHandle]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -  

**********************************************************************/
void USART_DeInit(USART_RegDef_t *pUSARTx)
{
	// disable clock for USART
	// reset USARTx register 
}

/*********************************************************************
 * @fn      		  		- USART_DeInit
 *
 * @brief             - Initialization for USARTx
 *
 * @param[pUSARTHandle]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -  

**********************************************************************/
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx , uint32_t FlagName)
{
	if(pUSARTx->SR & FlagName) return FLAG_SET;
	return FLAG_RESET;
}

/*********************************************************************
 * @fn      		  		- USART_DeInit
 *
 * @brief             - Initialization for USARTx
 *
 * @param[pUSARTHandle]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -  

**********************************************************************/
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{ // enable uart
		pUSARTx->CR1 |= (1 << USART_CR1_UE);
	}else
	{ // disable uart
		pUSARTx->CR1 &= (uint32_t)~(1 << USART_CR1_UE);
	}
}

/*********************************************************************
 * @fn      		  		- USART_DeInit
 *
 * @brief             - Initialization for USARTx
 *
 * @param[pUSARTHandle]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -  

**********************************************************************/
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName)
{
	pUSARTx->SR &= (uint32_t)~(StatusFlagName);
}

/*********************************************************************
 * @fn      		  		- USART_DeInit
 *
 * @brief             - Initialization for USARTx
 *
 * @param[pUSARTHandle]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -  

**********************************************************************/
void USART_SendData(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len)
{
	uint16_t *pdata;
  //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until TXE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_TXE_FLAG));

         //Check the USART_WordLength item for 9BIT or 8BIT in a frame
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits 
			pdata = (uint16_t*) pTxBuffer;
			pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF); // Load 9 bits into DR regsiter
			
			//check for USART_ParityControl
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used in this transfer. so, 9bits of user data will be sent
				//Implement the code to increment pTxBuffer twice 
				pTxBuffer++; // save data
				pTxBuffer++; // save parity bit
			}
			else
			{
				//Parity bit is used in this transfer . so , 8bits of user data will be sent
				//The 9th bit will be replaced by parity bit by the hardware
				pTxBuffer++;
			}
		}
		else
		{
			//This is 8bit data transfer 
			pUSARTHandle->pUSARTx->DR = (*pTxBuffer  & (uint8_t)0xFF);
			
			//Implement the code to increment the buffer address
			pTxBuffer++;
		}
	}

	//Implement the code to wait till TC flag is set in the SR
	while( ! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_TC_FLAG));

}

/*********************************************************************
 * @fn      		  		- USART_DeInit
 *
 * @brief             - Initialization for USARTx
 *
 * @param[pUSARTHandle]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -  

**********************************************************************/
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	
   //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until RXNE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_RXNE_FLAG)){} 

		//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			//We are going to receive 9bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used. so, all 9bits will be of user data

				//read only first 9 bits. so, mask the DR with 0x01FF
				*((uint16_t*) pRxBuffer) = (pUSARTHandle->pUSARTx->DR  & (uint16_t)0x1FF);

				//Now increment the pRxBuffer two times
				(uint16_t*) pRxBuffer++;
				(uint16_t*) pRxBuffer++;
			}
			else
			{
				//Parity is used, so, 8bits will be of user data and 1 bit is parity
				 *pRxBuffer = (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);
				 
				 //Increment the pRxBuffer
				(pRxBuffer)++;
			}
		}
		else
		{
			//We are going to receive 8bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used , so all 8bits will be of user data

				//read 8 bits from DR
				 *pRxBuffer = (uint8_t)pUSARTHandle->pUSARTx->DR;
			}

			else
			{
				//Parity is used, so , 7 bits will be of user data and 1 bit is parity

				//read only 7 bits , hence mask the DR with 0X7F
				 *pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & 0x7F);

			}

			//increment the pRxBuffer
			pRxBuffer++;
		}
	}
}


/*********************************************************************
 * @fn      		  - USART_SendDataWithIT
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - Resolve all the TODOs 

 */
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len)
{
	uint8_t TxBusyState = pUSARTHandle->TxBusyState;

	if(TxBusyState != USART_BUSY_IN_TX)
	{
		pUSARTHandle->TxLen = Len;
		pUSARTHandle->pTxBuffer = pTxBuffer;
		pUSARTHandle->TxBusyState = USART_BUSY_IN_TX;

		//Implement the code to enable interrupt for TXE
		pUSARTHandle->pUSARTx->SR = USART_CR1_TXEIE;
		

		//Implement the code to enable interrupt for TC 
		pUSARTHandle->pUSARTx->SR = USART_CR1_TCIE;
	}

	return TxBusyState;

}

/*********************************************************************
 * @fn      		  - USART_ReceiveDataIT
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - Resolve all the TODOs 

**********************************************************************/
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t RxBusyState = pUSARTHandle->RxBusyState;

	if(RxBusyState != USART_BUSY_IN_RX)
	{
		pUSARTHandle->RxLen = Len;
		pUSARTHandle->pRxBuffer = pRxBuffer;
		pUSARTHandle->RxBusyState = USART_BUSY_IN_RX;

		//Implement the code to enable interrupt for RXNE
		pUSARTHandle->pUSARTx->CR1 = USART_CR1_RXNEIE;

	}
	return RxBusyState;

}

/*********************************************************************
 * @fn      		  		- USART_DeInit
 *
 * @brief             - Initialization for USARTx
 *
 * @param[pUSARTHandle]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -  

**********************************************************************/
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)
{
	NVIC_IRQConfig(IRQNumber, EnorDi);
	NVIC_IRQPriorityConfig(IRQNumber, IRQPriority);
}

/*********************************************************************
 * @fn      		  - USART_IRQHandler
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - Resolve all the TODOs

 */
void USART_IRQHandling(USART_Handle_t *pUSARTHandle)
{

	uint32_t temp1 , temp2, temp3;
	uint8_t *pdata;
/*************************Check for TC flag ********************************************/

    //Implement the code to check the state of TC bit in the SR
	temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_TC);
	
	 //Implement the code to check the state of TCEIE bit 
	temp2 = pUSARTHandle->pUSARTx->CR1 & ( 1 << USART_CR1_TCIE);

	if(temp1 && temp2 )
	{
		//this interrupt is because of TC
		
		//close transmission and call application callback if TxLen is zero
		if ( pUSARTHandle->TxBusyState == USART_BUSY_IN_TX)
		{
			//Check the TxLen . If it is zero then close the data transmission
			if(! pUSARTHandle->TxLen )
			{
				//Implement the code to clear the TC flag
				pUSARTHandle->pUSARTx->SR &= (uint32_t)~( 1 << USART_SR_TC);
				
				//Implement the code to clear the TCIE control bit 
				
				//Reset the application state
				pUSARTHandle->TxBusyState = USART_READY;
				
				//Reset Buffer address to NULL
				pUSARTHandle->pTxBuffer = NULL;
				
				//Reset the length to zero
				pUSARTHandle->TxLen = 0;
				
				//Call the applicaton call back with event USART_EVENT_TX_CMPLT
				USART_ApplicationEventCallback(pUSARTHandle,USART_EVENT_TX_CMPLT);
			}
		}
	}

/*************************Check for TXE flag ********************************************/

	//Implement the code to check the state of TXE bit in the SR
	temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_TXE);
	
	//Implement the code to check the state of TXEIE bit in CR1
	temp2 = pUSARTHandle->pUSARTx->CR1 & ( 1 << USART_CR1_TXEIE);


	if(temp1 && temp2 )
	{
		//this interrupt is because of TXE
		
		if(pUSARTHandle->TxBusyState == USART_BUSY_IN_TX)
		{
			//Keep sending data until Txlen reaches to zero
			if(pUSARTHandle->TxLen > 0)
			{
				//Check the USART_WordLength item for 9BIT or 8BIT in a frame
				if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
				{
					//if 9BIT , load the DR with 2bytes masking the bits other than first 9 bits
					pdata = (uint16_t*) pUSARTHandle->pTxBuffer;
					
					//loading only first 9 bits , so we have to mask with the value 0x01FF
					pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);

					//check for USART_ParityControl
					if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
					{
						//No parity is used in this transfer , so, 9bits of user data will be sent
						//Implement the code to increment pTxBuffer twice
						pUSARTHandle->pTxBuffer++;
						pUSARTHandle->pTxBuffer++;
						
						//Implement the code to decrement the length
						pUSARTHandle->TxLen -= 2;
					}
					else
					{
						//Parity bit is used in this transfer . so , 8bits of user data will be sent
						//The 9th bit will be replaced by parity bit by the hardware
						pUSARTHandle->pTxBuffer++;
						
						//Implement the code to decrement the length
						pUSARTHandle->TxLen--;
					}
				}
				else
				{
					//This is 8bit data transfer
					pUSARTHandle->pUSARTx->DR = (*pUSARTHandle->pTxBuffer  & (uint8_t)0xFF);

					//Implement the code to increment the buffer address
					pUSARTHandle->pTxBuffer++;
					
					//Implement the code to decrement the length
					pUSARTHandle->TxLen--;
				}
				
			}
			if (pUSARTHandle->TxLen == 0 )
			{
				//TxLen is zero 
				//Implement the code to clear the TXEIE bit (disable interrupt for TXE flag )
				pUSARTHandle->pUSARTx->CR1 &= (uint32_t)~(1 << USART_CR1_TXEIE);
			}
		}
	}
	
/*************************Check for RXNE flag ********************************************/

	temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_RXNE);
	temp2 = pUSARTHandle->pUSARTx->CR1 & ( 1 << USART_CR1_RXNEIE);


	if(temp1 && temp2 )
	{
		//this interrupt is because of rxne
		//this interrupt is because of txe
		if(pUSARTHandle->RxBusyState == USART_BUSY_IN_RX)
		{
			//TXE is set so send data
			if(pUSARTHandle->RxLen > 0)
			{
				//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
				if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
				{
					//We are going to receive 9bit data in a frame

					//Now, check are we using USART_ParityControl control or not
					if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
					{
						//No parity is used. so, all 9bits will be of user data

						//read only first 9 bits so mask the DR with 0x01FF
						*((uint16_t*) pUSARTHandle->pRxBuffer) = (pUSARTHandle->pUSARTx->DR  & (uint16_t)0x01FF);

						//Now increment the pRxBuffer two times
						pUSARTHandle->pRxBuffer++;
						pUSARTHandle->pRxBuffer++;
						
						//Implement the code to decrement the length
						pUSARTHandle->RxLen -= 2;
					}
					else
					{
						//Parity is used. so, 8bits will be of user data and 1 bit is parity
						 *pUSARTHandle->pRxBuffer = (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);
						 
						 //Now increment the pRxBuffer
						 pUSARTHandle->pRxBuffer++;
						 
						 //Implement the code to decrement the length
						 pUSARTHandle->RxLen--;
					}
				}
				else
				{
					//We are going to receive 8bit data in a frame

					//Now, check are we using USART_ParityControl control or not
					if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
					{
						//No parity is used , so all 8bits will be of user data

						//read 8 bits from DR
						 *pUSARTHandle->pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);
					}

					else
					{
						//Parity is used, so , 7 bits will be of user data and 1 bit is parity

						//read only 7 bits , hence mask the DR with 0X7F
						 *pUSARTHandle->pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR  & (uint8_t)0x7F);

					}

					//Now , increment the pRxBuffer
					pUSARTHandle->pRxBuffer++;
					
					//Implement the code to decrement the length
					pUSARTHandle->RxLen--;
				}		
					
					
			}//if of >0

			if(! pUSARTHandle->RxLen)
			{
				//disable the rxne
				pUSARTHandle->pUSARTx->CR1 &= (uint32_t)~( 1 << USART_CR1_RXNEIE );
				pUSARTHandle->RxBusyState = USART_READY;
				USART_ApplicationEventCallback(pUSARTHandle,USART_EVENT_RX_CMPLT);
			}
		}
	}
	
	
/*************************Check for CTS flag ********************************************/
//Note : CTS feature is not applicable for UART4 and UART5

	//Implement the code to check the status of CTS bit in the SR
	temp1 = pUSARTHandle->pUSARTx->SR & (1 << USART_SR_CTS);
	
	//Implement the code to check the state of CTSE bit in CR1
	temp2 = pUSARTHandle->pUSARTx->CR3 & ( 1 << USART_CR3_CTSE);
	
	//Implement the code to check the state of CTSIE bit in CR3 (This bit is not available for UART4 & UART5.)
	temp3 = pUSARTHandle->pUSARTx->CR3 & ( 1 << USART_CR3_CTSE);


	if(temp1  && temp2 )
	{
		//Implement the code to clear the CTS flag in SR
		pUSARTHandle->pUSARTx->SR &= (uint32_t)~(1<< USART_SR_CTS);
		
		//this interrupt is because of cts
		USART_ApplicationEventCallback(pUSARTHandle,USART_EVENT_CTS);
	}

/*************************Check for IDLE detection flag ********************************************/

	//Implement the code to check the status of IDLE flag bit in the SR
	temp1 = pUSARTHandle->pUSARTx->SR & (1 << USART_SR_IDLE);
	
	//Implement the code to check the state of IDLEIE bit in CR1
	temp2 = pUSARTHandle->pUSARTx->CR3 & ( 1 << USART_CR3_CTSE);


	if(temp1 && temp2)
	{
		//Implement the code to clear the IDLE flag. Refer to the RM to understand the clear sequence 
		// read SR -> read DR
		temp3 = pUSARTHandle->pUSARTx->SR | pUSARTHandle->pUSARTx->DR;
		
		//this interrupt is because of idle
		USART_ApplicationEventCallback(pUSARTHandle,USART_EVENT_IDLE);
	}

/*************************Check for Overrun detection flag ********************************************/

	//Implement the code to check the status of ORE flag  in the SR
	temp1 = pUSARTHandle->pUSARTx->SR & USART_SR_ORE;
	
	//Implement the code to check the status of RXNEIE  bit in the CR1
	temp2 = pUSARTHandle->pUSARTx->CR1 & USART_CR1_RXNEIE;


	if(temp1  && temp2 )
	{
		//Need not to clear the ORE flag here, instead give an api for the application to clear the ORE flag . 
		//this interrupt is because of Overrun error 
		USART_ApplicationEventCallback(pUSARTHandle,USART_EVENT_ORE);
	}



/*************************Check for Error Flag ********************************************/

//Noise Flag, Overrun error and Framing Error in multibuffer communication
//We dont discuss multibuffer communication in this course. please refer to the RM
//The blow code will get executed in only if multibuffer mode is used. 

	temp2 =  pUSARTHandle->pUSARTx->CR3 & ( 1 << USART_CR3_EIE) ;

	if(temp2 )
	{
		temp1 = pUSARTHandle->pUSARTx->SR;
		if(temp1 & ( 1 << USART_SR_FE))
		{
			/*
				This bit is set by hardware when a de-synchronization, excessive noise or a break character
				is detected. It is cleared by a software sequence (an read to the USART_SR register
				followed by a read to the USART_DR register).
			*/
			USART_ApplicationEventCallback(pUSARTHandle,USART_ERREVENT_FE);
		}

		if(temp1 & ( 1 << USART_SR_NE) )
		{
			/*
				This bit is set by hardware when noise is detected on a received frame. It is cleared by a
				software sequence (an read to the USART_SR register followed by a read to the
				USART_DR register).
			*/
			USART_ApplicationEventCallback(pUSARTHandle,USART_ERREVENT_NF);
		}

		if(temp1 & ( 1 << USART_SR_ORE) )
		{
			USART_ApplicationEventCallback(pUSARTHandle,USART_ERREVENT_ORE);
		}
	}
} 

/*********************************************************************
 * @fn      		  - USART_SetBaudRate
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -  Resolve all the TODOs

 */
void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{

	//Variable to hold the APB clock
	uint32_t PCLKx;

  //Get the value of APB bus clock in to the variable PCLKx
  if(pUSARTx == USART1_BASEPTR)
  {
	   //USART1 and USART6 are hanging on APB2 bus
	   PCLKx = RCC_GetPCLK2Value();
  }else
  {
	   PCLKx = RCC_GetPCLK1Value();
  }
  uint32_t div = PCLKx;
	uint32_t dec;
	double F_part = PCLKx;
	double frac2 = 1.00;
	uint32_t tempreg;
	
	div = div / (BaudRate*16);
	F_part = 16*((F_part / (BaudRate*16))-div);
	dec = F_part;
	frac2 = 100*(F_part-dec);
	if(frac2>50)
	{
		dec ++;
		if(dec == 16)
		{
			dec = 0;
			div ++;
		}
	}
	
	tempreg = (div<<4)|dec;


  //copy the value of tempreg in to BRR register
  pUSARTx->BRR = tempreg;
}


/*********************************************************************
 * @fn      		  		- USART_PinConfig
 *
 * @brief             - Configure pin for USART
 *
 * @param[pUSARTHandle]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -  

**********************************************************************/
/*
Tx: Alternate function push-pull
Rx: Input floating/ Input pull-up
CK: Alternate function push-pull
RTS: Alternate function push-pull
CTS:  Input floating/ Input pull-up
				
				Default						Remap
USART1: 
Tx				PA9
Rx				PA10
CK				PA8
RTS				PA12
CTS				PA11

USART2: 
Tx				PA2
Rx				PA3
CK				PA4
RTS				PA1
CTS				PA0

USART3: 
Tx				PB10
Rx				PB11
CK				PB12
RTS				PB14
CTS				PB13

*/
_weak void USART_PinConfig(USART_RegDef_t *pUSARTx)
{
	GPIO_Handle_t GPIOHandle;
	if(pUSARTx == USART1_BASEPTR)
	{
		GPIOHandle.pGPIOx = GPIOA_BASEPTR;
		GPIO_PeriClockControl(GPIOA_BASEPTR, ENABLE);
		GPIOA_BASEPTR->CR[1] &= (uint32_t)~(0xffff);
		// Tx
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_9;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
		GPIO_Init(&GPIOHandle);
		// Rx
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_10;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_INPUT_PU_PD;
		GPIO_Init(&GPIOHandle);
		// CK
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_8;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
		GPIO_Init(&GPIOHandle);
		// RTS
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_12;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
		GPIO_Init(&GPIOHandle);
		// CTS
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_11;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
		GPIO_Init(&GPIOHandle);
		
	}else if(pUSARTx == USART2_BASEPTR)
	{
		GPIOHandle.pGPIOx = GPIOA_BASEPTR;
		GPIO_PeriClockControl(GPIOA_BASEPTR, ENABLE);
		GPIOA_BASEPTR->CR[0] &= (uint32_t)~(0xffff);
		GPIOHandle.pGPIOx = GPIOA_BASEPTR;
		// Tx
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_2;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
		GPIO_Init(&GPIOHandle);
		// Rx
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_3;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_INPUT_PU_PD;
		GPIO_Init(&GPIOHandle);
		// CK
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_4;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
		GPIO_Init(&GPIOHandle);
		// RTS
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_1;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
		GPIO_Init(&GPIOHandle);
		// CTS
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_0;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
		GPIO_Init(&GPIOHandle);
		
	}if(pUSARTx == USART3_BASEPTR)
	{
		GPIOHandle.pGPIOx = GPIOB_BASEPTR;
		// Tx
		GPIOHandle.pGPIOx = GPIOB_BASEPTR;
		GPIO_PeriClockControl(GPIOB_BASEPTR, ENABLE);
		GPIOB_BASEPTR->CR[1] &= (uint32_t)~(0xffff);
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_10;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
		GPIO_Init(&GPIOHandle);
		// Rx
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_11;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_INPUT_PU_PD;
		GPIO_Init(&GPIOHandle);
		// CK
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_12;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
		GPIO_Init(&GPIOHandle);
		// RTS
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_14;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
		GPIO_Init(&GPIOHandle);
		// CTS
		GPIOHandle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_13;
		GPIOHandle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
		GPIO_Init(&GPIOHandle);
		
	}else
	{
		// error
	}
}

/*********************************************************************
 * @fn      		  		- USART_DeInit
 *
 * @brief             - Initialization for USARTx
 *
 * @param[pUSARTHandle]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -  

**********************************************************************/
_weak void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle,uint8_t AppEv)
{
	
}
