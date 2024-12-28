#ifndef PCF8574_H
#define PCF8574_H

#include "gp_drive.h"
#include "i2c_drive.h"

void PCF8574_tx_byte(char i2c, char data);

#endif
