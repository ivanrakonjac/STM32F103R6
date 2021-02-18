# TIMER - Beleske

Kada se TIMER enabluje u CubeMXu u main.c se pojavljuje ova funkcija MX_TIM1_Init();   

To znaci da je timer inicijalizovan, ali ne i da je startovan.   

Da bi se startovao neophodno je pozvati HAL_TIM_Base_Start(&htim1) ili HAL_TIM_Base_Start_IT(&htim1) funkciju, gde je htim1 rucka na timer. 

Kada se TIMER pokrene u modu za interrupte odmah skace u prekidnu rutinu.

Da se to ne bi dogadjalo mozemo obrisati interrupt flag u status registru:

	(&htim1)->Instance->SR = ~TIM_SR_UIF

Da li je tajmer istekao mozemo znati na 2 nacina:
	1) Busy waitom
	2) Prekidom

### Busy wait

* Startujemo timer HAL_TIM_Base_Start(&htim1)

* Dohvatimo TIM->SR (status register) i proveravamo da li je Update interrupt Flag (UIF) postavljen na 1

		while((casovnik_tim_handle->Instance->SR & TIM_SR_UIF) == 0){
			//busy wait
		}
		TIM1->SR = ~TIM_SR_UIF;	 

### Interrupt

* Startujemo timer HAL_TIM_Base_Start_IT(&htim1);

* Cekamo da se desi prekid kako bi skocili u prekidnu rutinu

* Neku korisnu radnju mozemo izvrsiti deklaracijom nekog od slabih callbackova

		void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {					
			if(htim->Instance == htim1.Instance){
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
			}
		}

## Input Capture

Cemu sluzi capture funkcionalnost kanala?

* Ideja je da uhvatimo neki spoljasnji signal i obradimo ga na neki nacin.

* Zatim detektujemo dogadjaj na njemu (uzlaznu ili silaznu ivicu).

* Kada skontamo da se zeljeni dogadjaj desio, vrsimo hvatanje (capture) vrednost iz COUNTER registra u CAPTURE/COMPARE registar.

### Sta treba uciniti da bi se koristion Input Capture:

* Startovati input capture kanal u interapt modu (da ne bi bio blokirajuci)

		HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);

* Startovati timer

		HAL_TIM_Base_Start_IT(&htim1);

* Neku korisnu radnju opet mozemo izvrsiti u nekom od slabih callbackova

		void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim){
			//da li je ovde zbog timera1 i da li je aktivan bas kanal 1
			if(htim->Instance == TIM1 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
				timeStampStart = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			}
		}	

## Output compare

Sustina:

Izbacuje se neka vrednost na izlaz, a ta vrednost zavisi od poredjenja COUNTERA i CAPTURE/COMPARE registra.

### Sta treba uciniti da bi se koristion Output compare:

* Startovati OC kanal

		HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_1);

* Startovati Timer
	
		HAL_TIM_Base_Start_IT(&htim1);
  
