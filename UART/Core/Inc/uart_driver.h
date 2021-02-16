/*
 * uart_driver.h
 *
 *  Created on: 16.02.2021.
 *      Author: Ika
 */
#include "usart.h"

#ifndef CORE_INC_UART_DRIVER_H_
#define CORE_INC_UART_DRIVER_H_


extern void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart);

extern void UART_AsyncTransmit(char character);

#endif /* CORE_INC_UART_DRIVER_H_ */
