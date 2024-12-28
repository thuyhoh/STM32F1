#include "PCF8574.h"

/*
PCF8574 pin connect	with lcd16x2
P0 -> Rs 
P1 -> RW
p2 -> e
p3 -> screen light must 1
p4 d4
p5
p6 
p7 d7
	
*/

void PCF8574_add(char i2c, char Rw)
{
	i2c_add(i2c, 0x4E, Rw);
}

void PCF8574_tx_byte(char i2c, char data)
{
	i2c_start(i2c);
	PCF8574_add(i2c, 0);
	i2c_data(i2c, data);
	i2c_stop(i2c);
}


