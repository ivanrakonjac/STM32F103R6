#include <stdint.h>
#include "systick.h"

uint8_t const rodata[] = "VMA:FLASH, LMA:FLASH";
uint8_t data[] = "VMA:SRAM, LMA:FLASH";

uint32_t bss; //VMA:RAM, LMA:nije ni bitna jer se nigde ne ucitava

void systick_callback () {
	++bss;
}

uint32_t main(){
	bss = 0;

	systick_init();

	while (1){

	}

	return 0;

}
