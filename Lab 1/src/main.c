#include <stdint.h>

#include "systick.h"

uint8_t const rodata[] = "IVAN RAKONJAC";
uint8_t data[] = "2020 SI";

uint32_t bss;


uint32_t main ( ) {

	systick_init();

	while (1) {
	
	}
	
	return 0;
}