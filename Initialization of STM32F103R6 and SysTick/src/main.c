#include <stdint.h>

#include "systick.h"
#include "scb.h"
#include "nvic.h"

uint8_t const rodata[] = "VMA:FLASH, LMA:FLASH";
uint8_t data[] = "VMA:SRAM, LMA:FLASH";

uint32_t main(){



	systick_init();

	while (1){

	}

	return 0;

}
