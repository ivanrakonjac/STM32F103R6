/*
 * example.c
 *
 *  Created on: 16.02.2021.
 *      Author: Ika
 */
#include "FreeRTOS.h"
#include "task.h"
#include "example.h"
#include "uart_driver.h"
#include "gpio.h"

/*
 * TOK:
 * Iz main.c se poziva exampleInit ()
 * Iz exampleInit() se poziva UART_Init() i kreira se Task koji radi sa UARTom
 * U UART_Init() se kreira unutrasnji UART Task koji prima i transmituje karatkere iz Queuea
 */

/*
 * Task koji nam radi sa UARTom
 */
static void exampleTask(void* parameters){

	/*char character = UART_BlockReceiveCharacter();
	UART_AsyncTransmitChar(character);

	char* string = UART_BlockReceiveString();
	UART_AsyncTransmitString(string);
	vPortFree(string);

	UART_AsyncTransmitChar('M');
	UART_AsyncTransmitString("IPS_");
	UART_AsyncTransmitDecimal(2020);
	UART_AsyncTransmitChar('\r');*/


	while(1){

		UART_AsyncTransmitString("Uneti redni broj diode [1-4] \r");
		uint32_t index = UART_BlockReceiveDecimal();

		if(index >= 1 && index <= 4) {
			HAL_GPIO_TogglePin(GPIOC, 0x01 << (index - 1));
		}
	}
}

/*
 * Funkcija za inicijalizaciju UARTa i Taska koji sa UARTom radi
 */
void exampleInit(){
	UART_Init();
	xTaskCreate(exampleTask, "exampleTask", 128, NULL, 10, NULL);
}




