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
	
	wait_avr(1000);

	flashLED(YELLOW); // init start
	SPI_MasterInit(); // enable SPI for the SPItoUSART
	initUART(24); // initialize SPI_UART // 8 for 115200
	USART_Init(3); // initialize micro UART // 3 for 115200
	flashLED(YELLOW);
	WiFlyInit();
	
	///////////////////////////////////////////// Camera End /////////////////////////////////
	unsigned char temp[14] = {0};
	resetCam(temp);
	changeBaud(temp);
	initUART(8); // change Camera UASRT to 115200
	
	//openFTP((unsigned char*) "text.txt");
	//int j;
	//for (j = 0; j< 6; ++j) USART_Transmit(temp[j]);
	//closeFTP();
	//exitCommandMode();

	//changeSize(temp);
	unsigned char count = '1';
	
	//takePhoto((unsigned char*)"image.jpg");
	
	SET_BIT(PORTB, YELLOW); // init complete
    while(1)
    {
		
        if(GET_BIT(PINB, 2) == 0)
		{
			enterCommandMode();
			unsigned char filename[26] = {0};
			connect((unsigned char*)"/motion2.php", (unsigned char*)"id=01&s=SixthSense&f=image01.jpg", filename);
			takePhoto(filename);
			//takePhoto((unsigned char*)"temp/image01.jpg");
			//connect((unsigned char*)"/rename.php", (unsigned char*)"id=01&s=SixthSense&f=image01.jpg");
			exitCommandMode();
		}
		
    }
}

void takePhoto(unsigned char *filename)
{
	unsigned char response[PACKET_SIZE] ={0};
	unsigned char temp[14] = {0};
	unsigned int size;
	//flashLED(RED);
	capture(temp);
	//flashLED(RED);
	getSize(temp, &size);
	//char buf[10];
	
	//changeCompression(temp);
	
	openFTP(filename);
	//readDataAtOnce();
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
	//flashLED(RED);
}

void flashLED(int led)
{
	wait_avr(1000);
	SET_BIT(PORTB, led);
	wait_avr(1000);
	CLR_BIT(PORTB, led);	
	wait_avr(1000);
}