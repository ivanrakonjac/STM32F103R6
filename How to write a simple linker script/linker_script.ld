MEMORY
{
	REGION_PRVI (rwx) : ORIGIN = 0x0000EE00, LENGTH = 32k
	
	REGION_LMA (rx)   : ORIGIN = 0x99999999, LENGTH = 32k
}

SECTIONS
{
	izlazna_sekcija_prva :
	{
		. = . + 5;
		BYTE(0xFF)
		. = ALIGN(16);
		*(.text)
	} > REGION_PRVI
	
	izlazna_sekcija_druga 0x66660000 : 
	{
		*(.rodata)
	}
	
	izlazna_sekcija_treca : 
	{
		*(.data)
	} > REGION_PRVI AT> REGION_LMA 
	
	izlazna_sekcija_cetvrta 0x88880000 : 
	{
		*(.COMMON)
	}
	
	izlazna_sekcija_peta : 
	{
		*(.comment)
		*(.ARM.attribures)
	}
	
	podaci_start_vma_1 = ADDR(izlazna_sekcija_treca);
	podaci_start_lma = LOADADDR(izlazna_sekcija_treca);
}