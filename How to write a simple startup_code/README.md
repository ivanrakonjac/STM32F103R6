# How to write startup code for STM32F103R6

### .section .vector_table, "a"   
* dodajemo parametar a - allocatable jer sekcija vector_table nije dobro poznata, pa ne nasledjuje nikakve flegove

### .word main_stack_pointer_value   
* na pocetku vactor tabele se nalazi inicijalna vrednost SP (ovo znamo iz dokumentacije)
* necemo je def ovde, vec cemo je uvesti od negde (iz nekog drugog fajla) pomocu direktive .extern main_stack_pointer_value

### Reset handler - naredna vrednost u vector tabeli ( njegova adresa ) 
* ovo vrednost se inicijalno pri pokretanju mikrokontrolera upisuje u PC (funkcija na ovoj adresi ce se prva izvrsiti prilikom paljenja mikrokontrolera)

### objasnjenje asemblerskih direktiva sa pocetka fajla   
* .cpu cortex-m3 - o kom cpu-u je rec
* .fpu softvfp - koji se floating point unit koristi (vector floating point)
* .syntax unified - sintaksa je unified <=> i arm i thumb code se pisu na isti nacin
* .thumb - sav kod u nastavku je thumb

### for petlja   

	.rept 10
		.word default_handler
	.endr

### infinite loop:

	.section .text.default_handler
	.type default_handler, %function
	default_handler:
		b default_handler
		
		.end

### .word systick_handler   
* handler za sistemski tajmer

### .weak systick_handler   
* slab simbol da bi mogao da bude definisian u nekom fajlu spolja
* a ako nije imace vrednost iz ovo fajla

### .thumb_set systick_handler, default_handler   
* setuje vrednost systick_handler na default_handler
* i jos kaze da je systick_handler thumb funkcija

### Kopiranje podataka sa inicijalnim vrednostima iz FLASH memorije u SRAM
* ovo radimo da bi pri radjenju necega sa podacima sa inicijalnim vrednostima imali te vrednosti (da ne bi bile izgubljene)
* gde se ti podaci tacno nalaze u SRAM-u => izmedju _vma_data_start_ adrese i _vma_data_end_
* kako cemo znati sa koje adrese da ih citamo iz FLASH-a => _lma_data_start_ = LOADADDR(.data);

		ldr r0, =_lma_data_start_ => u ro stavljam adresu iz _lma_data_start_
		ldr r1, =_vma_data_start_ => u r1 stavljam adresu iz _vma_data_start_
		ldr r2, =_vma_data_end_   => u r2 stavljam adresu iz _vma_data_end_

		cmp r1, r2 => proveravam da li je r1==r2 i skacem na main ako jeste
		beq branch_to_main
		copy_loop:
		ldr r3, [r0], 4 => u r3 stavljam vrednost sa adrese r0 i uvecavam vrednost r0 za 4 (jer je 1 rec u armu 4B <=> r0++)
		str r3, [r1], 4 => stavljam vrednost iz r3 na adresu iz r1 i uvecavam r1 za 4 (r1++)
		cmp r1, r2
		blo copy_loop => ako je r1 < r2 skok na copy_loop
