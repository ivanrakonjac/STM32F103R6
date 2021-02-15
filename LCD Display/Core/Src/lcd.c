#include "FreeRTOS.h"
#include "lcd.h"
#include "gpio.h"
#include "queue.h"
#include "task.h"

/*
 * Raspored koriscenja pinova u proteus projektu

 PC0 - D4
 PC1 - D5
 PC2 - D6
 PC3 - D7
 PC4 - READ/WRITE
 PC5 - REGISTER_SELECT
 PC6 - ENABLE

 */

static TaskHandle_t  LCD_TaskHandle;
static QueueHandle_t LCD_QueueHandle;

#define LCD_ENABLE_BIT 0x40


/*
 * Funkcija koja vrsi jedan ciklus upisa
 *
 * Protokol za upis podatka:
 * generisati 1 REGISTER_SELECT -> (reg & 0x01) << 5)
 * generisati 0 READ/WRITE -> ne moramo nista spec da radimo
 * i staviti podatak na magistralu (posto koristimo samo 4 bita, moracemo iz 2 puta) -> | (val & 0x0F)
 * setovati i resetovanje ENABLE -> GPIOC->ODR |= LCD_ENABLE_BIT; GPIOC->ODR &= ~LCD_ENABLE_BIT;
 *
 * funkcija je static, sto znaci da joj nije moguce pristupiti spolja (iz nekog drugog fajla)
 */
static void LCD_Write(LCD_CommandReg reg, LCD_CommandVal val)
{
	GPIOC->ODR = ((reg & 0x01) << 5) | (val & 0x0F);

	GPIOC->ODR |= LCD_ENABLE_BIT;
	// Timing Characteristics - neko cekanje bi bilo neophodno da je realan kontroler, a ne simulator
	GPIOC->ODR &= ~LCD_ENABLE_BIT;
}


/*
 * Fukncija koja vrsi upis celog podatka (iz 2 ciklusa)
 * Ova fukncija ce se pozivati iz nekog Taska
 */
static void LCD_CommandInitiate(LCD_CommandReg reg, LCD_CommandVal val)
{
	// Prvo se upisuje visih 4 bita
	LCD_Write(reg, val >> 4);
	//Pa nizih 4 bita
	LCD_Write(reg, val >> 0);

	// Umesto da citamo Busy fleg, ali lakse za implementaciju je da sacekamo koliko traje i najduza operacija
	vTaskDelay(pdMS_TO_TICKS(2));
}


/*
 * Task koji procesira LCD
 */
static void LCD_Task(void *parameter)
{
	// Internal Reset Circuit (page: 23 u dokumentaciji)
	// Simuliramo to tako sto cekamo 20ms
	// Posle interne inicijalizacije mi mozemo raditi sta zelimo
	vTaskDelay(pdMS_TO_TICKS(20));

	// Setovati da saljemo podatke pomocu 4 bita
	// Posto je sirina instrukcije 8 bitova, a mi pozivamo direktno LCD_Write(), siftujemo za 4 mesta u desno
	LCD_Write(LCD_INSTRUCTION, (LCD_FUNCTION_SET_INSTRUCTION | LCD_FUNCTION_SET_4_BIT_INTERFACE) >> 4 );
	// Opet cekanje za svaki slucaj
	vTaskDelay(pdMS_TO_TICKS(2));

	// 4_BIT_INTERFACE, 2_LINE, 5x8_DOTS
	LCD_CommandInitiate(LCD_INSTRUCTION,
	LCD_FUNCTION_SET_INSTRUCTION |
	LCD_FUNCTION_SET_4_BIT_INTERFACE |
	LCD_FUNCTION_SET_2_LINE |
	LCD_FUNCTION_SET_5x8_DOTS);

	// Upali displej, ugasi kursor, ugasi blinkanje
	LCD_CommandInitiate(LCD_INSTRUCTION,
	LCD_CONTROL_INSTRUCTION |
	LCD_CONTROL_DISPLAY_ON |
	LCD_CONTROL_CURSOR_OFF |
	LCD_CONTROL_BLINK_OFF);

	// Podesavanje entry moda -> Inkrementiranje adrese, bez siftovanja
	LCD_CommandInitiate(LCD_INSTRUCTION,
	LCD_ENTRY_MODE_INSTRUCTION |
	LCD_ENTRY_MODE_INC_ADR |
	LCD_ENTRY_MODE_SHIFT_OFF);

	// Vracanje displeja u inicijalno stanje
	LCD_CommandInitiate(LCD_INSTRUCTION, LCD_RETURN_HOME_INSTRUCTION);

	LCD_Command cmd;
	while (1)
	{
		// Dohvatamo zahteve iz reda i blokiramo se ako je red prazan
		xQueueReceive(LCD_QueueHandle, &cmd, portMAX_DELAY);
		LCD_CommandInitiate(cmd.reg, cmd.val);
	}
}


/*
 * Funkcija u kojoj pravimo Task za rad LCDa
 */
void LCD_Init(){
	LCD_QueueHandle = xQueueCreate(64,sizeof(LCD_Command));
	// Obicno setovati prioritet kao i prioritet TimerTaska
	xTaskCreate(LCD_Task, "LCD Task", 128, NULL, 2, &LCD_TaskHandle);
}

/*
 * Funkcija koju mozemo zvati iz Taska za ubacivanje u red
 */
void LCD_CommandEnqueue(LCD_CommandReg reg, LCD_CommandVal val){
	LCD_Command cmd = {reg, val};
	xQueueSend(LCD_QueueHandle, &cmd, portMAX_DELAY);
}

/*
 * Funkcija koju mozemo zvati iz prekidne rutine za ubacivanje u red
 */
void LCD_CommandEnqueueFromISR(LCD_CommandReg reg, LCD_CommandVal val, BaseType_t* pxHigherPriorityTaskWoken){
	LCD_Command cmd = {reg, val};
	xQueueSendFromISR(LCD_QueueHandle, &cmd, pxHigherPriorityTaskWoken);
}
