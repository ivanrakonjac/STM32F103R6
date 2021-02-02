#include <stdint.h>

#include "systick.h"

void systick_init()
{
	STK->LOAD = 8000000 - 1;
	STK->VAL = 0;
	STK->CTRL |= 0x07;
}

void systick_handler () {
	int test = 0;
}
