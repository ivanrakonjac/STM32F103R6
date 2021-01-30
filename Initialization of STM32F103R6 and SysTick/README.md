# Initialization of STM32F103R6 and SysTick and using of SCB & NVIC

1) Create startup_code.c
2) Create makefile
3) Create linker_script.ld

How to initialize SysTick?

1) set values of necessary  registers (STK_LOAD, STK_VAL, STK_CTRL) in some method
2) call that method from main
3) override weak systick_handler method to do something
 