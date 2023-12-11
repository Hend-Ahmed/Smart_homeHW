#define F_CPU 16000000UL

#include <util/delay.h>
#include <string.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"

#include "EEPROM_interface.h"
#include "EEPROM_private.h"

#include "TIMER_B_interface.h"
#include "TIMER_B_private.h"

#include "Smart_interface.h"
#include "Smart_private.h"

#include "LCD_interface.h"
#include "LCD_private.h"

#include "UART_interface.h"
#include "UART_private.h"

#include "TIMER_interface.h"
#include "TIMER_private.h"

#include "ADC_interface.h"
#include "ADC_private.h"

#include "I2C_interface.h"
#include "I2C_private.h"



/*!Comment: Variables declaration*/
Login_Data u1[Max_Num] = {0};
uint8 Admin_Flag;
uint8 Buffer_1[10];
uint8 Buffer_2[10];
uint8 Arr_User[10]={0};
uint8 Arr_Pass [10]={0};
uint8 User_Taken=0;
uint16 Pass_Taken=0;
uint8 Door_flag = 0;
uint8 Return_Flag = 0;
uint16 Pass_Buffer;
uint8 Check=0;
uint8 Check_2;
uint8 static ErrorState = 0;
uint16 static u16location = 0x0000;
uint8 static Num = 0;
uint8 static u8Priority = 0;
uint8 static u8NumUser = 0;


/*!Comment: Function convert int to string*/
void int_to_string(int number, char* buffer)
{
	if (number == 0) {
		buffer[0] = '0';
		buffer[1] = '\0';
		return;
	}

	int i = 0;
	int is_negative = 0;

	if (number < 0)
	{
		is_negative = 1;
		number = -number;
	}

	while (number != 0)
	{
		int digit = number % 10;
		buffer[i++] = '0' + digit;
		number /= 10;
	}

	if (is_negative)
	{
		buffer[i++] = '-';
	}

	buffer[i] = '\0';

	// Reverse the string
	int start = 0;
	int end = i - 1;
	while (start < end)
	{
		char temp = buffer[start];
		buffer[start] = buffer[end];
		buffer[end] = temp;
		start++;
		end--;
	}
} // End Func

/*!Comment: Function for EXINT of Keypad */
void KeyPadSelect(void)
{   
	uint8 static counter = 0;
    
	if (counter == 0)
	{
		counter ++;
	    u8Priority = 1;
	    LCD_Clear();
	    LCD_udtPrintData("NOW USING KEYPAD");
	    _delay_ms(1000);
	    LCD_Clear();
	}
	
	GIE_vidDisableGlobalInterrupt();
} // End Func

/*!Comment: Function to know if user using Keypad or UART */
uint8 Priority_Select (void)
{
	uint8 u8Press ;
	
	if (u8Priority==0)
	{
		if(Return_Flag==1)
		{
			Return_Flag = 0;
		}
		u8Press = UART_Correct_Recieve();
	}
	else if (u8Priority==1)
	{
		u8Press = KEYPAD_KEY();
	}
	
	return u8Press;
} // End Func

/*!Comment: Function to know correct address of username in EEPROM */
uint16 Correct_Address (uint8 Username)
{
	uint8 i = 0;
	for (i = 0 ; i<10 ; i++)
	{
		if (u1[i].Name==Username)
		{
			break;
		}
	}
	return u1[i].Name_Address;
} // End Func

/*!Comment: Function to check & store users added every start of the system (Power Off) */
void vid_If_User_Added (void)
{
	uint8 i = 0;
	for (i = 0; i<30 ; i+=3)
	{
		if (EEPROM_Read(i)==0xFF)
		{
			continue;
		}
		else if (EEPROM_Read(i)!=0xFF)
		{
			u1[u8NumUser].Name = EEPROM_Read(i);
			u1[u8NumUser].Name_Address = i;
			u8NumUser++;
			u16location+=3;
			
		}
	} // End For
	
} // End Func

/*!Comment: Function to add user to the system (EEPROM) */
void vidAdd_User (uint8 Username)
{
	for (Num = 0 ; Num<30 ; Num++)
	{
		if (EEPROM_Read(Num)==0xFF)
		{
			EEPROM_Write(Num, Username);
			u1[u8NumUser].Name = Username;
			u1[u8NumUser].Name_Address= Num;
			u16location= Num;
			u8NumUser++;
			break;
		}
	} // End For
	
} // End Func

