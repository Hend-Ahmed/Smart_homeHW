#ifndef _LCD_INTERFACE_H_
#define _LCD_INTERFACE_H_

void LCD_vidInit
(
   void
);

Std_ReturnType LCD_udtSendData 
(
   uint8 u8Data
);

Std_ReturnType LCD_udtSendCommand
(
   uint8 u8Command
);
   
Std_ReturnType LCD_udtPrintData
(
   uint8* pu8DataArray
);

void LCD_vidGoTo
(
   uint8 u8Row,
   uint8 u8Column
 
);

void LCD_vidSpecialChar
(
    uint8 *pu8Arr,
    uint8 u8CGRAMLocation,
    uint8 u8Row,
    uint8 u8Column
);
 



#endif