/*
 * spi.c
 *
 * Created: 1/28/2012 8:44:59 PM
 *  Author: Nikola
 */ 

#include <avr/io.h>
#include "spi.h"

void startSPI(void)
{
	SPCR = 0x52;    // 01010010 - Master Mode, Enable SPI, Clock at Fosc/8
	SPSR = 0x00;    // Clear the status register
	
}

unsigned char SPI_transmit(unsigned char data)
{
	SPDR = data;
	
	while (!(SPSR & (1<<SPIF)));
	
	unsigned char out_data = SPDR;
	return data;
}

unsigned char SPI_receive(void)
{
	unsigned char data;
	
	SPDR = 0xff;
	
	while(!(SPSR & 0x80));
	data = SPDR;
	
	return data;
}