/*
 * efm32.c
 *
 *  Created on: 10 Nov 2016
 *      Author: rob
 */
#include "efm32.h"
#include "em_gpio.h"


//------------------------------------------------------------------------------
void efm32_initClks()
{
  CMU_HFRCOBandSet(EFM32_CLK_BAND);            // set HFRCO to required frequency.
  while (CMU_HFRCOBandGet() != EFM32_CLK_BAND); // wait till change takes hold

  // High Frequency Clock: select source
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);

  /* Enable peripheral clock */
  CMU_ClockEnable(cmuClock_HFPER, true);


  //--------------------------------------
  // Low energy clock config.
  CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_HFCLKLE);

  // Enable low energy section clocks.
  CMU_ClockEnable(cmuClock_LFB, true);
  CMU_ClockEnable(cmuClock_CORELE, true);

  //--------------------------------------
  CMU_ClockEnable(cmuClock_ADC0, true);
}
//------------------------------------------------------------------------------

void efm32_initGPIO()
{
  // Enable clock for GPIO by default
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Initialise GPIO interrupt dispatcher
  // MUST have this if using gpio triggered level/edge interrupts.
  GPIOINT_Init();
}
//------------------------------------------------------------------------------
void efm32_initPins()
{
  GPIO_PinModeSet(EFM32_PF2_PORT, EFM32_PF2_PIN, gpioModePushPull, 0);
}

//------------------------------------------------------------------------------
void efm32_initButtonPin(GPIOINT_IrqCallbackPtr_t callBack)
{
  // configure button pin
  GPIO_PinModeSet(EFM32_BUTTON_PORT, EFM32_BUTTON_PIN, gpioModeInputPullFilter, 0);

  // set the callback (i.e. the ISR) that will be called when the event occurs.
  GPIOINT_CallbackRegister(EFM32_BUTTON_PIN, callBack);

  // configure the interrupt to trigger on a rising edge.
  GPIO_IntConfig(EFM32_BUTTON_PORT, EFM32_BUTTON_PIN, true, false, true);
}
//------------------------------------------------------------------------------
void efm32_disableButtonInt()
{
  GPIO_IntConfig(EFM32_BUTTON_PORT, EFM32_BUTTON_PIN, true, false, false);
}
//------------------------------------------------------------------------------
void efm32_enableButtonInt()
{
  GPIO_IntConfig(EFM32_BUTTON_PORT, EFM32_BUTTON_PIN, true, false, true);
}
//------------------------------------------------------------------------------
/*
void efm32_initSensorLedInput(GPIOINT_IrqCallbackPtr_t intCallBack)
{
  GPIO_PinModeSet(EFM32_FH_LCDCLK_PORT, EFM32_FH_LCDCLK_PIN, gpioModeInput, 0);

  // set the callback (i.e. the ISR) that will be called when the event occurs.
  GPIOINT_CallbackRegister(EFM32_FH_LCDCLK_PIN, intCallBack);

  // configure the interrupt to trigger on a rising and falling edge.
  GPIO_IntConfig(EFM32_FH_LCDCLK_PORT, EFM32_FH_LCDCLK_PIN, true, true, true);
}
//-----------------------------------------------------------------------------
void efm32_initSensorBuzInput(GPIOINT_IrqCallbackPtr_t intCallBack)
{
  GPIO_PinModeSet(EFM32_FH_BUZ_PORT, EFM32_FH_BUZ_PIN, gpioModeInput, 0);

  // set the callback (i.e. the ISR) that will be called when the event occurs.
  GPIOINT_CallbackRegister(EFM32_FH_BUZ_PIN, intCallBack);

  // configure the interrupt to trigger on a rising and falling edge.
  GPIO_IntConfig(EFM32_FH_BUZ_PORT, EFM32_FH_BUZ_PIN, true, true, true);
}

//------------------------------------------------------------------------------
void efm32_initSensorAuxInput(GPIOINT_IrqCallbackPtr_t intCallBack)
{
  GPIO_PinModeSet(EFM32_FH_AUX_PORT, EFM32_FH_AUX_PIN, gpioModeInput, 0);

  // set the callback (i.e. the ISR) that will be called when the event occurs.
  GPIOINT_CallbackRegister(EFM32_FH_AUX_PIN, intCallBack);

  // configure the interrupt to trigger on a rising and falling edge.
  GPIO_IntConfig(EFM32_FH_AUX_PORT, EFM32_FH_AUX_PIN, true, true, true);
}
//------------------------------------------------------------------------------
*/
