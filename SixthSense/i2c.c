/*
 * i2c.c
 *
 * Created: 1/21/2012 4:50:10 PM
 *  Author: Nikola
 */ 
#include "i2c.h"


void initI2C()
{
	TWBR = 0x01;
}


void i2cwrite(unsigned char address, unsigned char reg, unsigned char data)
{
	//start
	
	// address of the bridge when connected A1 to SCL and A0 to SDA is 0xA6 (1010 011x)
	// x = 0 for write, x = 1 for read
	
/*	TWCR = 0xA4;					// 10100100 (TWINT, TWSTA and TWEN)
	while(!(TWCR & 0x80));			// wait for ACK (TWEA)
	TWDR = address;					// load address of device
	TWCR = 0x84;
	while(!(TWCR & 0x80));			// wait for ACK from device
	
	TWDR = reg;						// send register to write to
	TWCR = 0x84;
	while(!(TWCR & 0x80));			// wait for ACK from device
	TWDR = data;					// load data
	TWCR = 0x84;
	while(!(TWCR & 0x80));			// wait for ACK from device
	if ((TWSR & 0xF8) != 0x28)
		showError(TWSR);
	
	TWCR = 0x94;					// Stop condition */
}


unsigned char i2cread(unsigned char address)
{
	char data;
	TWCR = 0xA4;					// start condition
	while(!(TWCR & 0x80));			// wait for Start to be sent
	TWDR = address;					// load SLA+R address of device
	TWCR = 0x84;					// transmit address
	while(!(TWCR & 0x80));			// wait for ACK from camera
	
	if ((TWSR 0xF8) != 0x40)		// make sure ACK has been received
		showError(TWSR);
		
	TWCR = 0x84;
	while(!(TWCR & 0x80));			// wait for ACK from camera
	
	data = TWDR;
	return data;
	// not fully sure if correct
	// need to test this out
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
	SET_BIT(PORTB, RED);
	wait_avr(250);
	CLR_BIT(PORTB, RED);
	wait_avr(250);
	SET_BIT(PORTB, RED);
	wait_avr(250);
	CLR_BIT(PORTB, RED);
	
	wait_avr(1000);
	
	int i;
	for(i = 7; i >= 3; --i)
	{
		if ((err & (1 << i)) != 0)
		{
			SET_BIT(PORTB, RED);
			wait_avr(150);
			CLR_BIT(PORTB, RED);
			wait_avr(1000);
		}
		else
		{
			SET_BIT(PORTB, RED);
			wait_avr(150);
			CLR_BIT(PORTB, RED);
			wait_avr(150);
			SET_BIT(PORTB, RED);
			wait_avr(150);
			CLR_BIT(PORTB, RED);
			wait_avr(1000);
		}			
	}
	
}