/*!Comment: Function to add password of user to the system (EEPROM) */
void vidAdd_Pass (uint16 password)
{
	uint16 EEPROM_Pass;
	
	/*!Comment: Storing 16 bit value in 2 8-bit-location */
	EEPROM_Pass = password & 0xFF00;
	EEPROM_Pass = EEPROM_Pass >> 8;
	
	EEPROM_Write(u16location+1, (uint8)EEPROM_Pass);
	EEPROM_Write(u16location+2,(uint8)password);
	
	u16location+=3;
} // End Func

/*!Comment: Function to remove user from the system (EEPROM) */
void vidRemove_User(uint8 Username)
{
	uint16 Address;
	uint8 i;
	Address = Correct_Address (Username);
	
	/*!Comment: Loop to remove all data of user */
	for (i=0; i<3; i++)
	{
		EEPROM_Write(Address+i, 0xFF);
	} // End For
	
} // End Func

/*!Comment: Function to fire alarm and system break down after 3 wrong login */
void IsLoginCorrect(uint8 State)
{
	DIO_udtSetPinDirection(DIO_PORTA,DIO_PIN3,DIO_OUTPUT);
	uint8 static Counter = 0;
	State = ErrorState;
	if(ErrorState == 0)
	{
		Counter++;
		if(Counter == 3)
		{
			Counter = 0;
			
			/*!Comment: Buzzer On for 2 Seconds*/
			DIO_udtSetPinValue(DIO_PORTA,DIO_PIN3,DIO_HIGH);
			vidDelay_ms(2000);
			DIO_udtSetPinValue(DIO_PORTA,DIO_PIN3,DIO_LOW);
			
			if (u8Priority == 0)
			{
				UART_Send_String("PLEASE RESET THE SYSTEM \n");
			}
			
			LCD_Clear();
			LCD_udtPrintData("PLEASE RESET");
			LCD_vidGoTo(1,0);
			LCD_udtPrintData("THE SYSTEM");
			
			/*!Comment: System must be Reset*/
			while (1);
		}
	}
} // End Func

