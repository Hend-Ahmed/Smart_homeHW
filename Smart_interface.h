#ifndef _SMART_INTERFACE_H_
#define _SMART_INTERFACE_H_

typedef struct database
{
	uint8  Name;
	uint16 Name_Address;
}Login_Data;

void vidAdd_User (uint8 Username);

void vidAdd_Pass (uint16 password);

void vid_If_User_Added (void);

void vidRemove_User(uint8 Username);

void int_to_string(int number, char* buffer);

uint16 Correct_Address (uint8 Username);

void LCD_vidProgram(void);

void Smart_Options (uint8 Control_Lead);

void IsLoginCorrect(uint8 State);

uint8 Priority_Select(void);

void KeyPadSelect(void);

void vidLEDBrightnessControl(void);

void vidLEDControl(void);

void Smart_Login_Step (void);

void vidAddRemove(uint8 u8pressed);

void vidACController(void);



#endif

