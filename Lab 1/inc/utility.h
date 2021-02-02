/*
 * utility.h
 *
 *  Created on: 02.02.2021.
 *      Author: Ika
 */

#ifndef INC_UTILITY_H_
#define INC_UTILITY_H_


#define SET_VALUE(target, startBitIncl, endBitIncl, value) \
	do { \
		uint32_t temp = (target); \
		uint32_t mask = ~(~0 << ((endBitIncl) - (startBitIncl) + 1)); \
		temp &= ~(mask << startBitIncl); \
		temp |= ((value) & mask) << startBitIncl; \
		(target) = temp; \
	} while(0)



#endif /* INC_UTILITY_H_ */