/*!Comment: Function to interface in add/remove users */
void vidAddRemove(uint8 u8pressed)
{
	uint8 Username;
	uint8 user_take = 0;
	uint16 Password;
	uint16 Pass_take = 0;
	uint8 u8Loop = 0;
	uint8 i=0;

	while(u8Loop == 0)
	{
		if (u8Priority==0)
		{
			UART_Send_String("1:Add User\n");
			UART_Send_String("2:Remove User\n");
			UART_Send_String("0:Exit");
		}
		LCD_Clear();
		LCD_udtPrintData("1:Add 2:Remove");
		LCD_vidGoTo(1,0);
		LCD_udtPrintData("0:Exit");
		
		u8pressed = Priority_Select();
		switch(u8pressed)
		{
			case'1':	/*!Comment: Add User*/
				if (u8Priority==0)
				{
					UART_Send_String("USERNAME:       PASSWORD:      ");	
				}
				LCD_Clear();
				LCD_udtPrintData("USERNAME: ");
				LCD_vidGoTo(1,0);
				LCD_udtPrintData("PASSWORD: ");
				LCD_vidGoTo(0,10);
				
				/*!Comment: Username Storing from KEYPAD or UART */
				if (u8Priority == 0)
				{
					UART_Receive_String(Buffer_1);
					for (uint8 i = 0 ; i < 3 ; i++)
					{
						vidDelay_ms(100);
						if (Buffer_1[i]=='\n'|| Buffer_1[i] == '\r')
						{
						Buffer_1[i] = NULL;
						break;
						}
							
						if (i==0)
						{
							user_take =  Buffer_1[i]- '7';
							user_take = user_take << 4;
						}
						else
						{
							user_take |=  Buffer_1[i] - '0';
						}
						LCD_udtSendData(Buffer_1[i]);
						
					} // End For
				}
				else if ( u8Priority == 1)
				{
					for (i = 0; i <2 ;i++ )
					{
						Arr_User[i]= KEYPAD_KEY();
						LCD_udtSendData(Arr_User[i]);
						vidDelay_ms(100);
						if (i==0)
						{
							user_take = Arr_User[i]- '7';
							user_take = user_take << 4;
						}
						else
						{
							user_take |= Arr_User[i] - '0';
						}
					} // End For
				}
				Username = user_take;
				user_take = 0;
				vidAdd_User(Username);
					
				LCD_vidGoTo(1,10);
				/*!Comment: Password Storing from KEYPAD or UART */
				if ( u8Priority == 0)
				{
					UART_Receive_String(Buffer_2);
					//	  LCD_udtPrintData(Buffer);
				
				/*!Comment: Loop to break when i receive \r on UART*/
				for (i = 0; i <6 ;i++)
				{
					vidDelay_ms(100);
					if (Buffer_2[i] == '\r')
					{
						break;
					}
					LCD_udtSendData(Buffer_2[i]);
					
					/*!Comment: Convert string of char(Pass) into an equivalent integer */
					Pass_take = (Pass_take* 10) + (Buffer_2[i] - '0');
					}
				} // End For
				else if ( u8Priority == 1)
				{
					for (i = 0; i <5 ;i++ )
					{
						Arr_Pass[i]= Priority_Select();
						LCD_udtSendData(Arr_Pass[i]);
						Pass_take = (Pass_take* 10) + (Arr_Pass[i] - '0');
						vidDelay_ms(100);
					} // End For
				}
				Password = Pass_take;
				Pass_take = 0;
				vidAdd_Pass(Password);
				if (u8Priority==0)
				{
					UART_Send_String("Successfully Added \n");	
				}
				LCD_Clear();
				LCD_vidGoTo(0,2);
				LCD_udtPrintData("Successfully");
				LCD_vidGoTo(1,5);
				LCD_udtPrintData("Added");
				break;
				
			case'2':	/*!Comment: Remove User*/
				if (u8Priority==0)
					{
						UART_Send_String("USERNAME:       ");
					}
					LCD_udtPrintData("USERNAME: ");
					LCD_vidGoTo(1,0);

					/*!Comment: Username Storing from KEYPAD or UART */
					if (u8Priority == 0)
					{
						UART_Receive_String(Buffer_1);
						for (i = 0 ; i < 3 ; i++)
						{
							vidDelay_ms(100);
							if (Buffer_1[i]=='\n'|| Buffer_1[i] == '\r')
							{
								Buffer_1[i] = NULL;
								break;
							}
							
							if (i==0)
							{
								user_take =  Buffer_1[i]- '7';
								user_take = user_take << 4;
							}
							else
							{
								user_take |=  Buffer_1[i] - '0';
							}
							
							LCD_udtSendData(Buffer_1[i]);
						} // End For
					}
					else if (u8Priority == 1)
					{
						for (i = 0; i <2 ;i++ )
						{
							Arr_User[i]= KEYPAD_KEY();
							LCD_udtSendData(Arr_User[i]);
							vidDelay_ms(100);
							if (i==0)
							{
								user_take = Arr_User[i]- '7';
								user_take = user_take << 4;
							}
							else
							{
								user_take |= Arr_User[i] - '0';
							}
						}//for
					}
					Username = user_take;
					user_take = 0;
					/*!Comment: Remove the user with it's username*/
					vidRemove_User(Username);
					if (u8Priority==0)
					{
						UART_Send_String("Successfully Removed \n");
					}
					LCD_Clear();
					LCD_vidGoTo(0,2);
					LCD_udtPrintData("Successfully");
					LCD_vidGoTo(1,4);
					LCD_udtPrintData("Removed");
					break;
					
				case'0':	//Exit
					u8Loop = 1;
					break;
				default:
					if (u8Priority==0)
					{
						UART_Send_String("WRONG INPUT ");
					}
					LCD_Clear();
					LCD_udtPrintData("WRONG INPUT");
					vidDelay_ms(1000);
					break;
		} // End Switch
	} // End While
} // End Func

