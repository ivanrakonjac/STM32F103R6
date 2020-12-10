/*
 * casovnik.c
 *
 *  Created on: 10.12.2020.
 *      Author: Ika
 */

#include "casovnik.h"


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	if(htim->Instance == htim1.Instance){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
	}else if(htim->Instance == htim3.Instance){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	}

}


