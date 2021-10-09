/*******************************************************************
**File Name: xxxxxxxxxxxx.h/c                                     **
**Library Name: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.          **
**Original Project Name: Null.                                    **
**Author Name: Jeremiah A.                                        **
**Version No:  2.0                                                **
**Date Created: 11th May 2020.                                    **
**Last Edited: 29th August 2020.                                  **
********************************************************************/

#include "lcdi2c.h"

double roundup[11] =
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

uint8_t lcdPortCmd = 0;

void InitialiseLCD(lcdmodule_t* lcdModule);
void WriteLCDCmdReg(const uint8_t addr, uint8_t cmd);
void PrintLCDChar(const uint8_t addr, uint8_t data);
void PrintLCDCharXY16x2(const uint8_t addr, uint8_t data, uint8_t X, uint8_t Y);
void PrintLCDCharXY20x4(const uint8_t addr, uint8_t data, uint8_t X, uint8_t Y);
void PrintStringLCD(const uint8_t addr, char* data);
void PrintStringLCDXY16x2(const uint8_t addr, char* data, uint8_t X, uint8_t Y);
void PrintStringLCDXY20x4(const uint8_t addr, char* data, uint8_t X, uint8_t Y);
void ShiftCursorPos16x2(uint8_t addr, uint8_t X, uint8_t Y);
void ShiftCursorPos20x4(uint8_t addr, uint8_t X, uint8_t Y);
void SwitchDisplayCursor(uint8_t addr, dispCursor_t state);
void SwitchLineNumMatrixState(uint8_t addr, lineMatrx_t state);
void SelCursorMovement(uint8_t addr, cursrMovment_t state);
void ShiftDisplayCursrRight(uint8_t addr);
void ClearDisplay(uint8_t addr);
void SwitchLEDOn(uint8_t addr);
void GoHome(uint8_t addr);
void GoFirstLine(uint8_t addr);
void GoSecondLine(uint8_t addr);

/*void InitialiseLCD(lcdmodule_t* lcdModule)
{
	lcdPortCmd = 0;
	MsDelay(50);
	Writei2c(lcdModule->addr, 0xFF);
	MsDelay(50);
	WriteLCDCmdReg(lcdModule->addr, INIT_CMD);
	uSDelay(50);
	WriteLCDCmdReg(lcdModule->addr, INIT_CMD);
	uSDelay(50);
	WriteLCDCmdReg(lcdModule->addr, INIT_CMD1);
	uSDelay(50);
	//SwitchLineNumMatrixState(lcdModule->addr, lcdModule->lineMatrixSel);
	WriteLCDCmdReg(lcdModule->addr, TWOLINES_5x8MATRX);
	uSDelay(50);
	//SwitchDisplayCursor(lcdModule->addr, lcdModule->dispCursorSt);
	WriteLCDCmdReg(lcdModule->addr, DISPON_CURSOROFF);
	uSDelay(50);
//	WriteLCDCmdReg(lcdModule->addr, CLEAR_SCREEN);
	//MsDelay(500);
	//SelCursorMovement(lcdModule->addr, lcdModule->cursrMovementSel);
	WriteLCDCmdReg(lcdModule->addr, INCREMENT_CURSOR);
	MsDelay(500);
	//ShiftDisplayCursrRight(lcdModule->addr);
	//WriteLCDCmdReg(lcdModule->addr, SHIFT_DISP_RIGHT);
	//
	if (lcdModule->type == LCD16x2)
	{
		ClearDisplay16x2(lcdModule->addr);
	}
	else
	{
		ClearDisplay20x4(lcdModule->addr);
	}
	//ClearDisplay(lcdModule->addr);
	//MsDelay(50);
	//GoHome(lcdModule->addr);
}*/

