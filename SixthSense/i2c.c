/*
 * i2c.c
 *
 * Created: 1/21/2012 4:50:10 PM
 *  Author: Nikola
 */ 
#include "i2c.h"

void i2cstart(void)
{
	TWCR = 0xA4;					// 10100100 (TWINT, TWSTA and TWEN)
	while(!(TWCR & 0x80));			// wait for ACK (TWEA)
	
	if ((TWSR & 0xF8) == 0x08)
		flashSuccess();
	else
		showError(TWSR);
}

void i2cRepeatStart(void)
{
	TWCR = 0xA4;					// 10100100 (TWINT, TWSTA and TWEN)
	while(!(TWCR & 0x80));			//  wait for ACK (TWEA)
	
	if ((TWSR & 0xF8) == 0x10)
		flashSuccess();
	else
		showError(TWSR);
}

void ackCam(void)
{
	TWDR = CAM_W;						// load address of camera in TWDR
	TWCR = 0x84;					// 10000100 (TWINT, TWEM)
	while(!(TWCR & 0x80));			// wait for ACK from camera
	
	if ((TWSR & 0xF8) == 0x18)
		flashSuccess();
	else
		showError(TWSR);
}

/////// Helper Functions ////////

void flashSuccess(void)
{
	SET_BIT(PORTB, 0);
	wait_avr(150);
	CLR_BIT(PORTB, 0);
	wait_avr(150);
	SET_BIT(PORTB, 0);
	wait_avr(150);
	CLR_BIT(PORTB, 0);
	wait_avr(150);
	SET_BIT(PORTB, 0);
	wait_avr(150);
	CLR_BIT(PORTB, 0);
}

// Blink twice to show error and wait one second
// then blink one time per second to show 1
// or blink two times per second to show 0
void showError(unsigned char err)
{
	SET_BIT(PORTB, 0);
	wait_avr(250);
	CLR_BIT(PORTB, 0);
	wait_avr(250);
	SET_BIT(PORTB, 0);
	wait_avr(250);
	CLR_BIT(PORTB, 0);
	
	wait_avr(1000);
	
	int i;
	for(i = 7; i >= 3; --i)
	{
		if ((err & (1 << i)) != 0)
		{
			SET_BIT(PORTB, 0);
			wait_avr(150);
			CLR_BIT(PORTB, 0);
			wait_avr(1000);
		}
		else
		{
			SET_BIT(PORTB, 0);
			wait_avr(150);
			CLR_BIT(PORTB, 0);
			wait_avr(150);
			SET_BIT(PORTB, 0);
			wait_avr(150);
			CLR_BIT(PORTB, 0);
			wait_avr(1000);
		}			
	}
	
}



