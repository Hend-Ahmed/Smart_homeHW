#ifndef _I2C_INTERFACE_H_
#define	_I2C_INTERFACE_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "I2C_private.h"

#define F_CPU 16000000UL		/* Define CPU clock Frequency 16MHz */
#define SCL_CLK					400000u


#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))

/* !Comment: I2C Status Bits in the TWSR Register */
#define I2C_START         0x08 /* start has been sent */
#define I2C_REP_START     0x10 /* repeated start */
#define I2C_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define I2C_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define I2C_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define I2C_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define I2C_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

void I2C_Init();
uint8 I2C_Start(uint8 write_address);
uint8 I2C_Write(uint8 data);
uint8 I2C_Read_Ack();
uint8 I2C_Read_Nack();
void I2C_Stop();

#endif