void InitialiseLCD(lcdmodule_t* lcdModule)
{
	lcdPortCmd = 0;
	MsDelay(50);
	Writei2c(lcdModule->addr, 0xFF);
	MsDelay(50);
	WriteLCDCmdReg(lcdModule->addr, INIT_CMD);
	uSDelay(50);
	WriteLCDCmdReg(lcdModule->addr, INIT_CMD);
	uSDelay(50);
	WriteLCDCmdReg(lcdModule->addr, INIT_CMD1);
	uSDelay(50);
	SwitchLineNumMatrixState(lcdModule->addr, lcdModule->lineMatrixSel);
	uSDelay(50);
	SwitchDisplayCursor(lcdModule->addr, lcdModule->dispCursorSt);
	uSDelay(50);
	SelCursorMovement(lcdModule->addr, lcdModule->cursrMovementSel);
	MsDelay(50);
	if (lcdModule->type == LCD16x2)
	{
		ClearDisplay16x2(lcdModule->addr);
	}
	else
	{
		ClearDisplay20x4(lcdModule->addr);
	}

	//Functions declarations
	lcdModule->PrintChar			= &PrintLCDChar;
	lcdModule->PrintString			= &PrintStringLCD;
	lcdModule->PrintInteger 		= &PrintIntegerLCD;
	lcdModule->PrintFloat			= &PrintFloatLCD;
	lcdModule->SwitchDispCursor		= &SwitchDisplayCursor;
	lcdModule->SwitchLineMatrx 		= &SwitchLineNumMatrixState;
	lcdModule->SelCursorMovement	= &SelCursorMovement;
	lcdModule->ShiftDispCursorRight	= &ShiftDisplayCursrRight;
	lcdModule->GoHome				= &GoHome;
	lcdModule->SwitchLedOn			= &SwitchLEDOn;
	if (lcdModule->type == LCD16x2)
	{
		lcdModule->PrintFloatXY		= &PrintFloatLCDXY16x2;
		lcdModule->PrintCharXY		= &PrintLCDCharXY16x2;
		lcdModule->PrintStringXY 	= &PrintStringLCDXY16x2;
		lcdModule->PrintIntegerXY 	= &PrintIntegerLCDXY16x2;
		lcdModule->ShiftCursorPos 	= &ShiftCursorPos16x2;
		lcdModule->ClearDisplay 	= &ClearDisplay16x2;
	}
	else
	{
		lcdModule->PrintFloatXY 	= &PrintFloatLCDXY20x4;
		lcdModule->PrintCharXY 		= &PrintLCDCharXY20x4;
		lcdModule->PrintStringXY 	= &PrintStringLCDXY20x4;
		lcdModule->PrintIntegerXY 	= &PrintIntegerLCDXY20x4;
		lcdModule->PrintCharXY 		= &PrintLCDCharXY20x4;
		lcdModule->ClearDisplay 	= &ClearDisplay20x4;
	}
}


void WriteLCDCmdReg(const uint8_t addr, uint8_t cmd)
{
	lcdPortCmd = 0;
	uint8_t addrBuf =	addr;
	lcdPortCmd	=	(lcdPortCmd & 0x0F) | (cmd & 0xF0); //Get Upper Bits
	lcdPortCmd	&=	~(1<<RS);
	lcdPortCmd  &=   ~(1<<R_W);
	lcdPortCmd  |=  (1<<LED);
	Writei2c(addrBuf, lcdPortCmd);
	lcdPortCmd	&=	~(1<<RS);
	//lcdPortCmd &=   ~(1<<R_W);
	Writei2c(addrBuf, lcdPortCmd);
	lcdPortCmd	|=	(1 << EN);
	Writei2c(addrBuf, lcdPortCmd);
	uSDelay(1);
	lcdPortCmd &=	~(1 << EN);
	Writei2c(addrBuf, lcdPortCmd);
	uSDelay(200);

	lcdPortCmd	=	(lcdPortCmd & 0x0F)	|	(cmd << 4); //Get Lower Bits
	//lcdPortCmd	&=	~(1<<RS);
	//lcdPortCmd  &=   ~(1<<R_W);
	lcdPortCmd  |=  (1<<LED);
	Writei2c(addrBuf, lcdPortCmd);
	lcdPortCmd	|=	(1 << EN);
	Writei2c(addrBuf, lcdPortCmd);
	uSDelay(1);
	lcdPortCmd	&=	~(1 << EN);
	MsDelay(2);
}

