#include "systick.h"
#include <stdint.h>

void systick_init () {
	STK_LOAD = 8000000 - 1;
	STK_VAL = 0;
	STK_CTRL |= 0x07;
}


void __attribute__((weak)) systick_callback(){
	// Empty
}

void systick_handler () {
	systick_callback();
}
