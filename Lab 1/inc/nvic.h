/*
 * nvic.h
 *
 *  Created on: 02.02.2021.
 *      Author: Ika
 */

#ifndef INC_NVIC_H_
#define INC_NVIC_H_

#include <stdint.h>

typedef struct
{
	uint32_t ISER[3];
	uint32_t dummy0[29];
	uint32_t ICER[3];
	uint32_t dummy1[29];
	uint32_t ISPR[3];
	uint32_t dummy2[29];
	uint32_t ICPR[3];
	uint32_t dummy3[29];
	uint32_t IABR[3];
	uint32_t dummy4[61];
	uint32_t IPR[21];
} NVIC_RegisterMapType;

#define NVIC ((NVIC_RegisterMapType *) 0xE000E100)

#define NVIC_ENABLE_IRQ(irqNumber) \
	NVIC->ISER[(irqNumber) / 32] = 1 << ((irqNumber) % 32)



#endif /* INC_NVIC_H_ */
