/*
 * USART_tools.h
 *
 * Created: 12/21/2016 10:47:01 PM
 *  Author: Zsolt
 */ 


#ifndef USART_TOOLS_H_
#define USART_TOOLS_H_
//------------------------------------------------
//               HEADERS
//------------------------------------------------
// USART definitions, AVR Studio libraries
#include <stdlib.h>
#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>
//before including delay.h define CPU frequency
// see the 16MHz oscillator on the Arduino board
#define F_CPU 16000000UL
#include <util/delay.h>

//------------------------------------------------
//               DEFINES
//------------------------------------------------

//define USART baud rate, this value will be identical with the
// baud rate of the COM port in windows with which the Arduino 
// communicates with PC (see Device Manager!!)
#define USART_BAUDRATE 9600  
//calculate from Baud rate the prescaler value for the microcontroller
// baud rate counter (see ATMEGA328 datasheet)
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1) 

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------
void USARTInit();
void USART_char_send(char *c);
void USART_hex_send(uint8_t * h);
void USART_string_send(char *c);
void USART_int_send(uint16_t *i);
ISR(USART_RX_vect);

//------------------------------------------------
//               VARIABLES
//------------------------------------------------
uint8_t USART_ReadByte;

#endif /* USART_TOOLS_H_ */