/*
 * AVR_Gyro.c
 *
 * Created: 12/21/2016 10:44:40 PM
 *  Author: Zsolt
 */ 
//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

// own headers
#include "USART_tools.h"
#include "TWI_tools.h"
#include "MPU6050.h"
#include "GPIO_tools.h"

//------------------------------------------------
//               MAIN
//------------------------------------------------
int main(void)
{
// local variables
	uint8_t TWIReadout;
	uint16_t XAxisValue, YAxisValue;
	uint16_t XOffset, YOffset;
	
// device initializations
	USARTInit(); 
	TWIInit();
	MPU6050Init();
	LEDInit();
//wait after the initialization is done
// it takes time to devices to get working...
	_delay_ms(500);

//calibrating the accelerometer by definig x and y offset
	TWIReadout = MPU6050ReadReg(MPU6050_ACCEL_XOUT_H); // read out accelerometer X axis upper byte
	XAxisValue = TWIReadout << 8;                      // insert into final variable (higher 8bits)
	TWIReadout = MPU6050ReadReg(MPU6050_ACCEL_XOUT_L); // read out accelerometer X axis lower byte
	XAxisValue |= TWIReadout;						   // insert into final variable (lower 8 bits)
	XOffset = -XAxisValue;                             // offset is the negative read out value
	
	TWIReadout = MPU6050ReadReg(MPU6050_ACCEL_YOUT_H); // read out accelerometer Y axis upper byte
	YAxisValue = TWIReadout << 8;					   // insert into final variable (higher 8bits)
	TWIReadout = MPU6050ReadReg(MPU6050_ACCEL_YOUT_L); // read out accelerometer Y axis lower byte
	YAxisValue |= TWIReadout;						   // insert into final variable (lower 8 bits)
	YOffset = -YAxisValue;							   // offset is the negative read out value

// infinite loop in which accelerometer data is read out from registers,
// from each axis the data is merged into one 16 bit value (signed)
// with offset defined abowe the values are compensated
// using driveLED function LEDs are light up depending on values
    while(1)
    {
		TWIReadout = MPU6050ReadReg(MPU6050_ACCEL_XOUT_H); // read out accelerometer X axis upper byte
		XAxisValue = TWIReadout << 8;					   // insert into final variable (higher 8bits)
		TWIReadout = MPU6050ReadReg(MPU6050_ACCEL_XOUT_L); // read out accelerometer X axis lower byte
		XAxisValue |= TWIReadout;						   // insert into final variable (lower 8 bits)
		XAxisValue += XOffset;							   // compensate value with the offset
		USART_int_send(&XAxisValue);                       // print out on USART the value in terminal
		USART_string_send(" | ");
		TWIReadout = MPU6050ReadReg(MPU6050_ACCEL_YOUT_H); // read out accelerometer Y axis upper byte
		YAxisValue = TWIReadout << 8;					   // insert into final variable (higher 8bits)
		TWIReadout = MPU6050ReadReg(MPU6050_ACCEL_YOUT_L); // read out accelerometer Y axis lower byte			                                   
		YAxisValue |= TWIReadout;						   // insert into final variable (lower 8 bits)
		YAxisValue += YOffset;							   // compensate value with the offset
		USART_int_send(&YAxisValue);					   // print out on USART the value in terminal
		USART_string_send(" | ");
		USART_string_send("\n\r");						   // new line
		
		driveLED(&XAxisValue, &YAxisValue);				   // light up LEDs depending on values
		_delay_ms(150);									   // wait 150 ms
    }
}