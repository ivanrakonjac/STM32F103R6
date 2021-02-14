# NVIC & interrupt handlers

Konfigurisati sistem i NVIC periferije zgra tako da istovremeno vazi: 

(1) zahtevi za obradu prekida IRQ0, IRQ1 i IRQ2 jesu omoguceni, 

(2) u slučaju istovremenog pristizanja redosled obrade je IRQ1, IRQ2, IRQ0

(3) ne moze doci do ugnjezdavanja kada su u pitanju ova tri prekida


## Ideja

Da ne bi dolazilo do ugnjezdavanja treba svim prekidima setovati istu grupu, a onda pomocu podgrupe podesavati koji je bitniji.

CMSIS Dokumentacija za NVIC : https://arm-software.github.io/CMSIS_5/Core/html/group__NVIC__gr.html

Koristiti funkcije:

* NVIC_SetPriorityGrouping (uint32_t PriorityGroup)

* NVIC_EnableIRQ (IRQn_Type IRQn)

* NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)

* NVIC_SetPriority (IRQn_Type IRQn, uint32_t priority)

* NVIC->ISPR[0] = 0b111;
