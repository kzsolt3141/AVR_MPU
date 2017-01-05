/*
 * GPIO_tools.h
 *
 * Created: 1/4/2017 10:30:30 PM
 *  Author: Zsolt
 */ 


#ifndef GPIO_TOOLS_H_
#define GPIO_TOOLS_H_
//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

//------------------------------------------------
//               DEFINES
//------------------------------------------------
#define LEFT 1
#define RIGHT 3
#define FRONT 2
#define BACK 0

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------
void LEDInit();
void driveLED(uint16_t *xAxis, uint16_t *yAxis);


#endif /* GPIO_TOOLS_H_ */