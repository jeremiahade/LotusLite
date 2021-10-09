/*
 * i2cmasterdrv.c
 *
 * Created: 28/07/2021 19:25:41
 *  Author: jerem
 */

#include "i2cmasterdrv.h"

void InitialiseI2C()
{
	/* Disable TWI */
	//PRR &= ~(1 << PRTWI);
	TWCR = 0;
	/* SCL bitrate = F_CPU / (16 + 2 * TWBR * TWPS value) */
	/* Configured bit rate is 100.000kHz, based on CPU frequency 8.000MHz */
	TWBR = 0x40;          /* SCL bit rate: 100.000kHZ before prescaler 0X20 default */
	TWSR &= ~(1<<TWPS0); /* SCL prescaler: 1, effective bit-rate = 100.000kHz */
	TWSR &= ~(1<<TWPS1);
	TWCR |= CLEAR_I2C_INT_FLAG | ENABLE_I2C;
	TWCR &= ~(ENABLE_I2C_INT);
	TWCR &= ~(ENABLE_ACK_GEN);
}

i2cstat_t StartI2CWrite(uint8_t addr)
{
	uint8_t addrBuff = addr;
	addrBuff = (addrBuff << 1) | I2C_WRITE;

	TWCR |= CLEAR_I2C_INT_FLAG | START_I2C | ENABLE_I2C;

	while(!(TWCR & (1<<TWINT)));

	if(I2C_STAT != START_OK) return START_ERROR;

	//Print(START_SUCCESSFUL);
	TWDR = addrBuff;
	TWCR &= ~(1<<TWSTA);
	TWCR |= (1<<TWINT) | (1<<TWEN);

	while(!(BUSY_I2C));

	if(I2C_STAT != SLA_W_ACK) return ADDR_NACK;

	//Print(ADDR_ACK);
	return ADDR_ACK;
}

i2cstat_t StopI2C()
{
	TWCR |= CLEAR_I2C_INT_FLAG | ENABLE_I2C | STOP_I2C;
	return STOP_DONE;
}

i2cstat_t WriteI2Cbyte(uint8_t addr, uint8_t data)
{
	i2cstat_t status;

	status = StartI2CWrite(addr);
	if (status != ADDR_ACK) return status;

	//Print(status);
	TWDR = data;
	TWCR |= CLEAR_I2C_INT_FLAG | ENABLE_I2C;
	while(!(BUSY_I2C));

	if (I2C_STAT != DATA_ACK)
	{
		StopI2C();
		return NACK_DATA;
	}

	//Print(DATA_ACK)
	StopI2C();
	return ACK_DATA;
}

