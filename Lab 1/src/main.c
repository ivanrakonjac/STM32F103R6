#include <stdint.h>

#include "systick.h"
#include "nvic.h"
#include "scb.h"

uint8_t const rodata[] = "IVAN RAKONJAC";
uint8_t data[] = "2020 SI";

uint32_t bss;


uint32_t main ( ) {

	// PRIGROUP = 0b101 => 0bxx.yyyyyy
	SCB_AIRCR_PRIGROUP(5);

	NVIC_ENABLE_IRQ(0);
	NVIC_ENABLE_IRQ(1);
	NVIC_ENABLE_IRQ(2);

	// IRQNUM0_PRI = 0b10.100000; 80|20; GroupPri: 2 SubPri: 2
	NVIC_SET_PRIORITY(0, 0xA0);
	// IRQNUM1_PRI = 0b10.000000; 80|00; GroupPri: 2 SubPri: 0
	NVIC_SET_PRIORITY(1, 0x80);
	// IRQNUM2_PRI = 0b10.010000; 80|10; GroupPri: 2 SubPri: 1
	NVIC_SET_PRIORITY(2, 0x90);

	NVIC->ISPR[0] |= 0b111;

	// USG_FLT_PRI = 0b01.000000; 40|00; GroupPri: 1 SubPri: 0
	// BUS_FLT_PRI = 0b01.000000; 40|00; GroupPri: 1 SubPri: 0
	// MEM_FLT_PRI = 0b01.000000; 40|00; GroupPri: 1 SubPri: 0
	SCB->SHPR1 = (0x40 << 16) | (0x40 << 8) | (0x40 << 0);
	// SVC_EXC_PRI = 0b01.000000; 40|00; GroupPri: 1 SubPri: 0
	SCB->SHPR2 = (0x40 << 24);
	// SYSTICK_PRI = 0b00.000000; 00|00; GroupPri: 0 SubPri: 0
	// PEND_SV_PRI = 0b01.000000; 40|00; GroupPri: 1 SubPri: 0
	SCB->SHPR3 = (0x00 << 24) | (0x40 << 16);

	systick_init();

	while (1) {
	
	}
	
	return 0;
}
