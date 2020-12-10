# How to register timer update event handler in runtime

Handler is in Core/Src/casovnik.c file.

	void timer1Callback(){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
	}