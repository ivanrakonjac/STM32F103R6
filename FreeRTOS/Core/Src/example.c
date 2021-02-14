#include "FreeRTOS.h"
#include "timers.h"
#include "queue.h"
#include "example.h"
#include "gpio.h"
#include "task.h"

QueueHandle_t queueHandle;


void taskToggler (void* parameters);


void exampleInit() {
	queueHandle = xQueueCreate(10, sizeof(uint32_t));
	xTaskCreate(taskToggler, "taskToggler", 128, NULL, 2, NULL);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	uint32_t itemToQueue = GPIO_Pin;
	BaseType_t  woken = pdFALSE;
	xQueueSendToBackFromISR(queueHandle, &itemToQueue, &woken);
	portYIELD_FROM_ISR(woken);
}

void taskToggler (void* parameters) {
	uint32_t bufferForPinIndex;
	while (1) {
		xQueueReceive(queueHandle, &bufferForPinIndex, portMAX_DELAY);
		HAL_GPIO_TogglePin(GPIOC, bufferForPinIndex);
	}
}