void PrintLCDChar(const uint8_t addr, uint8_t data)
{
	//uint8_t lcdPortCmd =	0;
	uint8_t	addrBuf	=	addr;
	lcdPortCmd = (lcdPortCmd & 0x0F ) | (data & 0xF0);
	lcdPortCmd |=	(1 << RS);
	//lcdPortCmd &= ~(1<<R_W);
	lcdPortCmd  |=  (1<<LED);
	Writei2c(addrBuf, lcdPortCmd);
	lcdPortCmd |=	(1 << RS);
	//lcdPortCmd &= ~(1<<R_W);
	Writei2c(addrBuf, lcdPortCmd);
	lcdPortCmd |=	(1<<EN);
	Writei2c(addrBuf, lcdPortCmd);
	uSDelay(1);
	lcdPortCmd &=	~(1<<EN);
	Writei2c(addrBuf, lcdPortCmd);
	uSDelay(200);

	lcdPortCmd	=	(lcdPortCmd & 0x0F)	|	((data << 4) & 0xF0);
	lcdPortCmd |=	(1 << RS);
	//lcdPortCmd &= ~(1<<R_W);
	lcdPortCmd  |=  (1<<LED);
	Writei2c(addrBuf, lcdPortCmd);
	lcdPortCmd |= (1 << EN);
	Writei2c(addrBuf, lcdPortCmd);
	uSDelay(1);
	lcdPortCmd	&=	~(1	<< EN);
	Writei2c(addrBuf, lcdPortCmd);
	MsDelay(2);
}

void PrintLCDCharXY16x2(const uint8_t addr, uint8_t data, uint8_t X, uint8_t Y)
{
	ShiftCursorPos16x2(addr, X, Y);
	PrintLCDChar(addr, data);
}

void PrintLCDCharXY20x4(const uint8_t addr, uint8_t data, uint8_t X, uint8_t Y)
{
	ShiftCursorPos20x4(addr, X, Y);
	PrintLCDChar(addr, data);
}

void PrintStringLCD(const uint8_t addr, char* data)
{
	uint16_t iteration = 0;

	//GoHome(addr);
	while(data[iteration])
	{
		PrintLCDChar(addr, data[iteration]);
		iteration++;
	}

}

void PrintStringLCDXY16x2(const uint8_t addr, char* data, uint8_t X, uint8_t Y)
{
	ShiftCursorPos16x2(addr, X, Y);
	PrintStringLCD(addr, data);
}

void PrintStringLCDXY20x4(const uint8_t addr, char* data, uint8_t X, uint8_t Y)
{
	ShiftCursorPos20x4(addr, X, Y);
	PrintStringLCD(addr, data);
}

void PrintIntegerLCD(const uint8_t addr, int data)
{
	//char f = 5+'0';
	char dataCvBuff[10] = {};
	/*dataCvBuff[0] = f;
	dataCvBuff[1] = '8';*/

	int sign = 0;
	int	charPos = 0, rem = 0, buff;
	buff = data;

	if ((sign = buff) < 0)
	buff = -buff;

	do
	{
		rem = buff % BASE;
		dataCvBuff[charPos++] = rem + '0';
	}
	while((buff /= BASE) != 0);

	if(sign < 0)
	dataCvBuff[charPos++] = '-';
	dataCvBuff[charPos] = '\0';
	int pos, posRev = 0;
	char buffVal;

	for(pos = 0, posRev = strlen(dataCvBuff) - 1; pos < posRev; pos++, posRev--)
	{
		buffVal = dataCvBuff[pos];
		dataCvBuff[pos] = dataCvBuff[posRev];
		dataCvBuff[posRev] = buffVal;
	}
	//IntegerToAscii(data, dataCvBuff);
	//dataCvBuff = IntegerToAsci(data);
	//dataCvBuff = itoa(data, dataCvBuff, 10);
	PrintStringLCD(addr, dataCvBuff);
	//PrintLCDChar(addr, dataCvBuff[0]);
	//PrintLCDChar(addr, dataCvBuff[1]);
	/*while(*dataCvBuff)
	{
		PrintLCDChar(addr, '5');
	}*/
	//PrintStringLCD(addr, dataCvBuff);
}

