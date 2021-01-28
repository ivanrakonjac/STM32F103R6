# GNU Make tool

Koristi se za automatizaciju procesa prevodjenja.
Zna kako da prevede projekat i kako to da uradi efikasno (ne prevodi fajlove koji se nisu menjali).

To kako prevodi nas projekat mu mi definisemo u makefile-u.

To definisemo kroz pravila, u sledecoj formi:

	ciljPravila : preduslov1 preduslov2
		komanda koja predstavlja recept pravila (poziv alata)

Dokumentacija make alata: https://www.gnu.org/software/make/manual/make.html