/*!Comment: Function to login the system */
void Smart_Login_Step (void)
{
	uint8 i = 0;
	uint8 u8Pressed;
	
	Pass_Taken = 0;
	User_Taken = 0;
	Pass_Buffer = 0;
	
	if (Door_flag == 2)
	{
		u8Priority = 0;
	}
	LCD_Clear();
	LCD_udtPrintData("PRESS # WHEN");
	LCD_vidGoTo(1,0);
	LCD_udtPrintData("FINISHED");
	_delay_ms(1500);
	LCD_Clear();
	
	UART_Send_String("USERNAME:       PASSWORD:      ");
	LCD_udtPrintData("USERNAME: ");
	LCD_vidGoTo(1,0);
	LCD_udtPrintData("PASSWORD: ");
	LCD_vidGoTo(0,10);
	
	/*!Comment: Username Storing from KEYPAD or UART */
	if (u8Priority == 0)
	{
		UART_Receive_String(Buffer_1);
		for (i = 0 ; i < 3 ; i++)
		{
			vidDelay_ms(100);
       		
			if (Buffer_1[i]=='\n'|| Buffer_1[i] == '\r')
       		{
       			Buffer_1[i] = NULL;
       			break;
       		}
       	  
       		if (i==0)
       		{
       			User_Taken =  Buffer_1[i]- '7';
       			User_Taken = User_Taken << 4;
       		}
       		else
       		{
       			User_Taken |=  Buffer_1[i] - '0';
       		}
			   
       		LCD_udtSendData(Buffer_1[i]);
			
		} // End For
	}
	else if (u8Priority == 1)
	{
		for (i = 0; i <2 ;i++)
		{
			Arr_User[i]= KEYPAD_KEY();
       		LCD_udtSendData(Arr_User[i]);
       		vidDelay_ms(100);
       		
			if (i==0)
       		{
       			User_Taken = Arr_User[i]- '7';
       			User_Taken = User_Taken << 4;
       		}
       		else
       		{
       			User_Taken |= Arr_User[i] - '0';
       		}
    
         } //End For
	}
	
	LCD_vidGoTo(1,10);
	
	/*!Comment: Password Storing from KEYPAD or UART */
	if (u8Priority == 0)
	{
		UART_Receive_String(Buffer_2);
        for (i = 0; i <6 ;i++)
        {
       		vidDelay_ms(100);
       		if (Buffer_2[i] == '\r')
       		{
				break;
       		}
       		LCD_udtPrintData("*");
       		Pass_Taken = (Pass_Taken* 10) + (Buffer_2[i] - '0'); 
        } // End For
	}
    else if (u8Priority == 1)
    {
		for (i = 0; i <5 ;i++ )
		{
			Arr_Pass[i] = KEYPAD_KEY();
			LCD_udtPrintData("*");
			Pass_Taken = (Pass_Taken* 10) + (Arr_Pass[i] - '0');
			vidDelay_ms(100);
		} // End For
	}
	
	u8Pressed = Priority_Select();
	
	if (u8Pressed == '#')
	{
		Check = 0;
		LCD_Clear();	
		
		uint8 User = EEPROM_Read(Correct_Address(User_Taken));
		/*!Comment: Admin Flag */
		if(Admin_Flag == 1)		//If Admin
		{
			if(User != 160)	//A0
				Check_2 = 0;	//Guest is User
			else
				Check_2 = 1;	//Guest is Admin 
		}
		else if(Admin_Flag == 0)	//If user
		{
			if(User == 160)
			{
				if(Door_flag == 2)
				
					Check_2 = 1;
				else	
					Check_2 = 0;	//Guest is Admin 
			}
			else 
				Check_2 = 1;	//Guest is User
		}
		
		uint8 EEPROM_intvalue;
		uint8 KEYPAD_intvalue;
		
		LCD_Clear();
		LCD_udtSendData(User_Taken);
		
		if(Check_2 == 1)
		{
			if (User == User_Taken)
			{
				Check = 1;
				Check = Check + '0' ;
				LCD_Clear();
			}
		      /////////////////////////////////
			Pass_Buffer = EEPROM_Read(Correct_Address(User_Taken)+1);
			Pass_Buffer = Pass_Buffer << 8;
			Pass_Buffer |= EEPROM_Read(Correct_Address(User_Taken)+2);
			
			if (Pass_Buffer == Pass_Taken)
			{
				Pass_Buffer = 0;  
				Check += 1;
				Check = Check - '0' ;
				Pass_Taken = 0;
			}
			/////////////////////////////////
			if (Check == 2)
			{
				ErrorState = 1;
				LCD_Clear();
				if (Door_flag == 2)
				{
					if (u8Priority == 0)
					{
						UART_Send_String("ACCEPT DOOR OPEN \n1:YES   2:NO");
					}
					LCD_Clear();
					LCD_udtPrintData("ACCEPT DOOR OPEN");
					LCD_vidGoTo(1,0);
					LCD_udtPrintData("1:YES   2:NO");
					
					u8Pressed = Priority_Select();
					
					if (u8Pressed == '1')
					{
						Door_flag = 1;
					} 
					else if (u8Pressed == '2')
					{
						Door_flag = 0;
					}  
				}
				LCD_Clear();
				LCD_udtPrintData("LOGIN ACCEPTED  ");
				vidDelay_ms(1000);
				if (u8Priority == 0)
				{
					UART_Send_String("LOGIN ACCEPTED\n");
				} 
			}
			else if (Check !=2)
			{
				ErrorState = 0;
				LCD_Clear();
				LCD_udtPrintData("LOGIN DENIED");
				vidDelay_ms(1000);
				
				
			    if (u8Priority == 0)
			    {
					UART_Send_String("LOGIN DENIED\n");
			    }
				
			}
		}
		else if(Check_2 != 1)	
		{
			LCD_Clear();
			LCD_udtPrintData("LOGIN DENIED");
			vidDelay_ms(1000);
			ErrorState = 0;
			
			if (u8Priority == 0)
			{
			   UART_Send_String("LOGIN DENIED\n");
			}
		}    
	}     
} // End Func

