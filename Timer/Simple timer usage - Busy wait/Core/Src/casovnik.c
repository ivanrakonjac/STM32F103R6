/*
 * casovnik.c
 *
 *  Created on: 10.12.2020.
 *      Author: Ika
 */

#include "casovnik.h"

TIM_HandleTypeDef* casovnik_tim_handle = &htim1;

void casovnik(){
	HAL_TIM_Base_Start(casovnik_tim_handle);

	for(int i=0; i<5; i++){
		  while((casovnik_tim_handle->Instance->SR & TIM_SR_UIF) == 0){
			  //busy wait
		  }
		  TIM1->SR = ~TIM_SR_UIF;

		  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	}

	HAL_TIM_Base_Stop(casovnik_tim_handle);

}

