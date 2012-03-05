/*
 * SPItoUART.c
 *
 * Created: 2/29/2012 5:25:03 PM
 *  Author: Laptop
 */ 
#define PRESCALER 1
#define XTAL_FREQUENCY 14745600UL
#define BAUD_RATE_DIVISOR(baud) ((XTAL_FREQUENCY/PRESCALER)/(baud*16UL))
#include "SPItoUART.h"

void setBaudRate(unsigned long baudrate)
{
	unsigned long divisor = BAUD_RATE_DIVISOR(baudrate);
	
	writeRegister(0x03, 1 << 7 );
	writeRegister(0x00,(unsigned char)divisor);
	writeRegister(0x01, (unsigned char)(divisor>>8));	
}

void initUART(unsigned long baudrate)
{
	
	//setBaudRate(baudrate);
	//writeRegister(0x03, 0xBF); // access EFR register
	//writeRegister(0x02, 0xD0); // enable enhanced registers
	//writeRegister(0x03, 0x07); // 8 data bit, 2 stop bit, no parity
	//writeRegister(0x02, 0x06); // reset TXFIFO, reset RXFIFO, non FIFO mode
	//writeRegister(0x02, 0x01); // enable FIFO mode  
	
	//if(!uartConnected()) {SET_BIT(PORTB, 1); while(1);}
	//Line Control Register: Enable Writing DLH & DLL
  //& set no Parity, 2 stop bit, and 8 bit word length
  writeRegister(LCR,0x83);
  
  //Division registers DLL & DLH
  // Write '96' to get 9600 baud rate
  //Assumes you have the version with the ~14MHz crystal
  // (16x9600 = 153600 = 14.7456Mhz/96)
  // (16x38400 = 614400 = 14.7456Mhz/24)
  writeRegister(DLL,24);
  writeRegister(DLH,0x00); 
  
  //Line Control Register: Disnable Writing DLH & DLL
  //Same setup 
  writeRegister(LCR,0x03);
  
  //Modem Control Register
  //Normal Operating Mode
   writeRegister(MCR,0x00);
 
  //FIFO Control Register: Enable the FIFO and no other features
  writeRegister(FCR,0x07);
  
  if (!uartConnected()) flashLED(RED);  
}

int uartConnected() 
{
  const char TEST_CHARACTER = 'H';
  
  writeRegister(0x07, TEST_CHARACTER);

  return (readRegister(0x07) == TEST_CHARACTER);
}

void writeRegister(unsigned char address, unsigned char data)
{
	// SC16IS740 expects a R/W  bit first, followed by the 4 bit
	// register address of the byte.
	// So shift the bits left by three bits:
	unsigned char reg = address << 3;
	unsigned char regToSend = reg | 0x00;
	select();
	SPI_MasterTransmit(regToSend);
	SPI_MasterTransmit(data);
	deselect();
}

unsigned char readRegister(unsigned char address)
{
	// SC16IS740 expects a R/W  bit first, followed by the 4 bit
	// register address of the byte.
	// So shift the bits left by three bits:
	unsigned char reg = address << 3;
	// now combine the register address and the command into one byte:
	unsigned char dataToSend = reg | 0x80;
	unsigned char result;
	select();
	SPI_MasterTransmit(dataToSend);
	result = SPI_MasterTransmit(0xFF);
	deselect();
	
	return result;
}

unsigned char available()
{
	return readRegister(0x09);
}

unsigned char read()
{
	while (!available());
		//return -1;
	return readRegister(0x00);
}

void flush()
{
	unsigned char dummy;
	while (available())
		dummy = read();
}

void write(unsigned char value)
{
	
	while (readRegister(0x08) == 0);//{flashLED(RED);}
	writeRegister(0x00, value);
	
}

void ioSetDirection(unsigned char bits)
{
	writeRegister(0x0A, bits);
}

void ioSetState(unsigned char bits)
{
	writeRegister(0x0B, bits);
}