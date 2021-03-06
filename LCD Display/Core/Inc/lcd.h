/*
 * lcd.h
 *
 *  Created on: 15.02.2021.
 *      Author: Ika
 */

#ifndef CORE_INC_LCD_H_
#define CORE_INC_LCD_H_

#include <stdint.h>

#define LCD_CLEAR_DISPLAY_INSTRUCTION		0x01

#define LCD_RETURN_HOME_INSTRUCTION			0x02

#define LCD_ENTRY_MODE_INSTRUCTION			0x04
#define LCD_ENTRY_MODE_INC_ADR				0x02
#define LCD_ENTRY_MODE_DEC_ADR				0x00
#define LCD_ENTRY_MODE_SHIFT_ON				0x01
#define LCD_ENTRY_MODE_SHIFT_OFF			0x00

#define LCD_CONTROL_INSTRUCTION				0x08
#define LCD_CONTROL_DISPLAY_ON				0x04
#define LCD_CONTROL_DISPLAY_OFF				0x00
#define LCD_CONTROL_CURSOR_ON				0x02
#define LCD_CONTROL_CURSOR_OFF				0x00
#define LCD_CONTROL_BLINK_ON				0x01
#define LCD_CONTROL_BLINK_OFF				0x00

#define LCD_FUNCTION_SET_INSTRUCTION		0x20
#define LCD_FUNCTION_SET_8_BIT_INTERFACE	0x10
#define LCD_FUNCTION_SET_4_BIT_INTERFACE	0x00
#define LCD_FUNCTION_SET_2_LINE				0x08
#define LCD_FUNCTION_SET_1_LINE				0x00
#define LCD_FUNCTION_SET_5x10_DOTS			0x04
#define LCD_FUNCTION_SET_5x8_DOTS			0x00

#define LCD_SHIFT_INSTRUCTION				0x10
#define LCD_SHIFT_CURSOR					0x00
#define LCD_SHIFT_DISPLAY					0x08
#define LCD_SHIFT_DIRECTION_RIGHT			0x04
#define LCD_SHIFT_DIRECTION_LEFT			0x00

#define LCD_SET_CG_RAM_ADDRESS_INSTRUCTION	0x40
#define LCD_SET_DD_RAM_ADDRESS_INSTRUCTION	0x80

// Govori nam da li je DATA ili INSTRUKCTION registar
typedef enum {
	LCD_INSTRUCTION = 0,
	LCD_DATA
} LCD_CommandReg;

// Za prosledjivanje koda funkcije LCD kontroleru
typedef uint8_t LCD_CommandVal;

// Struktura koja se nalazi u redu, iz koga Task uzima zahteve za izvrsavanje
typedef struct {
	LCD_CommandReg reg;
	LCD_CommandVal val;
}LCD_Command;

extern void LCD_Init();

extern void LCD_CommandEnqueue(LCD_CommandReg reg, LCD_CommandVal val);

extern void LCD_CommandEnqueueFromISR(LCD_CommandReg reg, LCD_CommandVal val, BaseType_t* pxHigherPriorityTaskWoken);

#endif /* CORE_INC_LCD_H_ */
