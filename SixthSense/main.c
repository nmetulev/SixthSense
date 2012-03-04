/*
 * SixthSense.c
 *
 */ 

#include <avr/io.h>
#include "avr.h"
#include "i2c.h"
#include "camera.h"
//#include "lcd.h"
//#include "spi.h"
#include "WiFly.h"
#include "SPItoUART.h"
#include "USART.h"

int main(void)
{
	DDRB |= 0x03; // enable LEDs pins as output
	
	wait_avr(10000);

	flashLED(YELLOW); // init start
	SPI_MasterInit();
	initUART(9600);
	flashLED(YELLOW);
	
	
	//enterCommandMode();
	//println((unsigned char*) "ftp put derp.txt\r");
	//println((unsigned char*)"Test for file creation.");
	//println((unsigned char*)".txt");
	//exitCommandMode();
	
	///////////////////////////////////////////// Camera End /////////////////////////////////
	unsigned char temp[9];
	USART_Init(12);
	init_cam(temp);
	
	int i;
	enterCommandMode();
	println((unsigned char*) "ftp put camera_response.txt\r");
	for (i = 0; i < 9; ++i) {write(temp[i]);}
		wait_avr(500);
	println((unsigned char*)".txt");
	exitCommandMode();
	
	SET_BIT(PORTB, YELLOW); // init complete
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