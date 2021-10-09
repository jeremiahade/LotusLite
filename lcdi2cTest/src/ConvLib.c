/*
 * ConvLib.c
 *
 *  Created on: 6 Mar 2021
 *      Author: jerem
 */

#include "ConvLib.h"


double rounders[11] =
{
	0.5,				// 0
	0.05,				// 1
	0.005,				// 2
	0.0005,				// 3
	0.00005,			// 4
	0.000005,			// 5
	0.0000005,			// 6
	0.00000005,			// 7
	0.000000005,		// 8
	0.0000000005,		// 9
	0.00000000005		// 10
};

void ReversePos(char *buff);

void IntegerToAscii(int value, char asciiValue[])
{
	int sign = 0;
	int	charPos = 0, rem = 0, buff;
	buff = value;

	if ((sign = buff) < 0)
		buff = -buff;

	do
	{
		rem = buff % BASE;
		asciiValue[charPos++] = rem + '0';
	}
	while((buff /= BASE) != 0);

	if(sign < 0)
		asciiValue[charPos++] = '-';
	asciiValue[charPos] = '\0';
	ReversePos(asciiValue);
}

char* IntegerToAsci(int value)
{
	int sign = 0;
	int	charPos = 0, rem = 0, buff;
	buff = value;
	char* asciiValue = NULL;

	if ((sign = buff) < 0)
	buff = -buff;

	do
	{
		rem = buff % BASE;
		asciiValue[charPos++] = rem + '0';
	}
	while((buff /= BASE) != 0);

	if(sign < 0)
	asciiValue[charPos++] = '-';
	asciiValue[charPos] = '\0';
	ReversePos(asciiValue);
	return asciiValue;
}

int AsciiToInteger(char *asciiValue)
{
	int res = 0, charPos = 0;
	int8_t sign = 1;

	while(asciiValue[charPos] == ' ')
		charPos++;

	if(asciiValue[charPos] == '-' || asciiValue[charPos])
	{
		sign = 1-2*(asciiValue[charPos++] == '-');
	}

	while(asciiValue[charPos] != '\0')
	{
		if(!(ISDIGIT(asciiValue[charPos])))
		{
			res = 0;
			return res;
		}
		if(res >= INT_MAX/BASE  )
		{
			if (sign == 1)
				return INT_MAX;
			else
				return INT_MIN;
		}
		res = 10 * res + (asciiValue[charPos++] - '0');

	}
	return res * sign;
}

void FloatToAscii(float value, char *asciiValue, int precision)
{
	int wholeNum;
	int charPos = 0;
	float sign = 0.0;
	char valBuff;

	if(precision > MAX_PRECISION)
		precision = MAX_PRECISION;
	if((sign = value) < 0)
		value = -value;
	if (precision < 0)
		{
			if (value < 1.0) precision = 6;
			else if (value < 10.0) precision = 5;
			else if (value < 100.0) precision = 4;
			else if (value < 1000.0) precision = 3;
			else if (value < 10000.0) precision = 2;
			else if (value < 100000.0) precision = 1;
			else precision = 0;
		}
		// round value according the precision
		if (precision)
			value += rounders[precision];
		wholeNum = value;
		value -= wholeNum;
		if(!wholeNum)
			asciiValue[charPos++] = '0';
		else
		{
			while(wholeNum)
			{
				asciiValue[charPos++] = '0' + (wholeNum % BASE10);
				wholeNum /= BASE10;
			}
		}
		if(sign < 0)
		{
			asciiValue[charPos++] = '-';
		}
		ReversePos(asciiValue);
		if(precision)
		{
			asciiValue[charPos++] = '.';
			while(precision--)
			{
				value*=10.0;
				valBuff = value;
				asciiValue[charPos++] = '0' + valBuff;
				value -= valBuff;

			}
		}
		asciiValue[charPos] = 0;
}

float AsciiToFloat(char *asciiValue)
{
	int charPos = 0, expnt = 0;
	int	sign = 1;
	float res = 0.0;
	while(asciiValue[charPos] == ' ')
		asciiValue++;
	if(asciiValue[charPos] == '-' || asciiValue[charPos] == '+')
	{
		sign = 1-2*(asciiValue[charPos++] == '-');
	}
	while(asciiValue[charPos] != '\0' && ISDIGIT(asciiValue[charPos]))
	{
		res = 10 * res + (asciiValue[charPos++] - '0');
	}
	if(asciiValue[charPos] == '.')
	{
		while(asciiValue[charPos++] != '0' && ISDIGIT(asciiValue[charPos]) )
		{
			res = 10 * res + (asciiValue[charPos] - '0');
			expnt --;
		}
	}
	if(asciiValue[charPos]== 'e' || asciiValue[charPos] == 'E')
	{
		int expntSign = 1;
		int signCheck = 0;
		int expntValue = 0;
		signCheck = asciiValue[++charPos];
		if(signCheck == '-' || signCheck == '+')
		{
			expntSign = 1-2*(asciiValue[charPos++] == '-');
		}
		while(ISDIGIT(asciiValue[charPos]))
		{
			expntValue = 10 * expntValue + (asciiValue[charPos++] - '0');
		}
		expnt = expntValue * expntSign;
		if(expnt == 0)
			return res = 1;

	}

	while(expnt > 0)
	{
		res *= 10.0;
		expnt--;
	}
	while(expnt < 0)
	{
		res *= 0.1;
		expnt++;
	}
	return res * sign;
}

void ReversePos(char *buff)
{
	int pos, posRev = 0;
	char buffVal;

	for(pos = 0, posRev = strlen(buff) - 1; pos < posRev; pos++, posRev--)
	{
		buffVal = buff[pos];
		buff[pos] = buff[posRev];
		buff[posRev] = buffVal;
	}
}

