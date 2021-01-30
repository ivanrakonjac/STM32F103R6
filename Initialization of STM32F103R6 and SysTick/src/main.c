#include <stdint.h>

#include "systick.h"
#include "scb.h"
#include "nvic.h"

uint8_t const rodata[] = "VMA:FLASH, LMA:FLASH";
uint8_t data[] = "VMA:SRAM, LMA:FLASH";

uint32_t main(){

	SCB->CCR |= (1 << 4); // Catch dividing by 0 as an error
	SCB->SHCSR |= (1 << 18); //Enable usage fault


	uint32_t dummy = 1, zero = 0;
	uint32_t dummy2 = dummy / zero;

	systick_init();

	while (1){

	}

	return 0;

}
