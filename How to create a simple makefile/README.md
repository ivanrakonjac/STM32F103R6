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