#include "FreeRTOS.h"
#include "example.h"
#include "gpio.h"
#include "task.h"

void exampleTaskFunction (void* parameters);

void exampleInit() {
	xTaskCreate(exampleTaskFunction, "exampleTaskFunction0", 128, (void*) GPIO_PIN_0, 1, NULL);
	xTaskCreate(exampleTaskFunction, "exampleTaskFunction1", 128, (void*) GPIO_PIN_1, 1, NULL);

}


void exampleTaskFunction (void* parameters) {

	while(1) {
		HAL_GPIO_TogglePin(GPIOC, (uint32_t) parameters);
		vTaskDelay(1000);
	}
}
