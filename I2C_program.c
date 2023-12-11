#include <avr/io.h>		/* Include AVR std. library file */

/* Define bit rate */
#include "I2C_interface.h"
#include "I2C_private.h"
//#include ""
//#include ""

void I2C_Init()			
{
	/*!Comment: Get bit rate register value by formula */
    TWBR = BITRATE(TWSR=0x00);	
}

uint8 I2C_Start(uint8 write_address)
{
    uint8 status;	

	/*!Comment: Enable TWI, generate START */
    TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	
	/*!Comment: Wait until TWI finish its current job */
    while(!(TWCR&(1<<TWINT)));

	/*!Comment Read TWI status register */
    status = TWSR&0xF8;	
	
    if(status != 0x08)		
    return 0;
	
	/*!Comment: Write SLA+W in TWI data register */
    TWDR = write_address;		
	
	/*!Comment: Enable TWI & clear interrupt flag */
    TWCR = (1<<TWEN)|(1<<TWINT);
	
	/*!Comment: Wait until TWI finish its current job */
    while(!(TWCR&(1<<TWINT)));	
    
	/*!Comment: Read TWI status register */
	status=TWSR&0xF8;
	
    if(status == 0x18)		/*!Comment: Check for SLA+W transmitted &ack received */
    return 1;			/*!Comment: Return 1 to indicate ack received */

    if(status == 0x20)		/*!Comment: Check for SLA+W transmitted &nack received */
    return 2;			/*!Comment: Return 2 to indicate nack received */

    else
    return 3;			/*!Comment: Else return 3 to indicate SLA+W failed */
}

uint8 I2C_Repeated_Start(uint8 read_address) 
{
    uint8 status;		
	
	/*!Comment: Enable TWI, generate start */
    TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	
	/*!Comment: Wait until TWI finish its current job */
    while(!(TWCR&(1<<TWINT)));

	/*!Comment: Read TWI status register */
    status=TWSR&0xF8;
	
    if(status!=0x10)		/*!Comment: Check for repeated start transmitted */	
    return 0;			/*!Comment: Return 0 for repeated start condition fail */

	/*!Comment: Write SLA+R in TWI data register */
    TWDR=read_address;

	/*!Comment: Enable TWI and clear interrupt flag */
    TWCR=(1<<TWEN)|(1<<TWINT);	
	
	/*!Comment: Wait until TWI finish its current job */
    while(!(TWCR&(1<<TWINT)));	
	
	/*!Comment: Read TWI status register */
    status=TWSR&0xF8;		
    if(status==0x40)		/* Check for SLA+R transmitted &ack received */
    return 1;			/* Return 1 to indicate ack received */
	
    if(status==0x48)		/* Check for SLA+R transmitted &nack received */
    return 2;			/* Return 2 to indicate nack received */
	
    else
    return 3;			/* Else return 3 to indicate SLA+W failed */
}

uint8 I2C_Write(uint8 data)	
{
    uint8 status;	

	/*!Comment: Copy data in TWI data register */
    TWDR=data;

	/*!Comment: Enable TWI and clear interrupt flag */
    TWCR=(1<<TWEN)|(1<<TWINT);
	
	/*!Comment: Wait until TWI finish its current job */
    while(!(TWCR&(1<<TWINT)));

	/*!Comment: Read TWI status register */
    status=TWSR&0xF8;
	
    if(status==0x28)		/* Check for data transmitted &ack received */
    return 0;			/* Return 0 to indicate ack received */
	
    if(status==0x30)		/* Check for data transmitted &nack received */
    return 1;			/* Return 1 to indicate nack received */
	
    else
    return 2;			/* Else return 2 for data transmission failure */
}

uint8 I2C_Read_Ack()		
{
	/*!Comment: Enable TWI, generation of ack */
    TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA); 
	
	/*!Comment: Wait until TWI finish its current job */
    while(!(TWCR&(1<<TWINT)));	
	
    return TWDR;			
}

uint8 I2C_Read_Nack()		
{
	/*!Comment: Enable TWI and clear interrupt flag */
    TWCR=(1<<TWEN)|(1<<TWINT);	
	
	/*!Comment: Wait until TWI finish its current job */
    while(!(TWCR&(1<<TWINT)));	
	
    return TWDR;		
}

void I2C_Stop()			
{
	/*!Comment: Enable TWI, generate stop */
    TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);
	
	/*!Comment: Wait until stop condition execution */
    while(TWCR&(1<<TWSTO));
}
