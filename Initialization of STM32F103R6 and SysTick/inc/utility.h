#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdint.h>

/*
 * obrisati vrednost segmenta registra, a zatim smestiti tu novu vrednost
 * target - u koji registar nesto upisujemo
 * startBitIncl - pocev od kog bita (ukljucujuci i taj bit - Inclusiv)
 * endBitIncl - do kog bita (ukljucujuci i taj bit - Inclusiv)
 * value - nova vrednost
 */
#define SET_VALUE(target, startBitIncl, endBitIncl, value) \
	do { \
		/* dohvatamo vrednost registra */ \
		uint32_t temp = (target); \
		/* dobijamo onoliko nula na najnizim bitovima kolika je sirina segmenta, pa ih invertujemo u 1 */ \
		uint32_t mask = ~(~0 << ((endBitIncl) - (startBitIncl) + 1)); \
		/* masku siftujemo na odg poziciju, invertujemo u 0, andujemo sa tempom => dobijamo 0 na sirini segmenta u tempu */ \
		temp &= ~(mask << startBitIncl); \
		/* andujemo value i masku za slucaj da je value siri i siftujemo value na pocetak segmenta, onda orujemo sa tempom */ \
		temp |= ((value) & mask) << startBitIncl; \
		/* u target stavljamo temp */ \
		(target) = temp; \
	} while(0)

#endif
