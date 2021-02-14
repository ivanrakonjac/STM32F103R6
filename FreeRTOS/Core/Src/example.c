#include "FreeRTOS.h"
#include "example.h"
#include "gpio.h"
#include "task.h"

void taskController (void* parameters);
void taskToggler (void* paramteres);

TaskHandle_t controllerHandle;
TaskHandle_t togglerHandle;

void exampleInit() {
	xTaskCreate(taskController, "controller", 128, NULL, 2, &controllerHandle);
	xTaskCreate(taskToggler, "toggler", 128, NULL, 1, &togglerHandle);

}

void taskController (void* parameters) {
	while (1) {
		xTaskNotifyGive(togglerHandle);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void taskToggler (void* paramteres) {
	while (1) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);
	}
}
