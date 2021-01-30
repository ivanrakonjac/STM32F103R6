#ifndef _NVIC_H_
#define _NVIC_H_

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

#endif
