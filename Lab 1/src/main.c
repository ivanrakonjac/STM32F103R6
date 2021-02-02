#include <stdint.h>

#include "systick.h"
#include "nvic.h"

uint8_t const rodata[] = "IVAN RAKONJAC";
uint8_t data[] = "2020 SI";

uint32_t bss;


uint32_t main ( ) {

	NVIC_ENABLE_IRQ(0);
	NVIC_ENABLE_IRQ(1);
	NVIC_ENABLE_IRQ(2);

	NVIC->ISPR[0] |= 0b111;

	systick_init();

	while (1) {
	
	}
	
	return 0;
}
