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
#include "stdlib.h"

int main(void)
{
	DDRB |= 0x03; // enable LEDs pins as output
	
	wait_avr(10000);

	flashLED(YELLOW); // init start
	SPI_MasterInit();
	initUART(24);
	USART_Init(12);
	flashLED(YELLOW);
	/*
	
	enterCommandMode();
	println((unsigned char*)"set comm close .txt");
	println((unsigned char*)"ftp put derp.txt");
	println((unsigned char*)"Test for file creation.");
	print((unsigned char*)".txt");
	exitCommandMode();*/
	
	
	///////////////////////////////////////////// Camera End /////////////////////////////////
	unsigned char temp[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	unsigned char response[PACKET_SIZE] ={0};
	unsigned int size;
	resetCam(temp);
	changeSize(temp);
	flashLED(RED);
	capture(temp);
	flashLED(RED);
	getSize(temp, &size);
	char buf[10];
	
	openFTP((unsigned char*)"image.jpg");
	int address = 0;
	int eof = 0;
	unsigned char prev = 0x00;
	while(address<size)
	{
		readData(response, address);
		int j;
	//	print((unsigned char*)itoa(address, buf, 10));
		for (j = 0; j < PACKET_SIZE; ++j)
		{
			
			USART_Transmit(response[j]);
			if ((response[j] == (char)0xD9) && (prev == (char)0xFF)) {eof = 1; break;}
			else prev = (char)response[j];
		}
		
		address += PACKET_SIZE;
		if (eof == 1) break;
	}
	//println((unsigned char*)itoa(size, buf, 10));
	closeFTP();
	stop_cam(temp);
	
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