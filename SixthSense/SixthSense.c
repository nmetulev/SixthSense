/*
 * SixthSense.c
 *
 */ 

#include <avr/io.h>
#include "avr.h"
#include "i2c.h"
#include "spi.h"
#include "SDHC.h"

int main(void)
{
	
	DDRC |= 0x18;
	wait_avr(2);
	SET_BIT(PORTC, 3);
	wait_avr(2);
	SET_BIT(PORTC, 4);
	TWBR = 0x01;
	DDRB |= 1;
	
	
	wait_avr(1000);
	SET_BIT(PORTB, 0);
	wait_avr(1000);
	CLR_BIT(PORTB, 0);	
	wait_avr(2000);
	
	i2cwrite(0x02, 0x00); // active
	wait_avr(500);
	i2cwrite(0x02, 0x40); // reset
	wait_avr(500);
	i2cwrite(0x02, 0x00); // active
	wait_avr(500);
	i2cwrite(0x05, 0x80);
	
<<<<<<< HEAD
	//i2cstart();
	//wait_avr(1000);
	//ackCam();
	
	SD_init();
=======
>>>>>>> f15f577bb56013fad8e09b9b231a12a65a56e88a
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