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

#ifndef CAMERA_H_
#define CAMERA_H_

void transmitData(unsigned char*);
void init_cam(unsigned char*);
void stop_cam(char*);
void capture(char*);
void getSize(char*, int*);

#endif /* CAMERA_H_ */