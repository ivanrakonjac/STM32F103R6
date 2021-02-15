#include "FreeRTOS.h"
#include "timers.h"
#include "queue.h"
#include "example.h"
#include "gpio.h"
#include "task.h"
#include "lcd.h"


static void exampleTask (void* parameters) {
	char line1[16] = "Mikroprocesorski";

	// Stavljamo instrukciju u red, koja postavlja adresu na 0
	LCD_CommandEnqueue(LCD_INSTRUCTION, LCD_SET_DD_RAM_ADDRESS_INSTRUCTION | 0x00);

	for (uint32_t i = 0; i < 16; i++) {
		LCD_CommandEnqueue(LCD_DATA, line1[i]);
		vTaskDelay(pdMS_TO_TICKS(100));
	}

	while(1){

	}
}

void exampleInit() {
	LCD_Init();
	xTaskCreate(exampleTask, "exampleTask", 128, NULL, 5, NULL);
}
