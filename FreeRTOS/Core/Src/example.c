#include "FreeRTOS.h"
#include "example.h"
#include "gpio.h"
#include "task.h"

void defferedTask (void* paramteres);

TaskHandle_t defferedHandle;

void exampleInit() {
	xTaskCreate(defferedTask, "defferedTask", 128, NULL, 2, &defferedHandle);

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_0) {
		BaseType_t  woken = pdFALSE;
		vTaskNotifyGiveFromISR(defferedHandle, &woken);
		portYIELD_FROM_ISR(woken);
	}
}

void defferedTask (void* parameters) {
	while (1) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);
	}
}
