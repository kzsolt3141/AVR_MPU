/*
 * GPIO_tools.c
 *
 * Created: 1/4/2017 10:32:03 PM
 *  Author: Zsolt
 */ 
//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include "GPIO_tools.h"

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------

//------------------------------------------------
//               void LEDInit()
//------------------------------------------------
// initialize the PORTB to which LEDs are connected
void LEDInit()
{
	DDRB = 0xff;  // set PORTB data direction to OUTPUT
	PORTB = 0x00; // initialize PORTB with 0
}

//------------------------------------------------
//               void driveLED(uint16_t *xAxis, uint16_t *yAxis)
//------------------------------------------------
// get the pointer which points to  X and Y values 
// received from the accelerometer and light up LED 
// depending on the values
void driveLED(uint16_t *xAxis, uint16_t *yAxis)
{
	PORTB = 0x00;                                //initialize PORTB with 0
	if (((*xAxis) > 2000) & ((*xAxis) < 30000))  
	{
		PORTB |= 1 << BACK;
		PORTB &= ~ (1 << FRONT);
	}
		else
		if (((*xAxis) > 30000) & ((*xAxis) < 63535))
	{
		PORTB |= 1 << FRONT;
		PORTB &= ~ (1 << BACK);
	}
	
	if (((*yAxis) > 2000) & ((*yAxis) < 30000))
	{
		PORTB |= 1 << RIGHT;
		PORTB &= ~ (1 << LEFT);
	}
		else
		if (((*yAxis) > 30000) & ((*yAxis) < 63535))
	{
		PORTB |= 1 << LEFT;
		PORTB &= ~ (1 << RIGHT);
	}
}