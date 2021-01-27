SECTIONS
{
	izlazna_sekcija_prva 0x0000FF00 : 
	{
		*(.text)
	}
	
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