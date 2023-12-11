#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"


void UART_init(void)
{
	
	  SET_BIT(UCSRB, 3);
	  SET_BIT(UCSRB, 4);
	
	  UCSRC= 0b10000110;
	  
	  
	  //BUAD RATE
	  // from the table to get 9600
	  //if there is more than 255 put it in the UBRRH
	  UBRRL = 103 ;
}


void UART_vidSend(uint8 u8Data)
{
	while(GET_BIT(UCSRA, 5) == 0);
	UDR=u8Data;
}



uint8 UART_u8Receive(void)
{
	while (GET_BIT(UCSRA, 7) == 0) ;
	return UDR;
}

void UART_Send_String (uint8*  pu8DataArray)
{
	uint8 u8Counter = 0;
	
	while (pu8DataArray[u8Counter]!= '\0')
	{
		UART_vidSend(pu8DataArray[u8Counter]);
		u8Counter++;
	}
}

uint8 UART_Correct_Recieve(void)
{
	uint8 u8Pressed;
	uint8 u8Temp;
	
	for (uint8 i = 0 ; i < 3 ; i++ )
	{
		u8Pressed = UART_u8Receive();
		if (i == 0)
		{
			u8Temp = u8Pressed;
		}
		else if (i == 2)
		{
			u8Pressed = u8Temp;
		}
		
	}
	return u8Pressed;
}

void UART_Receive_String (uint8* pu8DataArray)
{
	uint8 received_length = 0; 
	uint8 is_end_of_string  = 0;

	while (received_length < Max_Num - 1 && !is_end_of_string )
	{
	   while (GET_BIT(UCSRA, 7) == 0) ;
	   pu8DataArray[received_length]= UDR;
	   
	   
	    if (pu8DataArray[received_length] == '\n')
	    {
		    is_end_of_string = 1;

	    }
		received_length++;
	}

}
