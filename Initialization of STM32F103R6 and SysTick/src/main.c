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
//	uint32_t dummy2 = dummy / zero;

	SCB->ICSR |= (1 << 31); // Set pend bit for non maskable interrupt
	SCB->ICSR |= (1 << 28); // Set pend bit for PendSV interrupt


	// Disable all interrupts except NMI - put 1 i Fault mask register
	__asm__(
		"mov r0, 1\n"
		"msr faultmask, r0"
	);

	// Pend NMI & PENDSV at same time
	SCB->ICSR |= SCB_ISCR_NMIPENDSET | SCB_ISCR_PENDSVSET;

	// Enable all interrupts again
	__asm__(
		"mov r0, 0\n"
		"msr faultmask, r0"
	);

	// Trigger svc (The supervisor call)
	__asm__("svc 0");

	systick_init();

	while (1){

	}

	return 0;

}
