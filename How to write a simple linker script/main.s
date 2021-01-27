	.cpu cortex-m3
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"main.c"
	
	.text @ Direktiva kojom se zapocinje nova sekcija
	@----------------------
	
	.global	nepromenljiva
	.section	.rodata @.section je direkiva koja zapocinje novu sekciju koja se zove rodata (read only)
	@----------------------
	.align	2
	.type	nepromenljiva, %object
	.size	nepromenljiva, 4
nepromenljiva:
	.word	6 @inicijalna vrednost nepromenljiva je 6
	
	
	.global	promenljiva
	.data
	@---------------------
	.align	2
	.type	promenljiva, %object
	.size	promenljiva, 4
promenljiva:
	.word	7
	
	
	.comm	neinicijalizovana,4,4
	
	
	.text
	@-------------------
	.align	1 @poravnjanje na adresu deljivu sa 2^1
	.global	main
	.arch armv7-m
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	main, %function @.type je direkiva koja kaze da je tip simbola main funkcija
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	add	r7, sp, #0
	movs	r3, #6
	adds	r2, r3, #5
	ldr	r3, .L3
	ldr	r3, [r3]
	add	r3, r3, r2
	ldr	r2, .L3+4
	str	r3, [r2]
	movs	r3, #0
	mov	r0, r3
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L4:
	.align	2
.L3:
	.word	promenljiva
	.word	neinicijalizovana
	.size	main, .-main
	.ident	"GCC: (xPack GNU Arm Embedded GCC, 64-bit) 9.3.1 20200408 (release)"
