#ifndef __STM32F103XX_FLASH_DRIVER_H_
#define __STM32F103XX_FLASH_DRIVER_H_

#include "stm32f103xx.h"

#define FLASH_RDPRT							  0x00A5U
#define FLASH_KEY1								0x45670123U
#define FLASH_KEY2								0xCDEF89ABU

typedef enum
{
	FLASH_OK,
	FLASH_ERROR,
}Flash_Status;

void Flash_Lock(void);
void Flash_Unlock(void);
void Flash_Read(volatile uint32_t AddrStart, uint8_t* Buff, uint32_t Lenght);
Flash_Status Flash_Write(volatile uint32_t AddrStart, uint8_t* Buff, uint32_t Lenght);
Flash_Status Flash_Erase(uint32_t addr_page);

#endif /*__STM32F103XX_FLASH_DRIVER_H_ */