/*!Comment: Function for dimming circuit */
void vidLEDBrightnessControl(void)
{ 
  
	uint8 u8Duty = 0;
	uint8 u8Flag = 0;
	TIMER_B_PWMInit();
	
	if (u8Priority==0)
	{
		UART_Send_String("Please Choose Mode\n");
	}
	LCD_vidGoTo(0,2);  
	LCD_udtPrintData("Please Choose");
	LCD_vidGoTo(1,6);
	LCD_udtPrintData("Mode");
  
	vidDelay_ms(1000);
	LCD_Clear();
	while(u8Flag == 0)
    {
		if (u8Priority==0)
		{
			UART_Send_String("To Exit Press 0\n1:OFF\n2:Saving\n3:Normal\n4:Full\n");
		}
		LCD_udtPrintData("To Exit Press 0");
		vidDelay_ms(1000);
		LCD_Clear();
		LCD_udtPrintData("1:OFF 2:Saving");
		LCD_vidGoTo(1,0);
		LCD_udtPrintData("3:Normal 4:Full");

		uint8 u8Recieved = Priority_Select();

		switch(u8Recieved)
		{
	        case '1':	/*!Comment: OFF Mode*/ 
				while(OCR1A != 0)
				{
					OCR1A-=1;
					vidDelay_ms(20);
				}
				vidDelay_ms(500);
				LCD_Clear();
				break;
	        
			case '2':	/*!Comment: Saving Mode */
				for(u8Duty = 0; u8Duty < 30; u8Duty++)
				{
					OCR1A=u8Duty;  /*increase the LED light intensity*/
					vidDelay_ms(20);
				}
				vidDelay_ms(500);
				LCD_Clear();
				break;
				
	        case '3':	/*!Comment: Normal Mode */
				for(u8Duty = 0; u8Duty < 100; u8Duty++)
				{
					OCR1A=u8Duty;  /*increase the LED light intensity*/
					vidDelay_ms(20);
				}
				vidDelay_ms(500);
				LCD_Clear();
				break;
				
	        case '4':	/*!Comment: Full Mode */
				for(u8Duty = 0; u8Duty<255; u8Duty++)
				{
					OCR1A=u8Duty;  /*increase the LED light intensity*/
					vidDelay_ms(20);
				}
				vidDelay_ms(500);
				LCD_Clear();
				break;
			  
	        case '0':	/*!Comment: Exit */
				u8Flag = 1;
				break;
			  
			default:
				if (u8Priority==0)
				{
					UART_Send_String("Wrong Input\n");
				}
				LCD_Clear();
				LCD_udtPrintData("Wrong Input");
				vidDelay_ms(1000);
				LCD_Clear();
				break;
			
		} // End Switch
		
		if(u8Flag == 1)
        break;
		
    } // End While
} // End Func

