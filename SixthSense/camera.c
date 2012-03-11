/*
 * camera.c
 *
 * Created: 2/5/2012 3:13:52 PM
 *  Author: Nikola
 */ 

#include "camera.h"


const unsigned char reset_cam[4] = {0x56, 0x00, 0x26, 0x00};
const unsigned char take_picture[] = {0x56, 0x00, 0x36, 0x01, 0x00};
const unsigned char read_size[] = {0x56, 0x00, 0x34, 0x01, 0x00};
const unsigned char read_data[] = {0x56, 0x00, 0x32, 0x0C, 0x00, 0x0A, 0x00, 0x00};
const unsigned char stop_picture[] = {0x56, 0x00, 0x36, 0x01, 0x03};
const unsigned char compression[] = {0x56, 0x00, 0x31, 0x05, 0x01, 0x01, 0x12, 0x04, 0xFF}; // max compression ratio
const unsigned char comp_ratio[] = {0x56, 0x00, 0x31, 0x05, 0x01, 0x01, 0x12, 0x04}; //0x00 to 0xFF for last hex code
const unsigned char image_size[] = {0x56, 0x00, 0x31, 0x05, 0x04, 0x01, 0x00, 0x19, 0x00}; // set to 640x480(0x19, 0x00) 160x120(0x19, 0x22)
const unsigned char baud_rate[] = {0x56, 0x00, 0x24, 0x03, 0x01, 0x0D, 0xA6}; // set to 38400 (0x2A 0xF2) - 9600 (0xAE 0xC8) - 115200 (0x0D 0xA6)
const unsigned char init_end[] = {0x36, 0x32, 0x35, 0x0D, 0x0A, 0x49, 0x6E, 0x69, 0x74, 0x20, 0x65, 0x6E, 0x64, 0x0D, 0x0A};
	
const unsigned char readResponse[] = {0x76, 0x00, 0x32, 0x00, 0x00};
void transmitData(const unsigned char data[], int length)
{	
	int i;
	for(i = 0; i < length; i++)
	{
		//USART_Transmit(data[i]);
		write(data[i]);
	}
}

void resetCam(unsigned char *response)
{
	flush();
	transmitData(reset_cam, 4);
	int i;
	for (i = 0; i < 4; i++)
		response[i] = read();
	wait_avr(4000);
}

void changeBaud(unsigned char *response)
{
	flush();
	transmitData(baud_rate, 7);
	int i;
	for (i = 0; i < 5; i++)
	{
		response[i] = read();
	}		
}

void changeCompression(unsigned char *response)
{
	flush();
	transmitData(compression, 9);
	int i;
	for (i = 0; i < 6; i++)
		response[i] = read();
}

void changeSize(unsigned char *response)
{
	flush();
	transmitData(image_size, 9);
	int i;
	for (i = 0; i < 5; i++)
		response[i] = read();
	resetCam(response);
}

void stop_cam(unsigned char* response)
{
	flush();
	transmitData(stop_picture, 5);
	int i;
	for (i = 0; i < 5; i++)
		response[i] = read();
}
void capture(unsigned char* response)
{
	flush();
	transmitData(take_picture, 5);
	int i;
	for (i = 0; i < 5; i++)
		response[i] = read();
}

void getSize(unsigned char *response, unsigned int *size)
{
	flush();
	transmitData(read_size, 5);
	int i;
	for (i = 0; i < 9; i++)
		response[i] = read();
	*size = response[7]*256;
	*size += ((int)response[8] & 0x00FF);
}

void readData(unsigned char *response, int address)
{
	flush();
	transmitData(read_data, 8);
	write(address>>8);
	write(address);
	write(0x00);
	write(0x00);
	write(PACKET_SIZE>>8); // KH
	write(PACKET_SIZE); // KL  32 image size
	write(0x00);
	write(0x0A);
	
	int i;
	for (i = 0; i < 5; i++) read();
		//if (readResponse[i] != read()) flashLED(YELLOW);
		
	for (i = 0; i < PACKET_SIZE; i++)
		response[i] = read();
}

void readDataAtOnce()
{
	unsigned int size = 0;
	unsigned char response[10];
	flush();
	transmitData(read_size, 5);
	int i;
	for (i = 0; i < 9; i++)
		response[i] = read();
	size = response[7]*256;
	size += ((int)response[8] & 0x00FF);
	
	flush();
	transmitData(read_data, 8);
	write(0x00);
	write(0x00);
	write(0x00);
	write(0x00);
	write(response[7]); // KH
	write(response[8]); // KL  32 image size
	write(0x00);
	write(0x0A);
	
	for (i = 0; i < 5; i++)
		if (readResponse[i] != read()) flashLED(YELLOW);
		
	//for (i = 0; i < PACKET_SIZE; i++)
		//response[i] = read();
		
	i = 0;
	while (i++ < size)
	{
		unsigned char temp = read();
		USART_Transmit(temp);
	}		
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