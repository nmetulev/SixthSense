/*
 * SixthSense.c
 *
 */ 

#include <avr/io.h>
#include "avr.h"
#include "i2c.h"

int main(void)
{
	
	TWBR = 0x02;
	DDRB |= 1;
	
	
	wait_avr(1000);
	SET_BIT(PORTB, 0);
	wait_avr(1000);
	CLR_BIT(PORTB, 0);	
	wait_avr(2000);
	
	
	i2cstart();
	wait_avr(1000);
	ackCam();
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