void PrintIntegerLCDXY16x2(const uint8_t addr, int data, uint8_t X, uint8_t Y)
{
	ShiftCursorPos16x2(addr, X, Y);
	PrintIntegerLCD(addr, data);
}

void PrintIntegerLCDXY20x4(const uint8_t addr, int data, uint8_t X, uint8_t Y)
{
	ShiftCursorPos20x4(addr, X, Y);
	PrintIntegerLCD(addr, data);
}

void PrintFloatLCD(const uint8_t addr, float data, uint8_t precision)
{
char dataCvBuff[20] = {};

int wholeNum;
int charPos = 0;
float sign = 0.0;
char valBuff;

if(precision > MAX_PRECISION)
precision = MAX_PRECISION;
if((sign = data) < 0)
data = -data;
if (precision < 0)
{
	if (data < 1.0) precision = 6;
	else if (data < 10.0) precision = 5;
	else if (data < 100.0) precision = 4;
	else if (data < 1000.0) precision = 3;
	else if (data < 10000.0) precision = 2;
	else if (data < 100000.0) precision = 1;
	else precision = 0;
}
// round data according the precision
if (precision)
data += roundup[precision];
wholeNum = data;
data -= wholeNum;
if(!wholeNum)
dataCvBuff[charPos++] = '0';
else
{
	while(wholeNum)
	{
		dataCvBuff[charPos++] = '0' + (wholeNum % BASE10);
		wholeNum /= BASE10;
	}
}
if(sign < 0)
{
	dataCvBuff[charPos++] = '-';
}

	int pos, posRev = 0;
	char buffVal;

	for(pos = 0, posRev = strlen(dataCvBuff) - 1; pos < posRev; pos++, posRev--)
	{
		buffVal = dataCvBuff[pos];
		dataCvBuff[pos] = dataCvBuff[posRev];
		dataCvBuff[posRev] = buffVal;
	}

if(precision)
{
	dataCvBuff[charPos++] = '.';
	while(precision--)
	{
		data*=10.0;
		valBuff = data;
		dataCvBuff[charPos++] = '0' + valBuff;
		data -= valBuff;

	}
}
//dataCvBuff[charPos] = 0;
PrintStringLCD(addr, dataCvBuff);
}
void PrintFloatLCDXY16x2(const uint8_t addr, float data, uint8_t precision, uint8_t X, uint8_t Y)
{
	ShiftCursorPos16x2(addr, X, Y);
	PrintFloatLCD(addr, data, precision);
}

void PrintFloatLCDXY20x4(const uint8_t addr, float data, uint8_t precision, uint8_t X, uint8_t Y)
{
	ShiftCursorPos20x4(addr, X, Y);
	PrintFloatLCD(addr, data, precision);
}

void PrintSpecialChar(const uint8_t addr, uint8_t data[], uint8_t charPos )
{
	charPos &= 0x07;

	WriteLCDCmdReg(addr, 0x40 | (charPos<<3));
	for(int i = 0; i < 8; i++)
	{
		//PrintLCDChar(addr, data[i]);
			uint8_t	addrBuf	=	addr;
			lcdPortCmd = (lcdPortCmd & 0x0F ) | (data[i] & 0xF0);
			lcdPortCmd |=	(1 << RS);
			//lcdPortCmd &= ~(1<<R_W);
			//lcdPortCmd  |=  (1<<LED);
			//Writei2c(addrBuf, lcdPortCmd);
			//lcdPortCmd |=	(1 << RS);
			//lcdPortCmd &= ~(1<<R_W);
			Writei2c(addrBuf, lcdPortCmd);
			lcdPortCmd |=	(1<<EN);
			Writei2c(addrBuf, lcdPortCmd);
			uSDelay(1);
			lcdPortCmd &=	~(1<<EN);
			Writei2c(addrBuf, lcdPortCmd);
			uSDelay(200);

			lcdPortCmd	=	(lcdPortCmd & 0x0F)	|	((data[i] << 4) & 0xF0);
			lcdPortCmd |=	(1 << RS);
			lcdPortCmd &= ~(1<<R_W);
			//lcdPortCmd  |=  (1<<LED);
			Writei2c(addrBuf, lcdPortCmd);
			lcdPortCmd |= (1 << EN);
			Writei2c(addrBuf, lcdPortCmd);
			uSDelay(1);
			lcdPortCmd	&=	~(1	<< EN);
			Writei2c(addrBuf, lcdPortCmd);
			MsDelay(2);
	}

}

