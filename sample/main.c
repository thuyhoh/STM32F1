#include "main.h"
#include "stm32f103xx_spi_driver.h"

char mes[20] = "hello world";
int main(void)
{
	SPI_Handle_t spi1;
	spi1.SPI_Config.SPI_BaudRate = SPI_BAUDRATE_PCLK_DIV4;
	spi1.SPI_Config.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	spi1.SPI_Config.SPI_CPHA = SPI_CPHA_FIST_EDGE;
	spi1.SPI_Config.SPI_CPOL = SPI_CPOL_LOW;
	spi1.SPI_Config.SPI_DFF = SPI_DFF_8BITS;
	spi1.SPI_Config.SPI_Mode = SPI_MASTER_MODE;
	spi1.SPI_Config.SPI_SSM = SPI_SSM_DI;
	SPI_Init(&spi1);
	while(1)
	{
		
		SysTick_Delayms(1000);
	}
// return 0; 
}
