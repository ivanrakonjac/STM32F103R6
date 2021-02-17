# Simple timer usage - Busy wait

Kada se TIMER enabluje u CubeMXu u main.c se pojavljuje ova funkcija MX_TIM1_Init();   

To znaci da je timer inicijalizovan, ali ne i da je startovan.   

Da bi se startovao neophodno je pozvati HAL_TIM_Base_Start(&htim1) funkciju, gde je htim1 rucka na timer.   

Led 1 (PB0) is toggled on the timer1 update event (500ms).

![image](https://user-images.githubusercontent.com/49063097/101819074-0e057700-3b25-11eb-92ff-abe2c78550ca.png)

