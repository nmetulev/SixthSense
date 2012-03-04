/*
 * camera.c
 *
 * Created: 2/5/2012 3:13:52 PM
 *  Author: Nikola
 */ 

#include "camera.h"


unsigned char reset_cam[] = {0x56, 0x00, 0x26, 0x00};
unsigned char take_picture[] = {0x56, 0x00, 0x36, 0x01, 0x00};
unsigned char read_size[] = {0x56, 0x00, 0x34, 0x01, 0x00};
unsigned char read_data[] = {0x56, 0x00, 0x32, 0x0C, 0x00, 0x0A, 0x00, 0x00};
unsigned char stop_picture[] = {0x56, 0x00, 0x36, 0x01, 0x03};
unsigned char comp_ratio[] = {0x56, 0x00, 0x31, 0x05, 0x01, 0x01, 0x12, 0x04}; //0x00 to 0xFF for last hex code
unsigned char image_size[] = {0x56, 0x00, 0x31, 0x05, 0x04, 0x01, 0x00, 0x19, 0x00}; // set to 640x480
unsigned char baud_rate[] = {0x56, 0x00, 0x24, 0x03, 0x01, 0x2A, 0xF2}; // set to 38400
unsigned char init_end[] = {0x36, 0x32, 0x35, 0x0D, 0x0A, 0x49, 0x6E, 0x69, 0x74, 0x20, 0x65, 0x6E, 0x64, 0x0D, 0x0A};
	
void transmitData(unsigned char data[])
{
	int j = strlen((char*)data);
	int i;
	
	for(i = 0; i < j; i++)
	{
		USART_Transmit(data[i]);
	}
}
void init_cam(unsigned char response[])
{
	// flush out buffer to rid of any data
	USART_flush();
	wait_avr(100);
	transmitData(reset_cam);
	wait_avr(4000);
	int i;
	for (i = 0; i < 4; i++)
		response[i] = USART_Receive();
	// set baud rate to 38400
	transmitData(baud_rate);
	wait_avr(500);
	for (i = 4; i < 9; i++)
		response[i] = USART_Receive();/*
	// set image size
	transmitData(image_size);
	wait_avr(500);
	for (i = 9; i < 14; i++)
		response[i] = USART_Receive();
	transmitData(init_end);*/
	wait_avr(2000);
}
void stop_cam(char* response)
{
	USART_flush();
	transmitData(stop_picture);
	int i;
	for (i = 0; i < 5; i++)
		*response++ = USART_Receive();
}
void capture(char* response)
{
	transmitData(take_picture);
	int i;
	for (i = 0; i < 5; i++)
		*response++ = USART_Receive();
}

void getSize(char *response, int *size)
{
	transmitData(read_size);
	int i;
	for (i = 0; i < 9; i++)
		*response++ = USART_Receive();
	*size = response[7]*256;
	*size += ((int)response[8] & 0x00FF);
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