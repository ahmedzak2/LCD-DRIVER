/*
 * LCD.h
 *
 *  Created on: Mar 21, 2021
 *      Author: Ahmed Zakria
 *      Description: HEADER FILE file for the LCD driver
 */

#ifndef LCD_H_
#define LCD_H_
#include "std_types.h"
#include"common_macros.h"
#include "micro_config.h"
/**********************************************************************************
 *               Preprocessor Macros
 **********************************************************************************/
/* LCD HW Pins */
#define LCD_CRTL_PORT PORTD // COMAND  PORT
#define LCD_CRTL_PORT_DIR DDRD // COMMAND PORT Direction
#define LCD_DATA_PORT PORTC // DATA  PORT
#define LCD_DATA_PORT_DIR DDRC // DATA PORT Direction
#define RS PD4 // Select The Data or Command register
#define RW PD5 // select read or write
#define E PD6 // enable data or not

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80
/**********************************************************************************
 *                Functions Prototypes                                            *
 **********************************************************************************/
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *Str);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_intgerToString(int data);


#endif /* LCD_H_ */
