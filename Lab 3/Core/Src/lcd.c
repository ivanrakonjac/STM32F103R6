/*
 * lcd.c
 *
 *  Created on: 19.02.2021.
 *      Author: Ika
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "lcd.h"
#include "gpio.h"
#include <stdint.h>

#define LCD_ENABLE_BIT 0x40

static TaskHandle_t LCD_TaskHandle;
static QueueHandle_t LCD_QueueHandle;


void LCD_Write_4_Bits(LCD_CommandReg reg, uint8_t val){
	GPIOC->ODR = ((reg & 0x01) << 5) | (val & 0x0F);
	// Timing Characteristics (page: 52, 58) ?
	GPIOC->ODR |= LCD_ENABLE_BIT;
	GPIOC->ODR &= ~LCD_ENABLE_BIT;
}

static void LCD_CommandInitiate(LCD_CommandReg reg, uint8_t val)
{
	// 4-bit interfacing to the MPU (page: 22)
	LCD_Write_4_Bits(reg, val >> 4);
	LCD_Write_4_Bits(reg, val >> 0);
	vTaskDelay(pdMS_TO_TICKS(2));
}


static void LCD_Task(void* params){

	vTaskDelay(pdMS_TO_TICKS(20));


	LCD_Write_4_Bits(LCD_INSTRUCTION,
			(LCD_FUNCTION_SET_INSTRUCTION | LCD_FUNCTION_SET_4_BIT_INTERFACE) >> 4);
	vTaskDelay(pdMS_TO_TICKS(2));

	LCD_CommandInitiate(LCD_INSTRUCTION,
			LCD_FUNCTION_SET_INSTRUCTION |
				LCD_FUNCTION_SET_4_BIT_INTERFACE |
				LCD_FUNCTION_SET_2_LINE |
				LCD_FUNCTION_SET_5x8_DOTS
				);

	LCD_CommandInitiate(LCD_INSTRUCTION,
			LCD_CONTROL_INSTRUCTION |
				LCD_CONTROL_DISPLAY_ON |
				LCD_CONTROL_CURSOR_ON |
				LCD_CONTROL_BLINK_ON
				);

	LCD_CommandInitiate(LCD_INSTRUCTION,
			LCD_ENTRY_MODE_INSTRUCTION |
				LCD_ENTRY_MODE_INC_ADR |
				LCD_ENTRY_MODE_SHIFT_OFF
				);


	LCD_Command cmd;
	while(1){
		xQueueReceive(LCD_QueueHandle, &cmd, portMAX_DELAY);
		LCD_CommandInitiate(cmd.reg, cmd.val);
	}
}


void LCD_Init(){
	LCD_QueueHandle = xQueueCreate(2, sizeof(LCD_Command));
	xTaskCreate(LCD_Task, "LCD_Task", 128, NULL, 2, &LCD_TaskHandle);
}

void LCD_PutInQueue(LCD_CommandReg reg, uint8_t val){
	LCD_Command cmd = {reg, val};
	xQueueSendToBack(LCD_QueueHandle,&cmd,portMAX_DELAY);
}
