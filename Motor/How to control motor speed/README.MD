# How to control motor speed

You can control motor speed by using the output compare mode of one of the STM's timers.

When you choose a timer, set one of the channels to PWM mode (Pulse With Modulation).

PWM mode allows generating a signal with a frequency determined by the value of the TIMx_ARR register and a duty cycle determined by the value of the TIMx_CCRx register.

For changing the value of the CCR register I use 2 buttons (INC and DEC), which are connected to EXTI0 and EXTI1 pins.

HAL_GPIO_EXTI_Callback is in Core/Src/gpio.c file.

![image](https://user-images.githubusercontent.com/49063097/101960938-dec83600-3c08-11eb-8e8a-18a10e95488d.png)

![image](https://user-images.githubusercontent.com/49063097/101960990-028b7c00-3c09-11eb-9bc7-2de5217c1e46.png)
