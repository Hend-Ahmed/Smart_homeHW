#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "KEYPAD_interface.h"
#include "KEYPAD_config.h"
#include "KEYPAD_private.h"

void KEYPAD_vid_Init (void) 
{
	/* Set columns pins direction as output */ 
	DIO_udtSetPinDirection(KEYPAD_Column_PORT, KEYPAD_C0_PIN, DIO_OUTPUT);
	DIO_udtSetPinDirection(KEYPAD_Column_PORT, KEYPAD_C1_PIN, DIO_OUTPUT);
	DIO_udtSetPinDirection(KEYPAD_Column_PORT, KEYPAD_C2_PIN, DIO_OUTPUT);
	DIO_udtSetPinDirection(KEYPAD_Column_PORT, KEYPAD_C3_PIN, DIO_OUTPUT);
	
	/* Set columns pins value as low */
	DIO_udtSetPinValue(KEYPAD_Column_PORT, KEYPAD_C0_PIN, DIO_HIGH); // was low    // set according to pull-up or pull-down resistors 
	DIO_udtSetPinValue(KEYPAD_Column_PORT, KEYPAD_C1_PIN, DIO_HIGH);
	DIO_udtSetPinValue(KEYPAD_Column_PORT, KEYPAD_C2_PIN, DIO_HIGH);
	DIO_udtSetPinValue(KEYPAD_Column_PORT, KEYPAD_C3_PIN, DIO_HIGH);
	
	/* Set rows pins direction as input */ 
	DIO_udtSetPinDirection(KEYPAD_Row_PORT, KEYPAD_R0_PIN, DIO_INPUT); 
	DIO_udtSetPinDirection(KEYPAD_Row_PORT, KEYPAD_R1_PIN, DIO_INPUT); 
	DIO_udtSetPinDirection(KEYPAD_Row_PORT, KEYPAD_R2_PIN, DIO_INPUT); 
	DIO_udtSetPinDirection(KEYPAD_Row_PORT, KEYPAD_R3_PIN, DIO_INPUT); 
	
	/* Set rows pins value as low */
	DIO_udtSetPinValue(KEYPAD_Row_PORT, KEYPAD_R0_PIN, DIO_HIGH);	//was high    // set according to pull-up or pull-down resistors 
	DIO_udtSetPinValue(KEYPAD_Row_PORT, KEYPAD_R1_PIN, DIO_HIGH);
	DIO_udtSetPinValue(KEYPAD_Row_PORT, KEYPAD_R2_PIN, DIO_HIGH);
	DIO_udtSetPinValue(KEYPAD_Row_PORT, KEYPAD_R3_PIN, DIO_HIGH);
}




uint8 KEYPAD_u8GetPressedKey(void) 
{
	uint8 u8ColumnID, u8RowID;
	
	uint8 u8PinState ;
	
	uint8 u8PressedKey = KEYPAD_NO_PRESSED_KEY ;
	
	uint8 u8KeypadMatrix[ROW_NUM][COL_NUM] = KPD_BUTTONS ;
	
	uint8 u8KpdColumns [COL_NUM] = {KEYPAD_C0_PIN, KEYPAD_C1_PIN, KEYPAD_C2_PIN, KEYPAD_C3_PIN}  ;
	uint8 u8KpdRows [ROW_NUM]	 = {KEYPAD_R0_PIN, KEYPAD_R1_PIN, KEYPAD_R2_PIN, KEYPAD_R3_PIN}  ;
	
	/* iterate on the columns to get the pressed button */
	for (u8ColumnID = 0u; u8ColumnID < COL_NUM; u8ColumnID++)
	{
		/* Enable column X*/
		DIO_udtSetPinValue(KEYPAD_Column_PORT, u8KpdColumns[u8ColumnID], DIO_LOW); // was low
		
		/* iterate on the rows to get the pressed button */		
		for (u8RowID = 0u; u8RowID < ROW_NUM; u8RowID++)
		{

			/* read row y*/			
			DIO_udtGetPinValue(KEYPAD_Row_PORT, u8KpdRows[u8RowID], &u8PinState) ;
			
			/* if row pin value is low y*/			
			if (u8PinState == DIO_LOW) // was low
			{
				/* key is found store value in variable*/
				u8PressedKey = u8KeypadMatrix[u8RowID][u8ColumnID] ;
 
 				while(u8PinState == DIO_LOW) //was low // to check if value is still pushed
 				{
 					DIO_udtGetPinValue(KEYPAD_Row_PORT, u8KpdRows[u8RowID], &u8PinState) ;
 				}
 				return u8PressedKey;
 			} 
			else{}
		}
		
		/* disable column */
		DIO_udtSetPinValue(KEYPAD_Column_PORT, u8KpdColumns[u8ColumnID], DIO_HIGH) ; // was high
	}
	return u8PressedKey;
}

uint8 KEYPAD_KEY (void)
{
uint8 u8Pressed;
u8Pressed = 0XFF;
while(u8Pressed == 0xff)
   {			
	u8Pressed = KEYPAD_u8GetPressedKey();
   }
   
   return u8Pressed ;
}

