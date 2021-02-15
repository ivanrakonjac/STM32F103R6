#include "FreeRTOS.h"
#include "lcd.h"
#include "gpio.h"

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
