/*
 * efm32.h
 *
 *  Created on: 10 Nov 2016
 *      Author: rob
 */

#ifndef EFM32_H_
#define EFM32_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "em_cmu.h"
#include "gpiointerrupt.h"
#include "efm32_config.h"
#include <stdint.h>


//------------------------------------------------------------------------------
#if defined (EFM32_CLK_BAND_14_MHz)
  #define EFM32_CLK_BAND cmuHFRCOBand_14MHz
  #define EFM32_CLKFREQ_Hz 14000000
#elif defined (EFM32_CLK_BAND_21_MHz)
  #define EFM32_CLK_BAND cmuHFRCOBand_21MHz
  #define EFM32_CLKFREQ_Hz 21000000
#else
  #define EFM32_CLKFREQ_Hz 14000000
#endif
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#define EFM32_PF2_PIN 2
#define EFM32_PF2_PORT gpioPortF

//------------------------------------------------------------------------------
#define EFM32_PIN_ON(port, pin) (GPIO_PinOutSet(port, pin))
#define EFM32_PIN_OFF(port, pin) (GPIO_PinOutClear(port, pin))
#define EFM32_PIN_TOG(port, pin) (GPIO_PinOutToggle(port, pin))

//------------------------------------------------------------------------------

#define EFM32_BUTTON_PIN 5
#define EFM32_BUTTON_PORT gpioPortD

#define EFM32_BUTTON_PIN_STATE() GPIO_PinInGet(EFM32_BUTTON_PORT, EFM32_BUTTON_PIN)

  //------------------------------------------------------------------------------
#define EFM32_LED_RED_PIN 15
#define EFM32_LED_RED_PORT gpioPortC

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


void efm32_initClks();
void efm32_initGPIO();
void efm32_initPins();
void efm32_initButtonPin(GPIOINT_IrqCallbackPtr_t callBack);

void efm32_disableButtonInt();
void efm32_enableButtonInt();

//void efm32_initSensorLedInput(GPIOINT_IrqCallbackPtr_t intCallBack);
//void efm32_initSensorBuzInput(GPIOINT_IrqCallbackPtr_t intCallBack);
//void efm32_initSensorAuxInput(GPIOINT_IrqCallbackPtr_t intCallBack);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif /* EFM32_H_ */
