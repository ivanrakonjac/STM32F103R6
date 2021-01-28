# GNU Make tool

Koristi se za automatizaciju procesa prevodjenja.
Zna kako da prevede projekat i kako to da uradi efikasno (ne prevodi fajlove koji se nisu menjali).

To kako prevodi nas projekat mu mi definisemo u makefile-u.

To definisemo kroz pravila, u sledecoj formi:

	ciljPravila : preduslov1 preduslov2
		komanda koja predstavlja recept pravila (poziv alata)

Kako pozvati make alat:

odemo u folder sa fajlovima, i iz komandne linije pozovoemo komandu make, ili make glavnoPravilo

Dokumentacija make alata: https://www.gnu.org/software/make/manual/make.html

* GNU MAKE (6 How to Use Variables)
	https://www.gnu.org/software/make/manual/html_node/Using-Variables.html

* GNU MAKE (10.5.3 Automatic Variables)
	https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html

* Podsetnik:
	* $(@) - cilj pravila
	* $(<) - prvi preduslov
	* $(^) - svi preduslovi

* GNU MAKE (10.5 Defining and Redefining Pattern Rules)
	https://www.gnu.org/software/make/manual/html_node/Pattern-Rules.html

Kako znati od kojih .h fajlova neki fajl zavisi:

* dodati opciju -MMD u flegove za kompajler koji ce nam to reci, i izgenerisace male makefileove koji sadrze samo pravilo za te zavisnosti
* opcija -MP (phony) generise lazna pravila => ako systick.o zavisi od systick.c i systick.h, izgenerisace se i pravilo za systick.h iako ne zavisi ni od jednog fajla

* GNU GCC (3.13 Options Controlling the Preprocessor)
	https://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html

Kako ukljuciti dependency fajove: 
	-include $(wildcard ./*.d) - zelimo da ukljucimo sve iz tekuceg direktorijuma sto ima ekstenziju .d

* GNU MAKE (4.4.3 The Function wildcard)
	https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html
* GNU MAKE (3.3 Including Other Makefiles)
	https://www.gnu.org/software/make/manual/html_node/Include.html

* GNU MAKE (6.3.1 Substitution References)
	https://www.gnu.org/software/make/manual/html_node/Substitution-Refs.html