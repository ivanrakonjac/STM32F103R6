#include "FreeRTOS.h"
#include "timers.h"
#include "example.h"
#include "gpio.h"
#include "task.h"


void callbackDeffered (void* p1, uint32_t p2);


void exampleInit() {

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_0) {
		BaseType_t  woken = pdFALSE;
		xTimerPendFunctionCallFromISR(callbackDeffered, NULL, 0, &woken);
		portYIELD_FROM_ISR(woken);
	}
}

void callbackDeffered (void* p1, uint32_t p2) {
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);
}