/*!Comment: Function to control light */
void vidLEDControl(void)
{
	DIO_udtSetPinDirection(DIO_PORTC,DIO_PIN2,DIO_OUTPUT);
	DIO_udtSetPinDirection(DIO_PORTC,DIO_PIN7,DIO_OUTPUT);
	
	uint8 u8Flag = 0;
	uint8 u8room;
	
	LCD_Clear();
	
	if (u8Priority==0)
	{
		UART_Send_String("Choose LED To Turn ON/OFF\n");
	}
	LCD_udtPrintData("Choose LED To");
	LCD_vidGoTo(1,0);
	LCD_udtPrintData("Turn ON/OFF");
	vidDelay_ms(1000);
	LCD_Clear();
	
	while(u8Flag == 0)
	{
		if (u8Priority==0)
		{
			UART_Send_String("To Exit Press 0\n1-Bedroom\n2-Living1\n3->\n");
		}
		LCD_udtPrintData("To Exit Press 0");
		vidDelay_ms(1000);
		LCD_Clear();
		LCD_udtPrintData("1-Bedroom ");  
		LCD_vidGoTo(1,0);
		LCD_udtPrintData("2-Living1 3->"); 

		 u8room = Priority_Select ();
		 
		/*!Comment: List more options */
		if(u8room == '3')
		{
		    if (u8Priority==0)
		    {
			    UART_Send_String("4-Living2\n5-Bathroom\n6->\n");
		    }
			LCD_Clear();
			LCD_udtPrintData("4-Living2"); //9
			LCD_vidGoTo(1,0);
			LCD_udtPrintData("5-Bathroom 6->"); //14
			u8room = Priority_Select ();
			
			/*!Comment: List more options */
			if(u8room == '6')
			{
				if (u8Priority==0)
				{
					UART_Send_String("7-Control1\n8-Control2\n");
				}
				LCD_Clear();
				LCD_udtPrintData("7-Control1"); 
				LCD_vidGoTo(1,0);
				LCD_udtPrintData("8-Control2");
				
				u8room = Priority_Select ();
			}
		}
		
		uint8 u8Choice = u8room;
		
		switch(u8Choice)
		{
			case '1':	/*!Comment: Bedroom */
				TOG_BIT(PORTD, DIO_PIN3);
				LCD_Clear();
				break;
				
			case '2':	/*!Comment: Living room 1 */
				TOG_BIT(PORTD, DIO_PIN6);
				LCD_Clear();
				break;
			
			case '4':	/*!Comment: Living room 2 */
				TOG_BIT(PORTB, DIO_PIN0);
				LCD_Clear();
				break;
			
			case '5':	/*!Comment: Bathroom */
				TOG_BIT(PORTC, DIO_PIN2);
				LCD_Clear();
				break;
			
			case '7':	/*!Comment: Control room 1*/
				TOG_BIT(PORTC, DIO_PIN7);
				LCD_Clear();
				break;
			
			case '8':	/*!Comment: Control room 2 (Dimming Circuit) */
				LCD_Clear();
				vidLEDBrightnessControl();
				break;
			
			case '0':	/*!Comment: Exit  */
				u8Flag = 1;
				break;
			
			default:
				if (u8Priority==0)
				{
					UART_Send_String("Wrong Input\n");
				}
				LCD_udtPrintData("Wrong Input");
				break;

		} // End Switch
	} // End While
} // End Func

