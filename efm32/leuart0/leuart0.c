/*
 * leuart.c
 *
 *  Created on: 27 Jan 2015
 *      Author: rob
 */


#include "leuart0.h"
#include "em_int.h"


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

volatile uint32_t leuart0_numCharsRx_ISR;
volatile uint8_t leuart0_rxData_ISR[LEUART0_RX_BUFFER_LEN];
//------------------------------------------------------------------------------
static void leuart0PinsInit();
static void leuart0Config();
static void leuart0PinRoute();

//------------------------------------------------------------------------------

// external interface functions

void leuart0_init()
{
  leuart0PinsInit();
  leuart0Config();
  leuart0PinRoute();

  LEUART_Enable(LEUART0, leuartEnable);
}

//------------------------------------------------------------------------------
void leuart0_txByteWait(const uint8_t txData)
{
  LEUART0->TXDATA = txData;
  while(!(LEUART0->STATUS & LEUART_STATUS_TXC));
}

//------------------------------------------------------------------------------
// ISR for all leuart0 interrupts.
// See startup_gcc_efm32lg.s for correct function name.
void LEUART0_IRQHandler(void)
{
  leuart0_rxData_ISR[leuart0_numCharsRx_ISR++] = LEUART0->RXDATA;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

static void leuart0PinsInit()
{
  GPIO_PinModeSet(LEUART0_TX_PORT, LEUART0_TX_PIN, gpioModePushPull, 1);

  GPIO_PinModeSet(LEUART0_RX_PORT, LEUART0_RX_PIN, gpioModeInputPull, 1);
}

//------------------------------------------------------------------------------
static void leuart0Config()
{
  LEUART_Init_TypeDef init = LEUART_INIT_DEFAULT;

  // enable LEUART0 clock
  //CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_HFRCO);

  // **** For EFM32LG (Leopard) When running at 28 MHz,
  // set HFLE bit in CMU_CTRL register to divide HFCORECLK(LE) by 4 (instead of 2).
  // This will result in the low energy (LE) peripherals being driven at 7 MHz
  // (the max they can handle is 24 MHz).

  // **** For EFM32LG (Leopard) When running off HFRCO, max CPU frequency is 28 MHz

  // **** need to set LEUART0->CLKDIV manually
  //
  // LEUART0->CLKDIV is the divider value that is used in the calculation
  // ( ** do NOT multiply it by 8 because it is shifted up 3 bits in the LEUART0->CLKDIV register)
  //
  // values used here:
  //
  // fLEUART0 = 7 MHz (clock rate into LEUART0 module, i.e. LFB clock)
  // baudrate (desired) = 115200
  //
  // LEUART0->CLKDIV = 256 * ((fLEUART0 / baudrate) - 1)
  //
  // => LEUART0->CLKDIV = 256 * ((7e6 / 115200) -1) = 15300 = 0x3bc4
  //
  // but need to remove bottom 3 bits, so:
  // LEUART0->CLKDIV = 0x3bc0 = 15296


  // for EFM32LG (Leopard) LFB clock is HFCORECLK(LE)/2
  //CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_CORELEDIV2);         // ALREADY DONE in chip_initClockLE()

//  CMU_ClockEnable(cmuClock_LFB, true);                            // ALREADY DONE in chip_initClockLE()
//  CMU_ClockEnable(cmuClock_CORELE, true);

  CMU_ClockEnable(cmuClock_LEUART0, true);

  LEUART_Reset(LEUART0);

  //init.baudrate = 19200;
  init.refFreq = CMU_ClockFreqGet(cmuClock_LEUART0);
  init.baudrate = LEUART0_BAUDRATE_VAL;

  //------------------------------------------------
  // Initialise LEUART0 interrupt.
  LEUART_IntClear(LEUART0, LEUART_IF_RXDATAV);
  NVIC_ClearPendingIRQ(LEUART0_IRQn);               // leuart has same interrupt for both RX and TX.

  LEUART_IntEnable(LEUART0, LEUART_IF_RXDATAV);
  NVIC_EnableIRQ(LEUART0_IRQn);

  leuart0_numCharsRx_ISR = 0;
  //------------------------------------------------

  LEUART_Init(LEUART0, &init);

  //LEUART0->CLKDIV = LEUART0_BAUDRATE_VAL;
}

//------------------------------------------------------------------------------
static void leuart0PinRoute()
{

  //LEUART0->ROUTE |= LEUART_ROUTE_RXPEN;
  LEUART0->ROUTE |= LEUART_ROUTE_TXPEN;
  LEUART0->ROUTE |= LEUART0_LEUART_ROUTE_LOCATION;

  // check value:
  // LEUART0->ROUTE = 0x00000203
}

//------------------------------------------------------------------------------
