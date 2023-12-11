/*********************************************************
********* File       ; EEPROM_interface.h **** EEPROM
********* created on : 15/9/2023
********* Author     : Abdullatif Aslam
*********************************************************/

/*********************************************************
*    eeprom_INTERFACE  GIDE                              *
*********************************************************/

#ifndef _SPI_INTERFACE_H_
#define _SPI_INTERFACE_H_

/*********************************************************
*   Functiom definetion                                  *
*********************************************************/

void EEPROM_vidWrite
(
	uint16 u16Adress, 
	uint8 u8Data
);

uint8 EEPROM_vidRead
(
	uint16 u16Adress
);

uint8 EEPROM_Read(uint16 Address);

void EEPROM_Write(uint16 Address, uint8 data);



#endif

/*****************FILE REVISION**************************
********* Auther name ;
********* Abdullatif Aslam      RRW-Q
*********
********* Updated record:
*********
********* 15/9/2023 RRW-Q SY.0 Updated function of EEPROM
*********
*********************************************************/