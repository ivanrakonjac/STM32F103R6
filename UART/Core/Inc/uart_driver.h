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

extern void UART_AsyncTransmitChar(char character);
extern void UART_AsyncTransmitString(char const* string);
extern void UART_AsyncTransmitDecimal(uint32_t decimal);


#endif /* CORE_INC_UART_DRIVER_H_ */
