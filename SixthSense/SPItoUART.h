/*
 * SPItoUART.h
 *
 * Created: 2/29/2012 5:25:18 PM
 *  Author: Laptop
 */ 
#include "spi.h"
#include "avr.h"
#include <avr/io.h>
#include "main.h"

#ifndef SPITOUART_H_
#define SPITOUART_H_


//Register Mapping
#define XHR 0x00
#define FCR 0x02
#define LCR 0x03
#define MCR 0x04
#define LSR 0x05
#define MSR 0x06
#define TXLVL 0x08
#define RXLVL 0x09
#define DLL 0x00
#define DLH 0x01

void setBaudRate(unsigned long baudrate);
void writeRegister(unsigned char address, unsigned char data);
unsigned char readRegister(unsigned char address);
void initUART(unsigned long baudrate);
void configureUART(unsigned long baudrate);
int uartConnected();
void ioSetDirection(unsigned char bits);
void ioSetState(unsigned char bits);
unsigned char available();
unsigned char read();
void write(unsigned char value);
unsigned char available();

#endif /* SPITOUART_H_ */