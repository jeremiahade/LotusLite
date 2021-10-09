#include <atmel_start.h>
#include "i2cmasterdrv.h"
#include "lcdi2c.h"
#include <util/delay.h>
#include <string.h>

#define DISPLAY_COLUMN 4

//SCL - PC5
//SDA - PC4

int testVal = 0;
uint8_t currentPage = 2, prevPage = 0, nextPage = 0, currentSubPage = 1;
uint8_t cursorPositionX = 1, cursorPositionY = 0;
uint8_t cwFlag, ccwFlag, btnSelFlag = 0;

/******Menu Functions Declaration************************************************/
void DisplayFrontPage(uint8_t addr);
void DisplaySettingsMenu(uint8_t addr, uint8_t subpageSel);
void DisplayManualMixMenu(uint8_t addr, uint8_t subPage);
void DisplayColourSelMenu(uint8_t addr, uint8_t subPage);
int GetMenuItemCount(char *item[]);


//Front Page title and items declarations
/**********************************************************/
char *frontPageTitle = "Welcome  Leticia";
char *frontPageItems[] = {"RED", "BLUE",
						  "GRN",  "WW"};

//Settings Menu title and items declaration
/*********************************************************/
char *settingsTitle = "SETTINGS MENU";
char *settingsItems[] = {"Colour Selection",
					   "Brightness",
					   "Manual Mix"};

//Manual mix sub settings title and items declaration
/**********************************************************/
char *manualmixTitle = "Manual Mix";
char *manualmixItems[] = {"RED",
						  "BLUE",
						  "GRN",
						  "WW"};

//Colour Selection Menu title and items declarations
/********************************************************/
char *colourSelTitle = "Colour Selection";
char *colouritems[] =	{"RED",
						 "GREEN",
						 "BLUE",
						 "WHITE"
						 "WHITE+WW",
						 "RED+GRN",
						 "RED+BLUE",
						 "BLUE+GRN"};

//LCD Module type declaration
/********************************************************/
lcdmodule_t lcdLarge;


int main(void)
{

	lcdLarge.addr = 0x27;

	testVal = 60;

	lcdLarge.addr = 0x27;
	lcdLarge.type = LCD20x4;
	lcdLarge.cursrMovementSel = incrementCursor;
	lcdLarge.dispCursorSt = dispOn_CursorBlink;
	lcdLarge.lineMatrixSel = twolines_5x8Matrix;
	lcdLarge.addr = 0x27;
	lcdLarge.type = LCD20x4;
	lcdLarge.cursrMovementSel = incrementCursor;
	lcdLarge.dispCursorSt =dispOn_Cursoroff;
	lcdLarge.lineMatrixSel = twolines_5x8Matrix;
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	InitialiseI2C();
	//InitialiseLCD(&lcd1);
	InitialiseLCD(&lcdLarge);

	currentPage = 4;

	/* Replace with your application code */
	while (1) {
		switch(currentPage)
		{
			case 1:
			DisplayFrontPage(lcdLarge.addr);
			break;

			case 2:
			DisplaySettingsMenu(lcdLarge.addr, 2);
			break;

			case 3:
			DisplayManualMixMenu(lcdLarge.addr, 2);
			break;

			case 4:
			DisplayColourSelMenu(lcdLarge.addr, 4);
			break;

			default:
			lcdLarge.PrintStringXY(lcdLarge.addr, "404: Page Error", 1, 2);
			break;
		}
		//Display front page
		//DisplayFrontPage(lcdLarge.addr);
		//lcdLarge.PrintString(lcdLarge.addr, "wwwwasre ");
		}
		//return 0;
}

int GetMenuItemCount(char *item[])
{
	  int count = 0;

	  while (strcmp("\0", item[count]) != 0)
	  {
		  count++;
	  }

	PrintIntegerLCDXY20x4(0x27, count, 3, 3);
	return count;
}

int GetPageSize(char *item[], int dispcolumn)
{
	int size, page =0, pagebuff= 0;
	float pagefltBuff = 0.00;
	//pagefltBuff = (float)(count)/(float)(dispcolumn);

	if (pagefltBuff == 1.0)
	{
		page = 1;
	}
	if (pagefltBuff > 0 && pagefltBuff <1)
	{
		page = 1;
	}
	if (pagefltBuff > 1)
	{
		pagebuff = (int)pagefltBuff;
		if ((pagefltBuff - pagebuff) != 0)
		{
			page = pagebuff + 1;
		}
		else if ((pagefltBuff - pagebuff) == 0)
		{
			page = pagebuff;
		}

	}
	return page;
}

