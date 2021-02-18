/*
 * work.c
 *
 *  Created on: 18.02.2021.
 *      Author: Ika
 */
#include "FreeRTOS.h"
#include "work.h"
#include "task.h"
#include "lcd.h"

static void workTask(void *parameters)
{
	LCD_CommandQueue_Put(LCD_INSTRUCTION, LCD_SET_CG_RAM_ADDRESS_INSTRUCTION | 0x08);

	LCD_CommandQueue_Put(LCD_DATA, 0x1F);
	LCD_CommandQueue_Put(LCD_DATA, 0x1F);
	LCD_CommandQueue_Put(LCD_DATA, 0x1F);
	LCD_CommandQueue_Put(LCD_DATA, 0x1F);
	LCD_CommandQueue_Put(LCD_DATA, 0x1F);
	LCD_CommandQueue_Put(LCD_DATA, 0x1F);
	LCD_CommandQueue_Put(LCD_DATA, 0x1F);

	while (1)
	{

		LCD_CommandQueue_Put(LCD_INSTRUCTION, LCD_SET_DD_RAM_ADDRESS_INSTRUCTION | 0x00);

		for (int i= 0; i < 16; i++) {
			LCD_CommandQueue_Put(LCD_DATA, 0x01);
			vTaskDelay(pdMS_TO_TICKS(100));
		}

		LCD_CommandQueue_Put(LCD_INSTRUCTION, LCD_SET_DD_RAM_ADDRESS_INSTRUCTION | 0x40);
		for (int i= 0; i < 16; i++) {
			LCD_CommandQueue_Put(LCD_DATA, 0x01);
			vTaskDelay(pdMS_TO_TICKS(100));
		}

		vTaskDelay(pdMS_TO_TICKS(1000));

		LCD_CommandQueue_Put(LCD_INSTRUCTION, LCD_CLEAR_DISPLAY_INSTRUCTION);
	}
}

void workInit()
{
	LCD_Init();
	xTaskCreate(workTask, "workTask", 128, NULL, 5, NULL);
}
