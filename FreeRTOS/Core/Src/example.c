#include "FreeRTOS.h"
#include "example.h"
#include "gpio.h"
#include "task.h"

void exampleTaskFunction (void* parameters);

void exampleInit() {
	xTaskCreate(exampleTaskFunction, "exampleTaskFunction", 128, NULL, 1, NULL);
}


void exampleTaskFunction (void* parameters) {

	while(1) {
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);
		vTaskDelay(1000);
	}
}
