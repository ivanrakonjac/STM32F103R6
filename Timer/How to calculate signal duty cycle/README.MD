# How to calculate signal duty cycle

A simple way to calculate the duty cycle of some signal using input capture functionality of STM32F103R6.

We measure how many ticks elapsed between 2 edges of the signal (one rising and one falling) - active ticks.

When we divide active ticks with a ticks elapsed for one period and multitply thaht with 100, we get the duty cycle of a signal.

Handler is in Core/Src/timer.c file.

![image](https://user-images.githubusercontent.com/49063097/101942759-4fac2580-3bea-11eb-88f2-3b55202a65aa.png)


