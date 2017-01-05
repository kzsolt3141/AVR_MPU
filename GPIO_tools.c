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
	if (((*xAxis) > MIN_POS_VAL) & ((*xAxis) < MAX_POS_VAL))     //xAxis points to a positive value
	{															 
		PORTB |= 1 << BACK;                                      // light up BACK  LED
		PORTB &= ~ (1 << FRONT);                                 // turn off FRONT LED
	}
		else
		if (((*xAxis) > MIN_NEG_VAL) & ((*xAxis) < MAX_NEG_VAL)) //xAxis points to a negative value
	{
		PORTB |= 1 << FRONT;									 // light up FRONT  LED
		PORTB &= ~ (1 << BACK);									 // turn off BACK LED
	}
	
	if (((*yAxis) > MIN_POS_VAL) & ((*yAxis) < MAX_POS_VAL))	 //yAxis points to a positive value
	{
		PORTB |= 1 << RIGHT;									 // light up RIGHT  LED
		PORTB &= ~ (1 << LEFT);									 // turn off LEFT LED
	}
		else
		if (((*yAxis) > MIN_NEG_VAL) & ((*yAxis) < MAX_NEG_VAL)) //yAxis points to a negative value
	{
		PORTB |= 1 << LEFT;										 // light up LEFT  LED
		PORTB &= ~ (1 << RIGHT);								 // turn off RIGHT LED
	}
}