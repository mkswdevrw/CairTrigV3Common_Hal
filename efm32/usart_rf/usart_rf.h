/*
 * usart_rf.h
 *
 *  Created on: 8 Nov 2016
 *      Author: Ben
 */

#ifndef USART_RF_H_
#define USART_RF_H_

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
#include <stdint.h>

//------------------------------------------------------------------------------
#define USART_RF_CS_SET()		(GPIO_PinOutSet(RF_USARTRF_CS_PORT, RF_USARTRF_CS_PIN))
#define USART_RF_CS_CLEAR()		(GPIO_PinOutClear(RF_USARTRF_CS_PORT, RF_USARTRF_CS_PIN))

//------------------------------------------------------------------------------
void usart_rf_init();
void usart_rf_disable();
uint8_t usart_rf_xferByteWait(const uint8_t txdata);

#ifdef __cplusplus
}
#endif

#endif /* USART_RF_H_ */
