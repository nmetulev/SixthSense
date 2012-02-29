/*
 * camera.c
 *
 * Created: 2/5/2012 3:13:52 PM
 *  Author: Nikola
 */ 

#include "i2c.h"
#include "camera.h"

void CamInit()
{
	
}


/*
void CamInit()
{
	int reset = 2; // reset pin on C
	SET_BIT(DDRC, reset); // enable reset pin for out
	
	CLR_BIT(PORTC, reset); // camera off
	wait_avr(200);
	SET_BIT(PORTC, reset); // camera on
	wait_avr(200);
	
	TWBR = 0x02; // set i2c clock speed
	
	i2cwrite(0x02, 0x00); // active
	wait_avr(2);
	i2cwrite(0x02, 0x40); // reset
	wait_avr(2);
	i2cwrite(0x02, 0x00); // active
	
	i2cwrite(0x03, 0x17); // DCLK = 18.8MHz
	i2cwrite(0x0B, 0x00); // white line off
	i2cwrite(0x05, 0x80); // frame rate full
	i2cwrite(0x04, 0x18); // RGB Full Size, OUT ON
	
	
	//i2cwrite(0x1E, 0xF9);
	//i2cwrite(0x0E, 0x0F);
	//i2cwrite(0x04, 0x18);
}
*/