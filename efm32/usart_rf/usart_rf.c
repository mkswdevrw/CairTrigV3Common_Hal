/*
 * usart_rf.c
 *
 *  Created on: 8 Nov 2016
 *      Author: Ben
 *
 *      USART RF dedicated functions
 *      The Si446x pins (other than SPI related)
 *      shall be managed in a different module
 */

#include "em_gpio.h"
#include "usart_rf.h"
#include "em_usart.h"
#include "em_cmu.h"
#include "usart_rf_config.h"

//------------------------------------------------------------------------------
static void usart_rf_spi_config();
static void usart_rf_pin_config();
static void usart_rf_pin_disable();
static void usart_rf_pin_route();

//------------------------------------------------------------------------------
// Init the internal dedicated rf usart
void usart_rf_init()
{
	usart_rf_spi_config();
	//**************WARNING*******************
	// CONFIG SPI MODULE BEFORE PIN CONFIG !!
	//****************************************
	usart_rf_pin_config();
	usart_rf_pin_route();
	USART_Enable(USARTRF1, usartEnable);
}

//------------------------------------------------------------------------------
// Disconnect the internal dedicated rf usart
void usart_rf_disable()
{
	usart_rf_pin_disable();

	USART_Enable(USARTRF1, usartDisable);
}

//------------------------------------------------------------------------------
// Routes usart rf pins
static void usart_rf_pin_route()
{
	// CS was left out on purpose so that it can be controlled manually
	USARTRF1 ->ROUTE = USARTRF_ROUTE_TXPEN;
	USARTRF1 ->ROUTE |= USARTRF_ROUTE_RXPEN;
	USARTRF1 ->ROUTE |= USARTRF_ROUTE_CLKPEN;
	USARTRF1 ->ROUTE |= USARTRF_ROUTE_LOCATION_LOC5; // defined iunder RF_USARTRF_LOCATION
}

uint8_t usart_rf_xferByteWait(const uint8_t txdata)
{
	uint8_t rxdata;

	  while (!(USARTRF1->STATUS & USART_STATUS_TXBL));
	  USARTRF1->TXDATA = (uint32_t)txdata;
	  while (!(USARTRF1->STATUS & USART_STATUS_TXC));
	  while (!(USARTRF1->STATUS & USART_STATUS_RXDATAV));
	  rxdata =  (uint8_t)USARTRF1->RXDATA;
	return rxdata;

}

//------------------------------------------------------------------------------
// Init the spi module
static void usart_rf_spi_config()
{
	USART_InitSync_TypeDef usartInit = USART_INITSYNC_DEFAULT;

	// enable SPI clock
	CMU_ClockEnable(cmuClock_USARTRF1, true);

	// Prepare struct for synchronous mode
	usartInit.enable = usartDisable;
	usartInit.refFreq = USARTRF_REFFREQ;
	usartInit.baudrate = USARTRF_BAUDRATE;
	usartInit.databits = USARTRF_DATABITS;
	usartInit.master = USARTRF_MASTER;
	usartInit.msbf = USARTRF_MSBF;
	usartInit.clockMode = USARTRF_CLOCKMODE;

	// Load the config.
	USART_InitSync(USARTRF1, &usartInit);
}


//------------------------------------------------------------------------------
// Init the usart rf spi pins
static void usart_rf_pin_config()
{
	GPIO_PinModeSet(RF_USARTRF_CS_PORT, RF_USARTRF_CS_PIN, gpioModePushPull, 1);
	GPIO_PinModeSet(RF_USARTRF_CLK_PORT, RF_USARTRF_CLK_PIN, gpioModePushPull, 0);
	GPIO_PinModeSet(RF_USARTRF_MOSI_PORT, RF_USARTRF_MOSI_PIN, gpioModePushPull, 0);
	GPIO_PinModeSet(RF_USARTRF_MISO_PORT, RF_USARTRF_MISO_PIN, gpioModeInputPull, 1);
}

//------------------------------------------------------------------------------
// Releases the usart rf pins
static void usart_rf_pin_disable()
{

	GPIO_PinModeSet(RF_USARTRF_CS_PORT, RF_USARTRF_CS_PIN, gpioModeDisabled, 0);
	GPIO_PinModeSet(RF_USARTRF_CLK_PORT, RF_USARTRF_CLK_PIN, gpioModeDisabled, 0);
	GPIO_PinModeSet(RF_USARTRF_MOSI_PORT, RF_USARTRF_MOSI_PIN, gpioModeDisabled, 0);
	GPIO_PinModeSet(RF_USARTRF_MISO_PORT, RF_USARTRF_MISO_PIN, gpioModeDisabled, 0);
}



