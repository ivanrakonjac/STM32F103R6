# Cross toolchain GCC

Prevodjenje i asembliranje koda bez linkovanja u elf format:

* -c = bez linkovanja -mcpu = koje se jezgro koristi -mthumb = instrukcijski set -o = izlazni format

      arm-none-eabi-gcc.exe -c -mcpu=cortex-m3 -mthumb -o main.o .\main.c
	

Prevodjenje iz elf u hex format:

* -O ihex = izlazni format fajla

	  arm-none-eabi-objcopy.exe -O ihex .\main.o main.hex


Pretprocesiranje fajla bez prevodjenja:

* -E = samo pretprocesiranje zelimo, bez prevodjenja, asembliranja ili linkovanja

* -o main.i = izlazni fajl

* .\main.c = ulazni fajl

	  arm-none-eabi-gcc.exe -o main.i .\main.c -E 

Samo prevedi bez asembliranja ili linkovanja:

* -S = samo prevedi bez asembliranja ili linkovanja

* main.s = rezultat, main.i = ulazni fajl

	  arm-none-eabi-gcc.exe -o main.s .\main.i -mcpu=cortex-m3 -mthumb -S


Kompajlul i asmebliraj ali nemoj da linkujes:

* main.o = izlaz (elf format) .\main.s = ulaz 

	  arm-none-eabi-gcc.exe -c -mcpu=cortex-m3 -mthumb -o main.o .\main.s


Gledanje tabele simbola iz elf fajla:

	arm-none-eabi-objdump.exe -t .\main.o 

Gledanje sekcija iz elf fajla:

	arm-none-eabi-objdump.exe -h .\main.o 
	
* Atributi sekcija
	* CONTENTS - ima pocetni sadrzaj
	* ALLOC - treba da postoji alociran prostor u mem
	* LOAD - treba zaista da se smesti u memoriju
	* RELOC - ima potrebe da se nkeke stvari realociraju
	* READONLY
	* CODE - sadrzi kod u sebi
	
* .bss je sekcija za podatke bez pocetne vrednosti

Dobijanje .elf fajla iz .o fajla uz pomoc linkerske scripte

	arm-none-eabi-ld.exe --script=linker_script.ld -o main.elf .\main.o
	
	
Sta tacno radi linker:

* uzima ulazne objektne fajlove
* prepoznaje koje sve sekcije postoje u njemu
* te sekcije razmesta po adresnom prostoru
* a kako to radi se definise u linkerskoj skripti

Dokumentacija za asembler: https://sourceware.org/binutils/docs/as/
Dokumentacija za linker: https://sourceware.org/binutils/docs/ld/

  