void ShiftCursorPos16x2(uint8_t addr, uint8_t X, uint8_t Y)
{
	if(X >= LCD16x2XMAX)
	{
		X = 15;
	}
	if(Y >= LCD16x2YMAX2LINE)
	{
		Y = 1;
	}

	/*if (Y == 0)
	{
		WriteLCDCmdReg(addr, (X | MOVE_CURSOR_1STLINE));
	}
	else
	{
		WriteLCDCmdReg(addr, (X  | MOVE_CURSOR_2NDLINE));
	}*/

	switch(Y)
	{
	case 0:
		WriteLCDCmdReg(addr, (X | MOVE_CURSOR_1STLINE));
		break;
	case 1:
		WriteLCDCmdReg(addr, (X  | MOVE_CURSOR_2NDLINE));
		break;
	default:
		WriteLCDCmdReg(addr, (X  | MOVE_CURSOR_2NDLINE));
		break;
	}
}

void ShiftCursorPos20x4(uint8_t addr, uint8_t X, uint8_t Y)
{
	if(X >= LCD20x4XMAX)
	{
		X = 19;
	}
	if(Y >= LCD20x4YMAX2LINE)
	{
		Y = 3;
	}

	/*if (Y == 0)
	{
		WriteLCDCmdReg(addr, ((X + 0x00) | SET_DDRAM_ADDR));
	}
	if (Y == 1)
	{
		WriteLCDCmdReg(addr, ((X + 0x40) | SET_DDRAM_ADDR));
	}
	if (Y == 2)
	{
		WriteLCDCmdReg(addr, ((X + 0x14) | SET_DDRAM_ADDR));
	}
	if (Y == 3)
	{
		WriteLCDCmdReg(addr, ((X + 0x54) | SET_DDRAM_ADDR));
	}*/
	switch(Y)
	{
	case 0:
		WriteLCDCmdReg(addr, ((X + 0x00) | SET_DDRAM_ADDR));
		break;
	case 1:
		WriteLCDCmdReg(addr, ((X + 0x40) | SET_DDRAM_ADDR));
		break;
	case 2:
		WriteLCDCmdReg(addr, ((X + 0x14) | SET_DDRAM_ADDR));
		break;
	case 3:
		WriteLCDCmdReg(addr, ((X + 0x54) | SET_DDRAM_ADDR));
		break;
	default:
		break;
		}
}

void SwitchDisplayCursor(uint8_t addr, dispCursor_t state)
{
	switch(state)
	{
	case dispOff_CursorOff:
		WriteLCDCmdReg(addr, DISPOFF_CURSOROFF);
		break;
	case dispOff_CursorOn:
		WriteLCDCmdReg(addr, DISPOFF_CURSORON);
		break;
	case dispOn_Cursoroff:
		WriteLCDCmdReg(addr, DISPON_CURSOROFF);
		break;
	case dispOn_CursorOn:
		WriteLCDCmdReg(addr, DISPON_CURSORON);
		break;
	case dispOn_CursorBlink:
		WriteLCDCmdReg(addr, DISPON_CURSORBLINK);
		break;
	default:
		WriteLCDCmdReg(addr, DISPON_CURSOROFF);
	}
}