void DisplayFrontPage(uint8_t addr)
{
	int count = 0;
	//lcdLarge.Clear1stdispLine(addr);
	//ClearDisplay20x4(addr);
	//lcdLarge.PrintStringXY(addr, frontPageTitle, 4,0);
	PrintStringLCDXY20x4(addr, frontPageTitle, 2,0);
	for(int i = 1; i < 3; i++)
	{
			PrintStringLCDXY20x4(addr, frontPageItems[i-1], 1, i);
			count = i;
			//PrintIntegerLCDXY20x4(addr, count, 1, 5);
	}
	for(int i = count; i < 4; i++)
	{
		PrintStringLCDXY20x4(addr, frontPageItems[i], 12, i-1);
	}
	PrintLCDCharXY20x4(addr, FORWARD_ARROW, 15,3);
	PrintStringLCDXY20x4(addr, settingsTitle, 16, 3);
	PrintIntegerLCDXY20x4(addr, testVal, 6, 1);

}

void DisplaySettingsMenu(uint8_t addr, uint8_t subpageSel)
{
	//int itemCount = 0;
	PrintStringLCDXY20x4(addr, settingsTitle, 2, 0);
	//itemCount = GetMenuItemCount(settingsItems);
	switch (subpageSel)
	{
		case 1:
		for (int i = 1; i <DISPLAY_COLUMN-1; i++)
		{
			PrintStringLCDXY20x4(addr, settingsItems[i-1], 1, i);
		}
		break;
		case 2:
			PrintStringLCDXY20x4(addr, settingsItems[2], 1, 1);
		break;
		default:
		break;

	}
	PrintLCDCharXY20x4(addr, FORWARD_ARROW, cursorPositionY,cursorPositionX);
	PrintStringLCDXY20x4(addr, "HOME", 16, 3);

}

void DisplayColourSelMenu(uint8_t addr, uint8_t subPage)
{
	uint8_t page2itemoffset = 2;
	uint8_t page3ItemOffset = 4;
	uint8_t page4ItemOffset = 5;
	PrintStringLCDXY20x4(addr, colourSelTitle , 2, 0);
	switch (subPage)
	{
		case 1:
		for (int i = 1; i <DISPLAY_COLUMN-1; i++)
		{
			PrintStringLCDXY20x4(addr, colouritems[i-1], 1, i);
		}
		break;

		case 2:
		for (int i = 1; i <DISPLAY_COLUMN-1; i++)
		{
			PrintStringLCDXY20x4(addr, colouritems[page2itemoffset], 1, i);
			page2itemoffset++;
		}
		break;

		case 3:
		for (int i = 1; i <DISPLAY_COLUMN-1; i++)
		{
			PrintStringLCDXY20x4(addr, colouritems[page3ItemOffset], 1, i);
			page3ItemOffset++;
		}
		break;

		case 4:
		for (int i = 1; i <DISPLAY_COLUMN-1; i++)
		{
			PrintStringLCDXY20x4(addr, colouritems[page4ItemOffset], 1, i);
			page4ItemOffset++;
		}
		break;

		default:
		break;

	}
	PrintLCDCharXY20x4(addr, FORWARD_ARROW, cursorPositionY,cursorPositionX);
	PrintStringLCDXY20x4(addr, "MENU", 16, 3);
}

void DisplayManualMixMenu(uint8_t addr, uint8_t subPage)
{
	uint8_t page2itemoffset = 2;
	PrintStringLCDXY20x4(addr, manualmixTitle, 2, 0);
	switch (subPage)
	{
		case 1:
		for (int i = 1; i <DISPLAY_COLUMN-1; i++)
		{
			PrintStringLCDXY20x4(addr, manualmixItems[i-1], 1, i);
		}
		break;
		case 2:
		for (int i = 1; i <DISPLAY_COLUMN-1; i++)
		{
			PrintStringLCDXY20x4(addr, manualmixItems[page2itemoffset], 1, i);
			page2itemoffset++;
		}
		break;
		default:
		break;

	}
	PrintLCDCharXY20x4(addr, FORWARD_ARROW, cursorPositionY,cursorPositionX);
	PrintStringLCDXY20x4(addr, "MENU", 16, 3);
}
