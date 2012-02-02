/*
 * i2c.c
 *
 * Created: 1/21/2012 4:50:10 PM
 *  Author: Nikola
 */ 
#include "i2c.h"

void i2cRepeatStart(unsigned char camAddress)
{
	TWCR = 0xA4;					// 10100100 (TWINT, TWSTA and TWEN)
	while(!(TWCR & 0x80));			//  wait for ACK (TWEA)
	TWDR = camAddress;					// load address of camera
	TWCR = 0x84;
	while(!(TWCR & 0x80));			// wait for ACK from camera
	if ((TWSR & 0xF8) == 0x18)
		flashSuccess();
	else
		showError(TWSR);
}

/*void ackCam(void)
{
	TWDR = CAM_W;
	TWCR = 0x84;					// 10000100 (TWINT, TWEM)
	while(!(TWCR & 0x80));			// wait for ACK from camera
}*/
void i2cwrite(unsigned char reg, unsigned char data)
{
	//start
	TWCR = 0xA4;					// 10100100 (TWINT, TWSTA and TWEN)
	while(!(TWCR & 0x80));			// wait for ACK (TWEA)
	TWDR = CAM_W;					// load address of camera
	TWCR = 0x84;
	while(!(TWCR & 0x80));			// wait for ACK from camera
	
	TWDR = reg;						// send register to write to
	TWCR = 0x84;
	while(!(TWCR & 0x80));			// wait for ACK from camera
	TWDR = data;					// load data
	TWCR = 0x84;
	while(!(TWCR & 0x80));			// wait for ACK from camera
	if ((TWSR & 0xF8) == 0x28)
		flashSuccess();
	else
		showError(TWSR);
	
	TWCR = 0x94;					// Stop condition
}
/*unsigned char i2cread(char reg, char ack)
{
	char data;
	
	TWDR = CAM_W;					// load address of camera
	TWCR = 0x84;
	while(!(TWCR & 0x80));			// wait for ACK from camera
	TWDR = reg;						// send register to read from
	TWCR = 0x84;
	while(!(TWCR & 0x80));			// wait for ACK from camera
	i2cRepeatStart();
	TWDR = CAM_R;
	TWCR = 0x84;
	while(!(TWCR & 0x80));			// wait for ACK from camera
	TWCR = 0x84;
	data = TWDR;
	
	return data;
	// not fully sure if correct
	// need to test this out
}*/

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



