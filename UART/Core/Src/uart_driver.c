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
#include "semphr.h"

#include <stdint.h>
#include "string.h"

// TRANSMIT
// -----------------------------------------------------------------------------

static SemaphoreHandle_t UART_TransmitMutexHandle;
static TaskHandle_t UART_TransmitTaskHandle;
static QueueHandle_t UART_TransmitQueueHandle;

/*
 * Task za slanje podataka preko prekidne rutine
 */
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
 * Tx Transfer completed callback.
 * Znaci ulazi se u ovu funkciju kada je transfer zavrsen.
 * Mi ulazimo da bi obavestili Task za slanje da je podatak transferovan i da moze da nastavi.
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart){
	if(huart->Instance == huart1.Instance){
		BaseType_t woken;
		// obavestavamo UART_TransmitTask da moze da nastavi svoje izvrsavanje
		vTaskNotifyGiveFromISR(UART_TransmitTaskHandle, &woken);

		// Eksplcitan zahtev za promenu konteksta
		portYIELD_FROM_ISR(woken);
	}
}

// RECEIVE
// -----------------------------------------------------------------------------

static SemaphoreHandle_t UART_ReceiveMutexHandle;
static TaskHandle_t UART_ReceiveTaskHandle;
static QueueHandle_t UART_ReceiveQueueHandle;


/*
 * Task za primanje podataka preko prekidne rutine
 */
static void UART_ReceiveTask(void* parameters){

	uint8_t buffer;

	while(1){
		HAL_UART_Receive_IT(&huart1, &buffer, sizeof(uint8_t));
		// ovde se blokiramo dok nas neko ne obavesti da je podatak primljen
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		xQueueSendToBack(UART_ReceiveQueueHandle, &buffer, portMAX_DELAY);
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == huart1.Instance){
		BaseType_t woken;
		// obavestavamo UART_ReceiveTask da moze da nastavi svoje izvrsavanje (podatak primljen)
		vTaskNotifyGiveFromISR(UART_ReceiveTaskHandle, &woken);
		portYIELD_FROM_ISR(woken);
	}
}


// GENERAL
// -----------------------------------------------------------------------------

/*
 * Funkcija za inicijalizaciju UARTA
 * Pravimo Task i Queue
 * Poziva se iz nekog fajla spolja
 */
void UART_Init(){

	xTaskCreate(UART_ReceiveTask, "UART_ReceiveTask", 128, NULL, 5, &UART_ReceiveTaskHandle);
	UART_ReceiveQueueHandle = xQueueCreate(128, sizeof(uint8_t));
	UART_ReceiveMutexHandle = xSemaphoreCreateMutex();

	xTaskCreate(UART_TransmitTask, "UART_TransmitTask", 128, NULL, 4, &UART_TransmitTaskHandle);
	UART_TransmitQueueHandle = xQueueCreate(128, sizeof(uint8_t));
	UART_TransmitMutexHandle = xSemaphoreCreateMutex();
}

// TRANSMIT UTIL
// -----------------------------------------------------------------------------


/*
 * Asinhrono vrsi stavljanje 1 karaktera na kraj reda
 */
void UART_AsyncTransmitChar(char character){
	xSemaphoreTake(UART_TransmitMutexHandle, portMAX_DELAY);

	xQueueSendToBack(UART_TransmitQueueHandle,&character, portMAX_DELAY);

	xSemaphoreGive(UART_TransmitMutexHandle);
}

/*
 * Asinhrono vrsi stavljanje stringa na kraj reda
 */
void UART_AsyncTransmitString(char const* string){

	if(string != NULL){
		xSemaphoreTake(UART_TransmitMutexHandle, portMAX_DELAY);

		for (int i = 0; i < strlen(string); ++i) {
			xQueueSendToBack(UART_TransmitQueueHandle,string + i, portMAX_DELAY);
		}

		xSemaphoreGive(UART_TransmitMutexHandle);
	}

}

/*
 * Asinhrono vrsi stavljanje broja kao niza karaktera na kraj reda
 */
void UART_AsyncTransmitDecimal(uint32_t decimal){

	xSemaphoreTake(UART_TransmitMutexHandle, portMAX_DELAY);

	char digits[32];
	uint32_t index = 32;

	while (index >= 0 && decimal != 0){
		digits[--index] = '0' + decimal % 10;
		decimal /= 10;
	}

	for (int i = index; i < 32; i++) {
		xQueueSendToBack(UART_TransmitQueueHandle,digits + i, portMAX_DELAY);
	}

	xSemaphoreGive(UART_TransmitMutexHandle);


}

// RECEIVE UTIL
// -----------------------------------------------------------------------------

char UART_BlockReceiveCharacter(){
	xSemaphoreTake(UART_ReceiveMutexHandle, portMAX_DELAY);

	char character;
	xQueueReceive(UART_ReceiveQueueHandle, &character, portMAX_DELAY);

	xSemaphoreGive(UART_ReceiveMutexHandle);

	return character;
}

char* UART_BlockReceiveString(){
	xSemaphoreTake(UART_ReceiveMutexHandle, portMAX_DELAY);

	char* string = pvPortMalloc(64);

	if(string != NULL){
		char character = '\0';
		uint32_t index = 0;
		while (character != '\r' && index < 64 ){
			xQueueReceive(UART_ReceiveQueueHandle, &character, portMAX_DELAY);
			string[index++] = character;
		}
		string[--index] = character;
	}

	xSemaphoreGive(UART_ReceiveMutexHandle);

	return string;
}
