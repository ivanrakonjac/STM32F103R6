#include "systick.h"
#include <stdint.h>

void systick_init () {
	STK->LOAD = 8000000 - 1;
	STK->VAL = 0;
	STK->CTRL |= 0x07;
}


void __attribute__((weak)) systick_callback(){
	// Empty
}
