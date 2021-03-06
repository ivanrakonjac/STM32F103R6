#include <stdint.h>

#include "systick.h"
#include "scb.h"
#include "nvic.h"
#include "utility.h"

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


	// Enable interrupts
	NVIC_ENABLE_IRQ(0);
	NVIC_ENABLE_IRQ(1);
	NVIC_ENABLE_IRQ(2);
	NVIC_ENABLE_IRQ(3);

	// Set pendig bits
	NVIC->ISPR[0] |= 0x0F;

	// Set priority group-prigroup bits
	SCB_AIRCR_PRIGROUP(3);

	// Set interrupts priority
	NVIC_SET_PRIORITY(0, 0x70);	//01.11
	NVIC_SET_PRIORITY(1, 0x60);	//01.10
	NVIC_SET_PRIORITY(2, 0x50); //01.01
	NVIC_SET_PRIORITY(3, 0x40); //01.00
						//60  ==  01.00 - a za izvrsavanje se gleda samo grupa

	NVIC->ISPR[0] |= 0x0F;

	// Setting of base priority (minimum priority which interrupt should have to be executed)
	__asm__(
		"mov r0, 0x30\n"
		"msr basepri, r0"
	);

	NVIC->ISPR[0] |= 0x0F;

	// Clear pending bits
	NVIC->ISPR[0] |= 0x00;

	SCB_AIRCR_PRIGROUP(3);

	NVIC->ISPR[0] |= 0x0F;

	// Moving to user mode
	__asm__(
		"mov r0, 0x01\n"
		"msr control, r0"
	);

	// Moving to privileged mode
	__asm__("svc 0");

	systick_init();

	while (1){

	}

	return 0;

}
