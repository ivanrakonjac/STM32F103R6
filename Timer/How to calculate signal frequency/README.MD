# How to calculate signal frequency

Simple way to calculate frequency of some signal using input capture functionality of STM32F103R6.

We mesure how meny ticks elapsed between 2 rising edges of signal.

When we divide frequeny for counter clock with elapsed ticks, we get frequency of a signal. 

Handler is in Core/Src/timer.c file.

![image](https://user-images.githubusercontent.com/49063097/101899413-15bd2e00-3bae-11eb-8bc6-f09371d32bcb.png)

