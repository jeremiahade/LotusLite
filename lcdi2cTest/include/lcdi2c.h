/*******************************************************************
**File Name: xxxxxxxxxxxx.h/c                                     **
**Library Name: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.          **
**Original Project Name: Null.                                    **
**Author Name: Jeremiah A.                                        **
**Version No:  2.0                                                **
**Date Created: 11th May 2020.                                    **
**Last Edited: 29th August 2020.                                  **
********************************************************************/

#ifndef LCDI2C_H_
#define LCDI2C_H_

#include "hwinterface.h"
#include <stdint.h>
#include "ConvLib.h"

#define CLEAR_SCREEN		0x01
#define	RETURN_HOME			0x02
#define DECREMENT_CURSOR	0x04
#define DECREMENT_CURSOR1	0x05
#define	INCREMENT_CURSOR	0x06
#define	INCREMENT_CURSOR1	0x07
#define	DISPOFF_CURSOROFF	0x08
#define DISPOFF_CURSORON	0x0A
#define DISPON_CURSOROFF	0x0C
#define DISPON_CURSORON		0x0E
#define DISPON_CURSORBLINK	0x0F
#define SHIFT_CURSOR_LEFT	0x10
#define SHIFT_CURSOR_RIGHT	0x14
#define SHIFT_DISP_LEFT		0x18
#define SHIFT_DISP_RIGHT	0x1C
#define MOVE_CURSOR_1STLINE	0x80
#define	MOVE_CURSOR_2NDLINE	0xC0
#define	TWOLINES_5x8MATRX	0x28
#define TWOLINES_5x10MATRX	0x2C
#define ONELINE_5x8MATRX	0x20
#define ONELINE_5x10MATRX	0x24
#define RS					0x00
#define R_W					0x01
#define EN					0x02
#define LED					0x03
#define INIT_CMD			0x33
#define INIT_CMD1			0x32
#define SET_DDRAM_ADDR		0x80
#define WRITE_CGRAM			0x40

//Overflow definition
#define LCD16x2XMAX			16
#define LCD16x2YMAX2LINE	2
#define LCD16x2YMAX1LINE	1
#define LCD20x4XMAX			20
#define LCD20x4YMAX2LINE	4
#define LCD20x4YMAX1LINE	1

//Character Code
#define	FORWARD_ARROW		0x7E
#define	BACKWARD_ARROW		0x7F
#define	CARET_CIRCUMFLEX	0x5E
#define DEGREE				0xDF
#define BOTTOM_DEGREE		0xA1
#define	OMEGA				0xF4
#define	ALPHA				0xE0
#define BETA				0xE2
#define	EPSILON				0xE3
#define	MICRO				0xE4
#define	SIGMA_NEPER			0xE5
#define	RHO_PICO			0xE6
#define GRADIANS			0xE7
#define SQUARE_ROOT			0xE8
#define COMPLEX_NUM			0xEA
#define NTH_NUM				0xEE
#define THETA				0xF2
#define	SUMMATION			0xF6
#define PI_SYMBOL			0xF7
#define	EULERMASCHCNSTSYM	0xF9
#define DIVIDE_SYMBOL		0xFD
#define MULTIPLY_SYMBOL		0xEB
#define INFINITY_SYMBOL		0xF3
#define SAMPLE_MEAN_SYM		0xF8
#define THERE_EXIST_SYM		0xD6

//Custom code



//Conversion definition
#define BASE10				10

typedef enum LCD_TYPE{
	LCD16x2,
	LCD20x4
}lcdType_t;

typedef enum LINE_MATRX{
	twolines_5x8Matrix,
	twolines_5x10Matrix,
	oneline_5x8Matrix,
	oneline_5x10Matrix
}lineMatrx_t;

typedef enum DISP_CURSOR_ST{
	dispOff_CursorOff,
	dispOff_CursorOn,
	dispOn_Cursoroff,
	dispOn_CursorOn,
	dispOn_CursorBlink
}dispCursor_t;

typedef enum CURSOR_MOVEMENT{
	decrementCursor,
	decrementCursorShiftDisp,
	incrementCursor,
	incrementCursorShiftDisp
}cursrMovment_t;

typedef enum DATA_TYPE{
	integer,
	string,
	floating,
}dataType_t;



typedef struct LCD_MODULE lcdmodule_t;

