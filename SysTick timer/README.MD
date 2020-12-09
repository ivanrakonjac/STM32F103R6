# NVIC & interrupt handlers

Konfigurisati sistem i NVIC periferije zgra tako da istovremeno vazi: 

(1) zahtevi za obradu prekida IRQ0, IRQ1 i IRQ2 jesu omoguceni, 

(2) u slučaju istovremenog pristizanja redosled obrade je IRQ1, IRQ2, IRQ0

(3) ne moze doci do ugnjezdavanja kada su u pitanju ova tri prekida