/*
 * SixthSense.c
 *
 */ 

#include <avr/io.h>
#include "avr.h"
#include "i2c.h"
#include "camera.h"

int main(void)
{
	
	DDRB |= 0x03; // enable LEDs pins as output

	flashLED(YELLOW); // init start
	
	CamInit();
	
	//i2cwrite(0x05, 0x80);
	
	flashLED(YELLOW); // init complete
    while(1)
    {
		
        if(GET_BIT(PINB, 2) == 0)
		{
			wait_avr(500);
			SET_BIT(PORTB, 0);
			wait_avr(500);
			CLR_BIT(PORTB, 0);	
		}
		
    }
}

void flashLED(int led)
{
	wait_avr(1000);
	SET_BIT(PORTB, led);
	wait_avr(1000);
	CLR_BIT(PORTB, led);	
	wait_avr(1000);
}