# SysTick timer

Konfigurisati sistem i STK (SisTick timer) periferiju jezgra,
tako da generise zahtev za obradu izuzetaka sa periodom od 1ms 
koji ce biti prihvacen cim stanje sistema i prioriteti izuzetaka to dozvole.

## Sta koristiti i kako:

CMSIS SysTick dokumentacija : https://arm-software.github.io/CMSIS_5/Core/html/group__SysTick__gr.html#gabe47de40e9b0ad465b752297a9d9f427

uint32_t SysTick_Config ( uint32_t  ticks	) 
