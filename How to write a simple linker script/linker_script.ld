MEMORY
{
	REGION_PRVI (rwx) : ORIGIN = 0x0000EE00, LENGTH = 32k
}

SECTIONS
{
	izlazna_sekcija_prva :
	{
		*(.text)
	} > REGION_PRVI
	
	izlazna_sekcija_druga 0x66660000 : 
	{
		*(.rodata)
	}
	
	izlazna_sekcija_treca 0x77770000 : 
	{
		*(.data)
	}
	
	izlazna_sekcija_cetvrta 0x88880000 : 
	{
		*(.COMMON)
	}
	
	izlazna_sekcija_peta : 
	{
		*(.comment)
		*(.ARM.attribures)
	}
}