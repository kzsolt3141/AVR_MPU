/*
 * MPU6050.c
 *
 * Created: 12/24/2016 1:14:32 AM
 *  Author: Zsolt
 */ 

//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include "MPU6050.h"

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------

//------------------------------------------------
//               void MPU6050WriteReg (uint8_t addr, uint8_t data)
//------------------------------------------------
// this function writes a value into a slave's internal register
// for this to happen a series of steps are done in conformity with 
// the MUP6050 datasheet. Steps are listed below.
void MPU6050WriteReg (uint8_t addr, uint8_t data)
{
	uint8_t status;
	TWIStart();                               // send S (Start bit)
	if (TWIGetStatus() != 0x08)               // verify if S was sent
		USART_string_send("S bit error\n\r");
	TWIWrite(MPU6050_I2C_ADDRESS << 1);       // write to the slave address with W (write) condition 
	status = TWIGetStatus();                  // get the status of the transfer
	if (status != 0x18)                       // verify if slave responds to his address
	{
		USART_hex_send(&status);
		USART_string_send(" SLAVE lost\n\r");
	}		
	TWIWrite(addr);                           // send to slave the internal register address which will be written
	status = TWIGetStatus();                  // get the status of the transfer
	if (status != 0x28)						  // verify if the slave responds to the written address with ACK
	{
		USART_hex_send(&status);
		USART_string_send(" internal addr found\n\r");
	}		
	TWIWrite(data);                           // write the internal register with the data
	status = TWIGetStatus();				  // get the status of the transfer
	if (status != 0x28)						  // verify if the slave accepted writted data with ACK
	{
		USART_hex_send(&status);
		USART_string_send(" Data not written\n\r");
	}	
	TWIStop();                                // send P (stop) bit
}

//------------------------------------------------
//               uint8_t MPU6050ReadReg (uint8_t addr)
//------------------------------------------------
// this function reads out a value from a slaves internal register
// it will return that data
// read out an internal register through TWI contains a few steps 
// which are listed below
uint8_t MPU6050ReadReg (uint8_t addr)
{
	uint8_t data, status;
	TWIStart();									  // send S (Start bit)
	if (TWIGetStatus() != 0x08)					  // verify if S was sent
		USART_string_send("S bit error\n\r");
	TWIWrite(MPU6050_I2C_ADDRESS << 1);			  // write to the slave address with W (write) condition
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x18)							  // verify if slave responds to his address
	{
		USART_hex_send(&status);
		USART_string_send(" SLAVE at W lost\n\r");
	}		
	TWIWrite(addr);								  // send to slave the internal register address which will be read
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x28)							  // verify if the slave responds to the written address with ACK
	{
		USART_hex_send(&status);
		USART_string_send(" internal addr lost\n\r");
	}		
	TWIStart();                                   // send a repeated S (start) condition
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x10)							  // verify if the slave responds to the repeated start condition
	{
		USART_hex_send(&status);
		USART_string_send(" repeated start failed\n\r");
	}
	TWIWrite((MPU6050_I2C_ADDRESS << 1) | 1);	  // write to the slave address with R (read) condition
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x40)							  // verify if slave responds to his address
	{
		USART_hex_send(&status);
		USART_string_send(" Slave at R lost\n\r");
	}
	data = TWIReadNACK();						  // read out data from with NACK (only one data will be read out, no need for ACK)
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x58)							  // verify if transfer was OK
	{
		USART_hex_send(&status);
		USART_string_send(" data with NACK lost\n\r");
	}
	TWIStop();                                   // send P (stop) bit
	return data;                                 // return the read out data
}

//------------------------------------------------
//               void MPU6050Init()
//------------------------------------------------
// this function initializes the MPU6050 by writing the devices configuration registers
// see MPU6050 register map document for more information..
void MPU6050Init()
{
	MPU6050WriteReg(MPU6050_PWR_MGMT_1, 0x80);  // reset device
	MPU6050WriteReg(MPU6050_SMPLRT_DIV, 0x08);  // set sample rate to 1kHz by dividing sample rate with 8
	MPU6050WriteReg(MPU6050_CONFIG, 0x06);      // set the highest low pass filter DLPCGF 6
	MPU6050WriteReg(MPU6050_GYRO_CONFIG, 0x08); // set gyro range to 500 degrees/s
	MPU6050WriteReg(MPU6050_ACCEL_CONFIG, 0x08);// set accelero range to 4g
	MPU6050WriteReg(MPU6050_PWR_MGMT_1, 0x00);  // disable reset condition
	MPU6050WriteReg(MPU6050_PWR_MGMT_1, 0x08);  // disable temperature
	MPU6050WriteReg(MPU6050_PWR_MGMT_2, 0x00);  // enable all the axis on gyro and accelerometer
}