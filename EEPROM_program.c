/*********************************************************
********* File       ; EEPROM_program.c **** program
********* created on : 15/9/2023
********* Author     : Abdullatif Aslam
*********************************************************/

/*********************************************************
*    LAIBRARY INCLUDE                                    *
*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EEPROM_private.h"
#include "EEPROM_interface.h"

#define EEPROM_Write_Addess		0xA0
#define EEPROM_Read_Addess		0xA1
#define SCL_CLK					400000

#include "TIMER_interface.h"
/*********************************************************
*    FUNCTION OF EEPROM                                  *
*********************************************************/

void EEPROM_vidWrite
(
	uint16 u16Adress, 
	uint8 u8Data
)
{
	while(GET_BIT(EECR, 1)!= 0);
	
	EEAR = u16Adress;	
	EEDR = u8Data;
	
	SET_BIT(EECR,2);
	SET_BIT(EECR,1);		
}

uint8 EEPROM_vidRead
(
	uint16 u16Adress
)
{
	
    while(GET_BIT(EECR, 1)!= 0);
	
	EEAR = u16Adress;
	
	SET_BIT(EECR,0);
	
	return EEDR;
}

void EEPROM_Write(uint16 Address, uint8 data)
{
	I2C_Start(EEPROM_Write_Addess);/* Start I2C with device write address */
	I2C_Write(Address);		/* Write start memory address for data write */	
	I2C_Write(data);
	I2C_Stop();			/* Stop I2C */
	vidDelay_ms(10);
}

uint8 EEPROM_Read(uint16 Address)
{
	uint8 data =0;
	I2C_Start(EEPROM_Write_Addess);/* Start I2C with device write address */
	I2C_Write(Address);		/* Write start memory address */
	I2C_Repeated_Start(EEPROM_Read_Addess);/* Repeat start I2C SLA+R */
	
	data = I2C_Read_Ack();
		//LCD_udtSendData(I2C_Read_Ack());
	I2C_Read_Nack();		/* Read flush data with nack */
	I2C_Stop();			/* Stop I2C */
	return data ;
}