void SwitchLineNumMatrixState(uint8_t addr, lineMatrx_t state)
{
	switch(state)
	{
	case twolines_5x8Matrix:
		WriteLCDCmdReg(addr, TWOLINES_5x8MATRX);
		break;
	case twolines_5x10Matrix:
		WriteLCDCmdReg(addr, TWOLINES_5x10MATRX);
		break;
	case oneline_5x8Matrix:
		WriteLCDCmdReg(addr, ONELINE_5x8MATRX);
		break;
	case oneline_5x10Matrix:
		WriteLCDCmdReg(addr, ONELINE_5x10MATRX);
		break;
	default:
		WriteLCDCmdReg(addr, TWOLINES_5x8MATRX);
	}
}

void SelCursorMovement(uint8_t addr, cursrMovment_t state)
{
	switch(state)
	{
	case incrementCursor:
		WriteLCDCmdReg(addr, INCREMENT_CURSOR);
		break;
	case incrementCursorShiftDisp:
		WriteLCDCmdReg(addr, INCREMENT_CURSOR1);
		break;
	case decrementCursor:
		WriteLCDCmdReg(addr, DECREMENT_CURSOR);
		break;
	case decrementCursorShiftDisp:
		WriteLCDCmdReg(addr, DECREMENT_CURSOR1);
		break;
	default:
		WriteLCDCmdReg(addr, INCREMENT_CURSOR);
	}
}

void ShiftDisplayCursrRight(uint8_t addr)
{
	WriteLCDCmdReg(addr, SHIFT_DISP_RIGHT);
}

void GoHome(uint8_t addr)
{
	WriteLCDCmdReg(addr, RETURN_HOME);
}

void GoFirstLine(uint8_t addr)
{
	WriteLCDCmdReg(addr, MOVE_CURSOR_1STLINE);
}

void GoSecondLine(uint8_t addr)
{
	WriteLCDCmdReg(addr, MOVE_CURSOR_2NDLINE);
}

void SwitchLEDOn(uint8_t addr)
{
	Writei2c(addr, (1<<3));
}

void ClearDisplay16x2(uint8_t addr)
{
	uint8_t X, Y = 0;

	for(Y = 0; Y < 2; Y++)
	{
		for(X = 0; X < 16; X++)
		{
			PrintLCDCharXY16x2(addr, ' ', X, Y);
		}
	}
	GoHome(addr);
}

void ClearDisplay20x4(uint8_t addr)
{
	uint8_t X, Y = 0;

	for(Y = 0; Y < 4; Y++)
	{
		for(X = 0; X < 20; X++)
		{
			PrintLCDCharXY20x4(addr, ' ', X, Y);
		}
	}
	GoHome(addr);
}

void ClearDisplay1stLine16x2(uint8_t addr)
{
	uint8_t X = 0;
	for(X = 0; X < 16; X++)
	{
		PrintLCDCharXY16x2(addr, ' ', X, 0);
	}
	GoHome(addr);
}
void ClearDisplay2ndLine16x2(uint8_t addr)
{
	uint8_t X = 0;
	for(X = 0; X < 16; X++)
	{
		PrintLCDCharXY16x2(addr, ' ', X, 1);
	}
	GoHome(addr);
}
void ClearDisplay1stLine20x4(uint8_t addr)
{
	uint8_t X = 0;
	for(X = 0; X < 20; X++)
	{
		PrintLCDCharXY20x4(addr, ' ', X, 0);
	}
	GoHome(addr);
}
void ClearDisplay2ndLine20x4(uint8_t addr)
{
	uint8_t X = 0;
	for(X = 0; X < 20; X++)
	{
		PrintLCDCharXY20x4(addr, ' ', X, 1);
	}
	GoHome(addr);
}
void ClearDisplay3rdLine20x4(uint8_t addr)
{
	uint8_t X = 0;
	for(X = 0; X < 20; X++)
	{
		PrintLCDCharXY20x4(addr, ' ', X, 2);
	}
	GoHome(addr);
}
void ClearDisplay4thLine20x4(uint8_t addr)
{
	uint8_t X = 0;
	for(X = 0; X < 20; X++)
	{
		PrintLCDCharXY20x4(addr, ' ', X, 3);
	}
	GoHome(addr);
}


void ClearDisplay(uint8_t addr)
{
	WriteLCDCmdReg(addr, CLEAR_SCREEN);
	//MsDelay(3);
}
