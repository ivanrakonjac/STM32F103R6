#include "systick.h"

void nmi_handler () {

}

void hard_fault_handler () {

}

void uasge_fault_handler () {

}

void sv_call_handler () {

}

void pend_sv_handler () {
	__asm__(
		"mov r0, 0x00\n"
		"msr control, r0"
	);
}

void systick_handler () {

}


void irq0_WWDG () {

}

void irq1_PVD () {

}

void irq2_TAMPER () {

}

void irq3_RTC () {

}
