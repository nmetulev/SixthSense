/*
 * camera.h
 *
 * Created: 2/5/2012 3:26:44 PM
 *  Author: Nikola
 */ 
#include "USART.h"
#include "avr.h"
#include <avr/io.h>
#include "string.h"
#include "main.h"
#include "SPItoUART.h"
#include "WiFly.h"

#ifndef CAMERA_H_
#define CAMERA_H_

#define PACKET_SIZE 32

void transmitData(const unsigned char*, int);
void resetCam(unsigned char*);
void changeSize(unsigned char*);
void changebaud(unsigned char*);
void stop_cam(unsigned char*);
void capture(unsigned char*);
void getSize(unsigned char*, unsigned int*);
void readData(unsigned char *, int);

#endif /* CAMERA_H_ */