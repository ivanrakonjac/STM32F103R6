.cpu cortex-m3
.fpu softvfp
.syntax unified
.thumb

.extern _main_stack_pointer_value

.weak systick_handler
.thumb_set systick_handler, default_handler

.weak irq0_WWDG
.thumb_set irq0_WWDG, default_handler

.weak irq1_PVD
.thumb_set irq1_PVD, default_handler

.weak irq2_TAMPER
.thumb_set irq2_TAMPER, default_handler

.weak irq3_RTC
.thumb_set irq3_RTC, default_handler

.section .vector_table, "a"
.word _main_stack_pointer_value
.word reset_handler
.rept 13
	.word default_handler
.endr
.word systick_handler
.word irq0_WWDG
.word irq1_PVD
.word irq2_TAMPER
.word irq3_RTC
.rept 64
	.word default_handler
.endr

.extern main

.extern _lma_data_start
.extern _vma_data_start
.extern _vma_data_end

.section .text.reset_handler
.type reset_handler, %function
reset_handler:
	ldr r0, =_lma_data_start
	ldr r1, =_vma_data_start
	ldr r2, =_vma_data_end
	
	cmp r1, r2
	beq branch_to_main
	
copy_loop:
	ldr r3, [r0], #4
	str r3, [r1], #4
	cmp r1, r2
	blo copy_loop
	
branch_to_main:
	b main
inifinite_loop:
	b inifinite_loop

.section .text.default_handler
.type default_handler, %function
default_handler:
	b default_handler
	
	.end
	
	
