/*
 * work.c
 *
 *  Created on: 19.02.2021.
 *      Author: Ika
 */
#include "FreeRTOS.h"
#include "work.h"
#include "uart.h"
#include "task.h"
#include "lcd.h"

static TaskHandle_t WorkTaskHandle;

static void WORK_Task(void* params){

	char c='a';
	uint32_t counter = 0;

	LCD_PutInQueue(LCD_INSTRUCTION, LCD_SET_DD_RAM_ADDRESS_INSTRUCTION | 0x00);

	while(1){

		c = UART_Receive();
		UART_Transmit(c);
		UART_Transmit('\r');

		LCD_PutInQueue(LCD_DATA, c);

		if(counter == 16){
			LCD_PutInQueue(LCD_INSTRUCTION, LCD_SET_DD_RAM_ADDRESS_INSTRUCTION | 0x40);

		}

		counter++;

		if(counter == 33){
			counter = 0;
			LCD_PutInQueue(LCD_INSTRUCTION, LCD_SET_DD_RAM_ADDRESS_INSTRUCTION | 0x00);
			LCD_PutInQueue(LCD_INSTRUCTION, LCD_CLEAR_DISPLAY_INSTRUCTION);
		}





		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void WORK_Init(){
	UART_Init();
	LCD_Init();
	xTaskCreate(WORK_Task, "WORK_Task", 64, NULL, 5, &WorkTaskHandle);
}
