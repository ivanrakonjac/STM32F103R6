/*
 * uart.c
 *
 *  Created on: 19.02.2021.
 *      Author: Ika
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdint.h>
#include "usart.h"

#include "uart.h"


static TaskHandle_t TransmitTaskHandle;
static QueueHandle_t TransmitQueueHandle;
static SemaphoreHandle_t TransmitMutexHandle;

static TaskHandle_t ReceiveTaskHandle;
static QueueHandle_t ReceiveQueueHandle;
static SemaphoreHandle_t ReceiveMutexHandle;



// Transmit ------------------------------------------------------------------



static void TransmitTask(void* params){

	uint8_t buffer;
	while(1){
		xQueueReceive(TransmitQueueHandle, &buffer, portMAX_DELAY);
		HAL_UART_Transmit_IT(&huart1, &buffer, sizeof(uint8_t));
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	}

}

void UART_Transmit(uint8_t character){
	xSemaphoreTake(TransmitMutexHandle, portMAX_DELAY);
	xQueueSendToBack(TransmitQueueHandle, &character, portMAX_DELAY);
	xSemaphoreGive(TransmitMutexHandle);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == huart1.Instance){

		BaseType_t woken = pdFALSE;
		vTaskNotifyGiveFromISR(TransmitTaskHandle, &woken);

		portYIELD_FROM_ISR(&woken);
	}
}


// Receive ------------------------------------------------------------------

static void ReceiveTask(void* params){

	uint8_t buffer;
	while(1){
		HAL_UART_Receive_IT(&huart1, &buffer, sizeof(uint8_t));
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		xQueueSendToBack(ReceiveQueueHandle, &buffer, portMAX_DELAY);
	}

}


uint8_t UART_Receive(){

	uint8_t buffer;
	xSemaphoreTake(ReceiveMutexHandle, portMAX_DELAY);
	xQueueReceive(ReceiveQueueHandle, &buffer, portMAX_DELAY);
	xSemaphoreGive(ReceiveMutexHandle);

	return buffer;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == huart1.Instance){

		BaseType_t woken = pdFALSE;
		vTaskNotifyGiveFromISR(ReceiveTaskHandle, &woken);

		portYIELD_FROM_ISR(&woken);
	}
}

// Initialization ------------------------------------------------------------

void UART_Init(){
	xTaskCreate(TransmitTask, "TransmitTask", 128, NULL, 4, &TransmitTaskHandle);
	TransmitQueueHandle = xQueueCreate(128, sizeof(uint8_t));
	TransmitMutexHandle = xSemaphoreCreateMutex();

	xTaskCreate(ReceiveTask, "ReceiveTask", 128, NULL, 4, &ReceiveTaskHandle);
	ReceiveQueueHandle = xQueueCreate(128, sizeof(uint8_t));
	ReceiveMutexHandle = xSemaphoreCreateMutex();

}
