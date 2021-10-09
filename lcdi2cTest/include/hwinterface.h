/*******************************************************************
**File Name: xxxxxxxxxxxx.h/c                                     **
**Library Name: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.          **
**Original Project Name: Null.                                    **
**Author Name: Jeremiah A.                                        **
**Version No:  2.0                                                **
**Date Created: 11th May 2020.                                    **
**Last Edited: 29th August 2020.                                  **
********************************************************************/

#ifndef HWINTERFACE_H_
#define HWINTERFACE_H_

#include <stdint.h>
#include "i2cmasterdrv.h"
#include <util/delay.h>
//#include <atmel_start.h>
//#include "driver_init.h"

#ifndef F_CPU
#define F_CPU 8000000
#endif


void Writei2c(uint8_t addr, uint8_t data);
uint8_t Readi2c(uint8_t addr);
void Stopi2cTx();
void Starti2c(uint8_t addr);
void MsDelay(uint16_t duration);
void uSDelay(uint16_t duration);


#endif /* HWINTERFACE_H_ */


