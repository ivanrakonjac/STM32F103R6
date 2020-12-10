/*
 * casovnik.c
 *
 *  Created on: 10.12.2020.
 *      Author: Ika
 */

#include "casovnik.h"

TIM_HandleTypeDef* casovnik_tim_handle = &htim1;

extern void timer1Callback();

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


	HAL_TIM_RegisterCallback(casovnik_tim_handle, HAL_TIM_PERIOD_ELAPSED_CB_ID, &timer1Callback);
	HAL_TIM_Base_Start_IT(casovnik_tim_handle);

}

void timer1Callback(){
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	if(htim->Instance == htim1.Instance){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
	}
}