/*!Comment: Func for AC controller */
void vidACController(void)
{
	DIO_udtSetPinDirection(DIO_PORTA, DIO_PIN0, DIO_INPUT);
	
	LCD_vidInit();
	ADC_vidInit();
	
	uint16 Temp = (ADC_u8ReadChannel(0));  // Channel On Pin A0
	vidDelay_ms(100);
	
	uint8 ADC_Reading = Temp * (5.0 / 1024.0);
	ADC_Reading = ADC_Reading *100;
	vidDelay_ms(500);
	
	if(ADC_Reading >= 28)
	{
		DIO_udtSetPinValue(DIO_PORTD, DIO_PIN7, DIO_LOW);	//DC motor turned ON
		LCD_udtPrintData("DC Motor On");
		vidDelay_ms(1000);
	}
	else if(ADC_Reading <= 21)
	{
		DIO_udtSetPinValue(DIO_PORTD, DIO_PIN7, DIO_HIGH);	//DC motor turned OFF
		LCD_udtPrintData("DC Motor Off");
		vidDelay_ms(1000);
	}
	else
	{
		/*!Comment: Do Nothing*/
	}
	vidDelay_ms(1000);
	
} // End Func


uint8 u8pressed = 0;
/*!Comment: Func to list all applications */
void Smart_Options (uint8 Control_Lead)
{
	uint8 u8loop =0;
	uint8 u8choice = 0;
	while (u8loop==0)
	{
		LCD_Clear();
		
		/*!Comment: List options for ADMIN/USER on LCD/UART */
		if (u8Priority==0)
		{
			UART_Send_String("A:Open Door\n");
			UART_Send_String("B:light\nC:More\n");
		}
		LCD_udtPrintData("A:Open Door");
		LCD_vidGoTo(1,0);
		LCD_udtPrintData("B:light C:More");

		u8pressed = Priority_Select();
		uint8 Return_Flag = 1;
		uint8 u8Loop2 = 0;
		switch(u8pressed)
		{
			case'A' :	/*!Comment: Servo motor */
			TIMER1_vidInit();
			LCD_Clear();
			if (Control_Lead == 1)
			{
				servo_rotate();
				vidDelay_ms(1000);
			}
			else if (Control_Lead == 0)
			{
				if (u8Priority==0)
				{
					UART_Send_String("Wait for ADMIN to accept");
					vidDelay_ms(1000);
				}
				LCD_udtPrintData("Wait for ADMIN");
				LCD_vidGoTo(1,0);
				LCD_udtPrintData("to accept");
				vidDelay_ms(1000);
				Door_flag = 2;
				LCD_Clear;
				Smart_Login_Step();
				if (Door_flag == 1)
				{
					if (u8Priority==0)
					{
						UART_Send_String("ADMIN ACCEPTED");
					}
					LCD_Clear();
					LCD_udtPrintData("ADMIN ACCEPTED");
					servo_rotate();
					vidDelay_ms(1000);
				}
				else if(Door_flag == 0)
				{
					if (u8Priority==0)
					{
						UART_Send_String("ADMIN DENIED");
					}
					LCD_Clear();
					LCD_udtPrintData("ADMIN DENIED");
				}
				if (Return_Flag == 0)
				{
					u8Priority = 0;
				}
				else 
					u8Priority = 1;

			}
			break;
			
			case'B' :	/*!Comment: Light control */
			LCD_Clear();
			vidLEDControl();
			break;
			
			case'C' :	/*!Comment: For more options */
			while(u8Loop2 == 0)
			{
				if (u8Priority==0)
				{
					UART_Send_String("1:AC\n");
					if(Admin_Flag == 1)
					{
						UART_Send_String("2:More\n");
					}
					UART_Send_String("0:Exit\n");
				}
				LCD_Clear();
				LCD_udtPrintData("1:AC 0:Exit");
				if(Admin_Flag == 1)
				{
					LCD_vidGoTo(1,0);
					LCD_udtPrintData("2:Add/Remove");
				}
				u8pressed = Priority_Select();
				
				/*!Comment: List more options*/
				switch(u8pressed)
				{
					case'0':	/*!Comment: Exit */
						u8Loop2 = 1;
						break;
					
					case'1':	/*!Comment: AC Controller */
						vidACController();
						break;
					
					case'2':	/*!Comment: Add/Remove User*/
						if(Admin_Flag == 1)
						{
							vidAddRemove(u8pressed);
						}
						break;
					
					default:
						if (u8Priority==0)
						{
							UART_Send_String("WRONG INPUT ");
						}
						LCD_Clear();
						LCD_udtPrintData("WRONG INPUT");
						vidDelay_ms(1000);
						break;
						
				} // End Switch 2
			} // End While
			break;
			case '0':	/*!Comment: Exit */
			u8loop = 1;
			break;
			
			default:
			if (u8Priority==0)
			{
				UART_Send_String("WRONG INPUT ");
			}
			LCD_Clear();
			LCD_udtPrintData("WRONG INPUT");
			vidDelay_ms(1000);
			break;
		}//End Switch 1
	}//End While
} //End Func

