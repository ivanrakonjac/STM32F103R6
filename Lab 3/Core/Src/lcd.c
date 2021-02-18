/*
 * lcd.c
 *
 *  Created on: 18.02.2021.
 *      Author: Ika
 */

#include "FreeRTOS.h"
#include <stdint.h>
#include "lcd.h"
#include "gpio.h"
#include "task.h"
#include "queue.h"

#define LCD_ENABLE_BIT 0x40

static TaskHandle_t  LCD_TaskHandle;
static QueueHandle_t LCD_QueueHandle;

/*
 * Funkcija koja vrsi 1 ciklus upisa (upisuje 4 bita)
 *
 * Postuje protokol:
 * Stavlja 1 na REGISTER_SELECT - (reg & 0x01) << 5
 * generise 0 READ/WRITE -> ne moramo nista u kodu da radimo
 * Stavlja vrednost na linije za vrednosti - (val & 0x0F);
 * setuje i resetuje ENABLE -> GPIOC->ODR |= LCD_ENABLE_BIT; GPIOC->ODR &= ~LCD_ENABLE_BIT;
 */
static void LCD_Write_4_Bits(LCD_CommandReg reg, uint8_t val){

	GPIOC->ODR = ((reg & 0x01) << 5) | (val & 0x0F);
	GPIOC->ODR |= LCD_ENABLE_BIT;
	GPIOC->ODR &= ~LCD_ENABLE_BIT;

}

/*
 * Funkcija koja upisuje 8 bita u odabrani registar u LCDu
 */
static void LCD_Write_8_Bits(LCD_CommandReg reg, uint8_t val){
	// Prvo se upisuje visih 4 bita
	LCD_Write_4_Bits(reg, val >> 4);
	//Pa nizih 4 bita
	LCD_Write_4_Bits(reg, val >> 0);

	// Umesto da citamo Busy fleg, ali lakse za implementaciju je da sacekamo koliko traje i najduza operacija
	vTaskDelay(pdMS_TO_TICKS(2));
}

static void LCD_Task(void* parameters){
	// Internal Reset Circuit (page: 23 u dokumentaciji)
	// Simuliramo to tako sto cekamo 20ms
	// Posle interne inicijalizacije mi mozemo raditi sta zelimo
	vTaskDelay(pdMS_TO_TICKS(20));

	// Setovati da saljemo podatke pomocu 4 bita
	// Posto je sirina instrukcije 8 bitova, a mi pozivamo direktno LCD_Write(), siftujemo za 4 mesta u desno
	LCD_Write_4_Bits(LCD_INSTRUCTION, (LCD_FUNCTION_SET_INSTRUCTION | LCD_FUNCTION_SET_4_BIT_INTERFACE) >> 4 );
	// Opet cekanje za svaki slucaj
	vTaskDelay(pdMS_TO_TICKS(2));

	LCD_Write_8_Bits(LCD_INSTRUCTION,
		LCD_FUNCTION_SET_INSTRUCTION |
		LCD_FUNCTION_SET_4_BIT_INTERFACE |
		LCD_FUNCTION_SET_2_LINE |
		LCD_FUNCTION_SET_5x8_DOTS);

	LCD_Write_8_Bits(LCD_INSTRUCTION,
		LCD_CONTROL_INSTRUCTION |
		LCD_CONTROL_DISPLAY_ON |
		LCD_CONTROL_CURSOR_OFF |
		LCD_CONTROL_BLINK_OFF);

	LCD_Write_8_Bits(LCD_INSTRUCTION,
		LCD_ENTRY_MODE_INSTRUCTION |
		LCD_ENTRY_MODE_INC_ADR |
		LCD_ENTRY_MODE_SHIFT_OFF);

	LCD_Command cmd;
	while(1){
		// Dohvatamo zahteve iz reda i blokiramo se ako je red prazan
		xQueueReceive(LCD_QueueHandle, &cmd, portMAX_DELAY);
		LCD_Write_8_Bits(cmd.reg, cmd.val);
	}
}

void LCD_Init(){
	LCD_QueueHandle = xQueueCreate(64, sizeof(LCD_Command));
	xTaskCreate(LCD_Task, "LCD_Task", 128, NULL, 2, &LCD_TaskHandle);
}

void LCD_CommandQueue_Put(LCD_CommandReg reg, LCD_CommandVal val)
{
	LCD_Command cmd = { reg, val };
	xQueueSend(LCD_QueueHandle, &cmd, portMAX_DELAY);
}

void LCD_CommandQueue_Put_FromISR(LCD_CommandReg reg, LCD_CommandVal val, BaseType_t *pxHigherPriorityTaskWoken)
{
	LCD_Command cmd = { reg, val };
	xQueueSendFromISR(LCD_QueueHandle, &cmd, pxHigherPriorityTaskWoken);
}
