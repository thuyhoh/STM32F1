#include "stm32f103xx_flash_driver.h"

/****************************************************************************
 * @fn	  				- 			Flash_Lock

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void Flash_Lock(void)
{
	/* Set Lock bit in FLASH_CR */
	FLASH_BASEPTR->CR |= 1<<7;
}

/****************************************************************************
 * @fn	  				- 			Flash_Unlock

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void Flash_Unlock(void)
{
	/* Unlock sequence */
	FLASH_BASEPTR->KEYR = FLASH_KEY1;
	FLASH_BASEPTR->KEYR = FLASH_KEY2;
}

/****************************************************************************
 * @fn	  				- 			Flash_Unlock

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void Flash_Read(volatile uint32_t AddrStart, uint8_t* Buff, uint32_t Lenght)
{
	uint32_t i;
	for(i = 0; i< Lenght; i++)
	{
		*(uint8_t*)(Buff + i) = *(uint8_t*)(AddrStart + i); 
	}
}

/****************************************************************************
 * @fn	  				- 			Flash_Unlock

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
Flash_Status Flash_Write(volatile uint32_t AddrStart, uint8_t* Buff, uint32_t Lenght)
{
	if((AddrStart == 0x0000) ||  Buff == 0x00 || ((Lenght%2)| (Lenght == 0)))
	{
		// Error
		return FLASH_ERROR;
	}
	// check bit busy
	while(FLASH_BASEPTR->SR & 1)
	{
		// wait to bay bit
	}
	// check Lock bit in FLASH_CR
	if(FLASH_BASEPTR->CR & (1<<7))
	{
		Flash_Unlock();	
	}
	// Set the PG bit in the FLASH_CR register
	FLASH_BASEPTR->CR |= 1<<0;
	uint32_t i;
	for(i = 0; i< (Lenght/2); i++)
	{
		*((uint16_t*)(AddrStart + i*2U)) = *((uint16_t*)(Buff + i*2U));
	}
	// check bit busy
	while(FLASH_BASEPTR->SR & 1)
	{
		// wait to bay bit
	}
	// clear the PG bit in the FLASH_CR register
	FLASH_BASEPTR->CR |= ~(uint32_t)(1<<0);
	// Lock Flash
	Flash_Lock();
	return FLASH_OK;
}


/****************************************************************************
 * @fn	  				- 			Flash_Unlock

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
Flash_Status Flash_Erase(uint32_t addr_page)
{
	if(addr_page < 0x08000000 || addr_page > 0x0801FFFF)
	{
		return FLASH_ERROR;
	}
	// check bit busy
	while(FLASH_BASEPTR->SR & 1)
	{
		// wait to bay bit
	}
	// check Lock bit in FLASH_CR
	if(FLASH_BASEPTR->CR & (1<<7))
	{
		Flash_Unlock();	
	}
	// Set the PER bit in the FLASH_CR register
	FLASH_BASEPTR->CR |= 1<<1;	
	// Program the FLASH_AR register to select a page to erase
	FLASH_BASEPTR->AR = addr_page;
	// Set the STRT bit in the FLASH_CR register
	FLASH_BASEPTR->CR |= 1<<5;
	// waiting busy bit is reset
	while(FLASH_BASEPTR->SR & 1<<0);
	// clear PER bit
	FLASH_BASEPTR->CR &= ~(uint32_t)(1<<1);
	// clear STRT bit
	FLASH_BASEPTR->CR &= 1<<5;
	// Lock Flash
	Flash_Lock();
	return FLASH_OK;
}
