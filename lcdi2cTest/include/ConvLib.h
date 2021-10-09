/*
 * ConvLib.h
 *
 *  Created on: 6 Mar 2021
 *      Author: jerem
 */

#ifndef CONVLIB_H_
#define CONVLIB_H_

#endif /* CONVLIB_H_ */

#include <stdio.h>
#include <stdint-gcc.h>
#include <string.h>
#include <stdbool.h>

#define BASE 10
#define BASE10 10
#define INT_MAX  32215
#define INT_MIN  -32215
#define ISDIGIT(INPUT)(INPUT >= '0' && INPUT <= '9')
#define MAX_PRECISION	10




void IntegerToAscii(int value, char *asciiValue);
char* IntegerToAsci(int value);
int AsciiToInteger(char *asciiValue);
void FloatToAscii(float value, char *asciiValue, int precision);
float AsciiToFloat(char *asciiValue);
