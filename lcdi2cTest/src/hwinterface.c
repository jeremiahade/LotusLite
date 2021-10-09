/*******************************************************************
**File Name: xxxxxxxxxxxx.h/c                                     **
**Library Name: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.          **
**Original Project Name: Null.                                    **
**Author Name: Jeremiah A.                                        **
**Version No:  2.0                                                **
**Date Created: 11th May 2020.                                    **
**Last Edited: 29th August 2020.                                  **
********************************************************************/

#include <hwinterface.h>

void Writei2c(uint8_t addr, uint8_t data)
{
	WriteI2Cbyte(addr, data);
}

uint8_t Readi2c(uint8_t addr)
{
	uint8_t data = 0;
	return data;
}

void Starti2c(uint8_t addr)
{
	StartI2CWrite(addr);
}

void Stopi2cTx()
{
	StopI2C();
}

void MsDelay(uint16_t duration)
{
	while(duration)
	{
		_delay_ms(1);
		duration--;
	}
}

void uSDelay(uint16_t duration)
{
	while(duration)
	{
		_delay_us(1);
		duration--;
	}
}