/*!Comment: Function to interface with ADMIN/USER */
void LCD_vidProgram(void)
{
	uint8 u8Pressed ;
	LCD_vidGoTo(0,5);
	LCD_udtPrintData("WELCOME");
	UART_Send_String("WELCOME\n");
	_delay_ms(1000);
	LCD_Clear();
	
	LCD_vidGoTo(0,0);
	LCD_udtPrintData("TO USE KEYPAD");
	LCD_vidGoTo(1,0);
	LCD_udtPrintData("PRESS PUSHB.2");
	_delay_ms(4000);
	LCD_Clear();
	
	LCD_udtPrintData("To LOGIN 'A'");
	UART_Send_String("To LOGIN 'A'\n");
	LCD_vidGoTo(1,0);
	
	uint8 u8Loop = 0 ;
	while (u8Loop==0)
	{
		u8Pressed = Priority_Select();
		/*!Comment: Switch case to choose ADMIN or USER*/
		switch(u8Pressed)
		{
			case 'A':
			if (u8Priority==0)
			{
				UART_Send_String("ADMIN OR USER 1:ADMIN   2:USER\n");
			}
			
			LCD_Clear();
			LCD_udtPrintData("ADMIN OR USER");
			LCD_vidGoTo(1,0);
			LCD_udtPrintData("1:ADMIN   2:USER");
			
			u8Loop = 1;
			break;
			
			default:
			if (u8Priority==0)
			{
				UART_Send_String("WRONG INPUT PLEASE ENTER 'A' \n");
			}
			
			LCD_Clear();
			LCD_udtPrintData("WRONG INPUT");
			LCD_vidGoTo(1,0);
			LCD_udtPrintData("PLEASE ENTER 'A'");
			break;
		} //End Switch
	} // End While
	
	uint8 u8Loop2 = 0;
	while(u8Loop2 == 0)
	{
		if (u8Priority == 0)
		{
			u8Pressed = UART_Correct_Recieve();
			u8Loop2 = 1;
		}
		else if (u8Priority == 1)
		{
			u8Pressed = KEYPAD_KEY();
			
			/*!Comment: Admin not allowed on Keypad*/
			if(u8Pressed  == '1')
			{
				LCD_Clear();
				LCD_udtPrintData("Not Allowed");
				LCD_vidGoTo(1,0);
				LCD_udtPrintData("On Keypad");
				vidDelay_ms(1000);
				
				LCD_Clear();
				LCD_udtPrintData("ADMIN OR USER");
				LCD_vidGoTo(1,0);
				LCD_udtPrintData("1:ADMIN   2:USER");
			}
			else
			{
				u8Loop2 = 1;
			}
			
		}
		
		/*!Comment: Flag for if ADMIN or NOT */
		if(u8Pressed == '1')
		{
			Admin_Flag = 1;
		}
		else if (u8Pressed == '2')
		{
			Admin_Flag = 0;
		}

	}// End While
	
	//////////////////////////////////////////////////////////////////////
	if (u8Priority==0)
	{
		UART_Send_String("PRESS # WHEN FINISHED \n");
		vidDelay_ms(500);
	}
	/////////////////////////////////////////////////////////////////////

	
	/*!Comment: Username Storing from KEYPAD or UART */
	for(uint8 i = 0; i<3; i++)
	{
		Smart_Login_Step();
		IsLoginCorrect(ErrorState);
		if(ErrorState == 1)
			break;
	} //End For
	
	if (u8Priority==0)
	{
		UART_Send_String("To Exit Press 0\n");
	}
	LCD_Clear();
	LCD_udtPrintData("To Exit Press 0");
	vidDelay_ms(2000);
	
	Smart_Options (Admin_Flag);
	
} // End Func


