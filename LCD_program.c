#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define F_CPU 16000000UL
#include "util/delay.h"

#include "DIO_interface.h"
#include "DIO_private.h"

#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"

Std_ReturnType LCD_udtSendCommand
(
uint8 u8Command
)
{
	Std_ReturnType udtReturnValue = E_OK;
	
	/* !Comment: Clearing RS pin to send command */
	DIO_udtSetPinValue(LCD_RS, DIO_LOW);
	
	/* !Comment: Clearing RW pin to write */
	DIO_udtSetPinValue(LCD_RW, DIO_LOW);
	
	/* !Comment: Write data on the data port */
	LCD_DATA_PORT &= 0x0F;                // Make the higher bits zero ''old command''
	LCD_DATA_PORT |= u8Command & 0xF0;    // Maintain the lower bits
	
	/* !Comment: Enable pulse */
	DIO_udtSetPinValue(LCD_E, DIO_HIGH);
	_delay_us(10);
	DIO_udtSetPinValue(LCD_E, DIO_LOW);
	
	_delay_us(100);
	
	/* !Comment: Write data on the data port */
	LCD_DATA_PORT = u8Command << 4;
	
	/* !Comment: Enable pulse */
	DIO_udtSetPinValue(LCD_E, DIO_HIGH);
	_delay_us(10);
	DIO_udtSetPinValue(LCD_E, DIO_LOW);
	
	_delay_us(100);
	
	return udtReturnValue;
}


void LCD_vidInit
(
void
)
{
	LCD_DATA_DIRECTION = 0xFF;
	
	DIO_udtSetPinDirection(LCD_RS, DIO_OUTPUT);
	DIO_udtSetPinDirection(LCD_RW, DIO_OUTPUT);
	DIO_udtSetPinDirection(LCD_E, DIO_OUTPUT);
	
	_delay_ms(40);
	
	/* !Comment: Function set */
	LCD_udtSendCommand(0x33);
	LCD_udtSendCommand(0x32);
	LCD_udtSendCommand(0x28);
	_delay_ms(1);
	
	/* !Comment: Display off */
	LCD_udtSendCommand(0x0C);
	_delay_ms(1);
	
	/* !Comment: Display clear */
	LCD_udtSendCommand(0x01);
	_delay_ms(2);
	
	/* !Comment: Entry mode */
	LCD_udtSendCommand(0x02);
	
}

Std_ReturnType LCD_udtSendData
(
uint8 u8Data
)
{
	Std_ReturnType udtReturnValue = E_OK;
	
	
	/* !Comment: Clearing RS pin to send command */
	DIO_udtSetPinValue(LCD_RS, DIO_HIGH);
	
	/* !Comment: Clearing RW pin to write */
	DIO_udtSetPinValue(LCD_RW, DIO_LOW);
	
	/* !Comment: Write data on the data port */
	LCD_DATA_PORT = u8Data & 0xF0;
	
	/* !Comment: Enable pulse */
	DIO_udtSetPinValue(LCD_E, DIO_HIGH);
	_delay_us(10);
	DIO_udtSetPinValue(LCD_E, DIO_LOW);
	
	_delay_us(100);
	
	/* !Comment: Write data on the data port */
	LCD_DATA_PORT = u8Data << 4;
	
	/* !Comment: Enable pulse */
	DIO_udtSetPinValue(LCD_E, DIO_HIGH);
	_delay_us(10);
	DIO_udtSetPinValue(LCD_E, DIO_LOW);
	
	_delay_us(100);
	
	return udtReturnValue;
	
}

Std_ReturnType LCD_udtPrintData
(
uint8*  pu8DataArray
)
{
	Std_ReturnType udtReturnValue = E_OK;
	uint8 u8Counter = 0;
	
	while (pu8DataArray[u8Counter]!= '\0')
	{
		LCD_udtSendData(pu8DataArray[u8Counter]);
		u8Counter++;
	}
	return udtReturnValue;
}

void LCD_vidGoTo
(
uint8 u8Row,
uint8 u8Column

)
{
	if (u8Row == 0)
	{
		LCD_udtSendCommand(u8Column + 128);
	}
	else
	{
		LCD_udtSendCommand((u8Column + 0x40) + 128);
	}
	
}

void LCD_vidSpecialChar
(
uint8*  pu8Arr,
uint8  u8CGRAMLocation,
uint8  u8DDRAM_Row,
uint8  u8DDRAM_Column
)
{
	uint8 u8Counter;
	
	LCD_udtSendCommand(u8CGRAMLocation*8 + 64);
	
	/* Write on CGRAM */
	for (u8Counter=0; u8Counter<8; u8Counter++)
	{
		LCD_udtSendData(pu8Arr[u8Counter]);
	}
	
	/* Go bacl to DDRAM */
	LCD_vidGoTo(u8DDRAM_Row, u8DDRAM_Column);
	
	/* Print CGRAM location u8CGRAMLocation data  */
	LCD_udtSendData(u8CGRAMLocation);
}
void LCD_Clear (void)
{
	LCD_udtSendCommand(0x01);
	_delay_ms(500);
}


