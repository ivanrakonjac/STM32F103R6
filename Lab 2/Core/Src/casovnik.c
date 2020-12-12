/*
 * casovnik.c
 *
 *  Created on: 12.12.2020.
 *      Author: Ika
 */

#include "casovnik.h"


/*
 * Niz vrednosti koje je potrebno postaviti
 * na katode sedmosegmentnog displeja sa zajednickom anodom
 * kako bi se prikazala odgovarajuca decimalna cifra
 * ukoliko je povezivanje pinova izvrseno na naznacen nacin.
 *
 *                              A
 *                           *******
 *                         *         *
 *                       F *         * B
 *                         *    G    *
 *                           *******
 *                         *         *
 *                       E *         * C
 *                         *    D    *
 *                           *******
 *
 *
 * |-----|||-----|-----|-----|-----|-----|-----|-----|-----|||-----|
 * |     ||| PC7 | PC6 | PC5 | PC4 | PC3 | PC2 | PC1 | PC0 |||     |
 * |-----|||-----|-----|-----|-----|-----|-----|-----|-----|||-----|
 * | DIG ||| DP  |  A  |  B  |  C  |  D  |  E  |  F  |  G  ||| VAL |
 * |-----|||-----|-----|-----|-----|-----|-----|-----|-----|||-----|
 * |  0  |||  1  |  0  |  0  |  0  |  0  |  0  |  0  |  1  ||| 81  |
 * |  1  |||  1  |  1  |  0  |  0  |  1  |  1  |  1  |  1  ||| CF  |
 * |  2  |||  1  |  0  |  0  |  1  |  0  |  0  |  1  |  0  ||| 92  |
 * |  3  |||  1  |  0  |  0  |  0  |  0  |  1  |  1  |  0  ||| 86  |
 * |  4  |||  1  |  1  |  0  |  0  |  1  |  1  |  0  |  0  ||| CC  |
 * |  5  |||  1  |  0  |  1  |  0  |  0  |  1  |  0  |  0  ||| A4  |
 * |  6  |||  1  |  0  |  1  |  0  |  0  |  0  |  0  |  0  ||| A0  |
 * |  7  |||  1  |  0  |  0  |  0  |  1  |  1  |  1  |  1  ||| 8F  |
 * |  8  |||  1  |  0  |  0  |  0  |  0  |  0  |  0  |  0  ||| 80  |
 * |  9  |||  1  |  0  |  0  |  0  |  0  |  1  |  0  |  0  ||| 84  |
 * |-----|||-----|-----|-----|-----|-----|-----|-----|-----|||-----|
 *
 */

uint8_t seven_seg[] = { 0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F, 0x80, 0x84 };

uint32_t tekucaCifra = 0;


void casovnik(){
	GPIOC->ODR = seven_seg[1];
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	tekucaCifra = (tekucaCifra + 1) % 10;
	GPIOC->ODR = seven_seg[tekucaCifra];
}

void promeniCifru(){
	HAL_GPIO_EXTI_Callback(GPIO_PIN_6);
}