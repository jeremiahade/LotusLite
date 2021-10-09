/*
 * i2cmasterdrv.h
 *
 * Created: 28/07/2021 19:26:14
 *  Author: jerem
 */


#ifndef I2CMASTERDRV_H_
#define I2CMASTERDRV_H_

#include <compiler.h>
#include <util/twi.h>

#define I2C_READ 0x01
#define I2C_WRITE 0x00

#define START_OK			0x08
#define REPEATED_START_OK	0x10
#define SLA_W_ACK			0x18
#define SLA_W_NACK			0x20
#define DATA_ACK			0x28
#define DATA_NACK			0x30
#define LOSS_DATA_SLA_W		0x38

#define MASK_TWSR			0xF8
#define I2C_STAT			(TWSR & MASK_TWSR)

#define START_I2C			(1<<TWSTA)
#define STOP_I2C			(1<<TWSTO)
#define CLEAR_I2C_INT_FLAG	(1<<TWINT)
#define ENABLE_I2C			(1<<TWEN)
#define	ENABLE_I2C_INT		(1<<TWIE)
#define ENABLE_ACK_GEN		(1<<TWEA)
#define BUSY_I2C			((TWCR & (CLEAR_I2C_INT_FLAG)))

typedef enum I2C_STA{
	START_SUCCESSFUL,
	START_ERROR,
	ADDR_NACK,
	ADDR_ACK,
	ACK_DATA,
	NACK_DATA,
	STOP_DONE

}i2cstat_t;

void InitialiseI2C();
i2cstat_t StartI2CWrite(uint8_t addr);
i2cstat_t StopI2C();
i2cstat_t WriteI2Cbyte(uint8_t addr, uint8_t data);







#endif /* I2CMASTERDRV_H_ */