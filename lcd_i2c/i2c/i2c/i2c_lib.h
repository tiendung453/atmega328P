/*
 * i2c_lib.h
 *
 * Created: 9/28/2024 10:37:25 AM
 *  Author: DungLT
 */ 


#ifndef I2C_LIB_H_
#define I2C_LIB_H_

#include <avr/io.h>

void i2c_init();
void i2c_write(unsigned char data);
void i2c_start(void);
void i2c_stop();

#endif /* I2C_LIB_H_ */