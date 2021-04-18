/*
 * LCD.c
 *
 *  Created on: Mar 21, 2021
 *      Author: Ahmed zakria
 *      Description: Source file for the LCD driver
 */


#include"LCD.h"

void LCD_init(void)
{

	LCD_DATA_PORT_DIR=0xff;
	LCD_CRTL_PORT_DIR |=(1<<RS) |(1<<RW) |(1<<E);
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); // use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode
	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
}

void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CRTL_PORT,RS);// MAKE RS REGITER IS COMMAND REGISTER
	CLEAR_BIT(LCD_CRTL_PORT,RW);// MAKE RW REGITER IS WRITE
	_delay_ms(1); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_CRTL_PORT,E); // ENBALE DATA
	_delay_ms(1); /* delay for processing Tas = 50ns */
	LCD_DATA_PORT = command;
	_delay_ms(1);
	CLEAR_BIT(LCD_CRTL_PORT,E); // DISBALE DATA
	_delay_ms(1); /* delay for processing Tas = 50ns */
}
void LCD_displayCharacter(uint8 data)
{
	SET_BIT(LCD_CRTL_PORT,RS);// MAKE RS REGITER IS DATA REGISTER
	CLEAR_BIT(LCD_CRTL_PORT,RW);// MAKE RW REGITER IS WRITE
	_delay_ms(1); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_CRTL_PORT,E); // ENBALE DATA
	_delay_ms(1); /* delay for processing Tas = 50ns */
	LCD_DATA_PORT = data;
	_delay_ms(1);
	CLEAR_BIT(LCD_CRTL_PORT,E); // DISBALE DATA
	_delay_ms(1); /* delay for processing Tas = 50ns */

}
void LCD_displayString(const char *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}
	void LCD_clearScreen(void)
	{
		LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */

	}

			void LCD_goToRowColumn(uint8 row,uint8 col)
			{
				uint8 address;
				switch(row)
				{
				case 0:
					address =col;// start at line 2
					break;
				case 1:
					address =col+0x40; // start at line 2
					break;
				case 2:
					address =col+0x10;  // start at line 3
					break;
				case 3:
					address =col+0x50;  // start at line 4
					break;
				}
				/* to write to a specific address in the LCD
					 * we need to apply the corresponding command 0b10000000+Address */
					LCD_sendCommand(address | SET_CURSOR_LOCATION);
			}

			void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
			{
				LCD_goToRowColumn(row,col); /* go to to the required LCD position */
				LCD_displayString(Str); /* display the string */
			}
			void LCD_intgerToString(int data)
			{
				 char buff[16]; /* String to hold the ascii result */
				   itoa(data,buff,10); /* 10 for decimal */
				   LCD_displayString(buff);
			}
