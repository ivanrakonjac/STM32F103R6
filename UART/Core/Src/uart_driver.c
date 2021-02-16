/*
 * uart_driver.c
 *
 *  Created on: 16.02.2021.
 *      Author: Ika
 */

#include "FreeRTOS.h"
#include "uart_driver.h"
#include "queue.h"
#include "task.h"
#include "usart.h"
#include <stdint.h>


static TaskHandle_t UART_TransmitTaskHandle;
static QueueHandle_t UART_TransmitQueueHandle;

static void UART_TransmitTask(void* parameters){
	uint8_t buffer;
	while(1){
		xQueueReceive(UART_TransmitQueueHandle, &buffer, portMAX_DELAY);
		HAL_UART_Transmit_IT(&huart1, &buffer, sizeof(uint8_t));
		// ovde se blokiramo dok nas neko ne obavesti da mozemo da nastavimo
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	}
}

/*
 * Funkcija za inicijalizaciju UARTA
 * Pravimo Task i Queue
 * Poziva se iz nekog fajla spolja
 */
void UART_Init(){
	xTaskCreate(UART_TransmitTask, "UART_TransmitTask", 128, NULL, 4, &UART_TransmitTaskHandle);
	UART_TransmitQueueHandle = xQueueCreate(128, sizeof(uint8_t));
}

/*
 * This function handles UART interrupt request.
 * I to pri svim slucajevima (slanje i primanje i error...)
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart){
	if(huart->Instance == huart1.Instance){
		BaseType_t woken;
		// obavestavamo UART_TransmitTask da moze da nastavi svoje izvrsavanje
		vTaskNotifyGiveFromISR(UART_TransmitTaskHandle, &woken);
	}
}

/*
 * Asinhrono vrsi slanje 1 karaktera putem uarta
 */
void UART_AsyncTransmit(char character){
	xQueueSendToBack(UART_TransmitQueueHandle,&character, portMAX_DELAY);
}
