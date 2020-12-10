/*
 * casovnik.c
 *
 *  Created on: 10.12.2020.
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
uint8_t seven_seg[] =
{ 0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F, 0x80, 0x84 };

TIM_HandleTypeDef* casovnik_tim_handle = &htim1;

uint32_t counter = 0;
uint32_t tekuca = 0;

uint32_t sekunde = 0;
uint32_t minuti = 0;

uint32_t cifre[4] = {0 , 0 , 0, 0};

void casovnik(){

	//na port c, u njegov output data register izbacili smo vrednosti iz seven_seg[1] == 0xCF
	GPIOC->ODR = seven_seg[0];

	HAL_TIM_Base_Start_IT(casovnik_tim_handle);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	if(htim->Instance == htim1.Instance){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);

		if(++counter == 100){ //znak da je protekla 1 sekunda

			counter = 0;

			if(++sekunde == 60){
				sekunde = 0;

				if(++minuti == 60){
					minuti = 0;
				}
			}

			cifre[0] = minuti / 10;
			cifre[1] = minuti % 10;
			cifre[2] = sekunde / 10;
			cifre[3] = sekunde % 10;
		}

		tekuca = (tekuca + 1) % 4;

		//stavljam sve 0 u ODR
		GPIOC->ODR = ~0xFFF;

		//orujem ODR sa vrednoscu cifre koja treba da se upise
		GPIOC->ODR |= seven_seg[cifre[tekuca]];

		//aktiviram da li se upisuje u 0, 1, 2, 3 cifru displeja
		GPIOC->ODR |= 0x1 << (8 + tekuca);


	}
}

void resetStoperice(){
	minuti = 0;
	sekunde = 0;
	tekuca = 0;
}

