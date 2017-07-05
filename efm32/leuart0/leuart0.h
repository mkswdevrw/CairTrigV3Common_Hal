/*
 * leuart.h
 *
 *  Created on: 27 Jan 2015
 *      Author: rob
 */

#ifndef LEUART_H_
#define LEUART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "em_device.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_leuart.h"
#include <stdbool.h>

// LEUART0 is DAB on DAU 0.2

//------------------------------------------------------------------------------

#define LEUART0_BAUDRATE_VAL 115200

#define LEUART0_LEUART_ROUTE_LOCATION LEUART_ROUTE_LOCATION_LOC5

#define LEUART0_RX_PORT gpioPortC
#define LEUART0_RX_PIN 15

#define LEUART0_TX_PORT gpioPortC
#define LEUART0_TX_PIN 14

#define LEUART0_RX_BUFFER_LEN 64

//------------------------------------------------------------------------------

extern volatile uint32_t leuart0_numCharsRx_ISR;
extern volatile uint8_t leuart0_rxData_ISR[];
//------------------------------------------------------------------------------

void leuart0_init();
void leuart0_txByteWait(const uint8_t txData);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif /* LEUART_H_ */
