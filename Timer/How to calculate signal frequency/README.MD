# How to calculate signal frequency

A simple way to calculate the frequency of some signal using input capture functionality of STM32F103R6.

We measure how many ticks elapsed between 2 rising edges of the signal.

When we divide frequency for a counter clock with elapsed ticks, we get the frequency of a signal.

Handler is in Core/Src/timer.c file.

![image](https://user-images.githubusercontent.com/49063097/101899413-15bd2e00-3bae-11eb-8bc6-f09371d32bcb.png)