typedef void(*printcharLCD_t)(const uint8_t, unsigned char);
typedef void(*printcharLCDXY_t)(const uint8_t, uint8_t, uint8_t , uint8_t);
typedef void(*printstringLCD_t)(const uint8_t, char*);
typedef void(*printstringLCDXY_t)(const uint8_t, char*, uint8_t, uint8_t);
typedef void(*printintegerLCD_t)(const uint8_t, int);
typedef void(*printintegerLCDXY_t)(const uint8_t, int, uint8_t, uint8_t);
typedef void(*printfloatLCD_t)(const uint8_t, float, uint8_t);
typedef void(*printfloatLCDXY_t)(const uint8_t, float, uint8_t, uint8_t, uint8_t);
typedef	void(*shiftcursorpos_t)(const uint8_t, uint8_t, uint8_t);
typedef void(*swdispcursor_t)(const uint8_t, dispCursor_t);
typedef void(*swlinematrxst_t)(const uint8_t, lineMatrx_t);
typedef void(*selcursormovement_t)(const uint8_t, cursrMovment_t);
typedef void(*shiftdispcurright_t)(const uint8_t);
typedef void(*gohome_t)(const uint8_t);
typedef void(*go1stline_t)(const uint8_t);
typedef void(*go2ndline_t)(const uint8_t);
typedef void(*swledon_t)(const uint8_t);
typedef void(*cleardisp_t)(const uint8_t);
typedef void(*cleardisp1stline_t)(const uint8_t);
typedef void(*cleardisp2ndline_t)(const uint8_t);
typedef void(*cleardisp3rdline_t)(const uint8_t);
typedef void(*cleardisp4thline_t)(const uint8_t);

//typedef struct LCD_MODULE lcdmodule_t;

struct LCD_MODULE{
	uint8_t				addr;
	lcdType_t				type;
	lineMatrx_t			lineMatrixSel;
	dispCursor_t			dispCursorSt;
	cursrMovment_t 		cursrMovementSel;

	printcharLCD_t			PrintChar;
	printcharLCDXY_t 		PrintCharXY;
	printstringLCD_t		PrintString;
	printstringLCDXY_t		PrintStringXY;
	printintegerLCD_t		PrintInteger;
	printintegerLCDXY_t	PrintIntegerXY;
	printfloatLCD_t		PrintFloat;
	printfloatLCDXY_t		PrintFloatXY;
	shiftcursorpos_t		ShiftCursorPos;
	swdispcursor_t			SwitchDispCursor;
	swlinematrxst_t		SwitchLineMatrx;
	selcursormovement_t	SelCursorMovement;
	shiftdispcurright_t	ShiftDispCursorRight;
	gohome_t				GoHome;
	go1stline_t			Go1stLine;
	go2ndline_t			Go2ndLine;
	swledon_t				SwitchLedOn;
	cleardisp_t			ClearDisplay;
	cleardisp1stline_t  	Clear1stdispLine;
	cleardisp2ndline_t		Clear2ndDispLine;
	cleardisp3rdline_t		Clear3rdDispLine;
	cleardisp4thline_t		Clear4thDispLine;
};

void InitialiseLCD(lcdmodule_t* lcdModule);
void WriteLCDCmdReg(const uint8_t addr, uint8_t cmd);
void PrintLCDChar(const uint8_t addr, unsigned char data);
void PrintLCDCharXY16x2(const uint8_t addr, uint8_t data, uint8_t X, uint8_t Y);
void PrintLCDCharXY20x4(const uint8_t addr, unsigned char data, uint8_t X, uint8_t Y);
void PrintStringLCD(const uint8_t addr, char* data);
void PrintStringLCDXY16x2(const uint8_t addr, char* data, uint8_t X, uint8_t Y);
void PrintStringLCDXY20x4(const uint8_t addr, char* data, uint8_t X, uint8_t Y);
void PrintIntegerLCD(const uint8_t addr, int data);
void PrintIntegerLCDXY16x2(const uint8_t addr, int data, uint8_t X, uint8_t Y);
void PrintIntegerLCDXY20x4(const uint8_t addr, int data, uint8_t X, uint8_t Y);
void PrintFloatLCD(const uint8_t addr, float data, uint8_t precision);
void PrintFloatLCDXY16x2(const uint8_t addr, float data, uint8_t precision, uint8_t X, uint8_t Y);
void PrintFloatLCDXY20x4(const uint8_t addr, float data, uint8_t precision, uint8_t X, uint8_t Y);
void PrintSpecialChar(const uint8_t addr, uint8_t data[], uint8_t charPos );
void ShiftCursorPos16x2(uint8_t addr, uint8_t X, uint8_t Y);
void ShiftCursorPos20x4(uint8_t addr, uint8_t X, uint8_t Y);
void SwitchDisplayCursor(uint8_t addr, dispCursor_t state);
void SwitchLineNumMatrixState(uint8_t addr, lineMatrx_t state);
void SelCursorMovement(uint8_t addr, cursrMovment_t state);
void ClearDisplay(uint8_t addr);
void GoHome(uint8_t addr);
void ShiftDisplayCursrRight(uint8_t addr);
void GoFirstLine(uint8_t addr);
void GoSecondLine(uint8_t addr);
void ClearDisplay16x2(uint8_t addr);
void ClearDisplay20x4(uint8_t addr);
void ClearDisplay1stLine16x2(uint8_t addr);
void ClearDisplay2ndLine16x2(uint8_t addr);
void ClearDisplay1stLine20x4(uint8_t addr);
void ClearDisplay2ndLine20x4(uint8_t addr);
void ClearDisplay3rdLine20x4(uint8_t addr);
void ClearDisplay4thLine20x4(uint8_t addr);

#endif /* LCDI2C_H_ */
