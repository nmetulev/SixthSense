/*
 * i2c.h
 *
 * Created: 1/21/2012 5:02:18 PM
 *  Author: Nikola
 */ 

#include "avr.h"

#ifndef I2C_H
#define I2C_H

#define CAM_W 0x7A
#define CAM_R 0x7B

void i2cRepeatStart(unsigned char);
void ackCam(void);
void i2cwrite(unsigned char, unsigned char);
//// Helper Functions ///

void flashSuccess(void);
void showError(unsigned char);


#endif /* I2C_H_ */