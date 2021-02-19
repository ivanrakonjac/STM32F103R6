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

static TaskHandle_t WorkTaskHandle;

static void WORK_Task(void* params){
	while(1){
		UART_Transmit('a');
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void WORK_Init(){
	UART_Init();
	xTaskCreate(WORK_Task, "WORK_Task", 128, NULL, 5, &WorkTaskHandle);
}
