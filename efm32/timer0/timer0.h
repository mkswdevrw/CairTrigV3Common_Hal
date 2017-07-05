/*
 * Gecko General Purpose Hardware Timer Library
 *
 */

#ifndef TIMER_H_
#define TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "em_device.h"
#include "em_timer.h"
#include "timer0_config.h"
#include "efm32.h"
#include <stdbool.h>
#include <stdint.h>

//------------------------------------------------------------------------------

#define TIMER0_CLK_FREQ_Hz (EFM32_CLKFREQ_Hz / TIMER0_PRESCALE)

#define TIMER0_TOP (TIMER0_CLK_FREQ_Hz / TIMER0_FREQ_Hz)

#if TIMER0_FREQ_Hz >= 1000
  #define TIMER0_mS_MULTIPLIER (TIMER0_FREQ_Hz / 1000)
#else
  #define TIMER0_S_MULTIPLIER TIMER0_FREQ_Hz
#endif


//------------------------------------------------------------------------------

extern volatile uint32_t timer0_tick;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void timer0_init();
void timer0_enable();

/*
void timer0_delay(const uint32_t dlyTicks);
void timer0_delay_mS(const uint32_t _dlyTicks);
void timer0_delay_mS_debugPrint(const uint32_t _dlyTicks);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

static inline void timer0_TickReset(uint32_t* tickCount)
{
  *tickCount = timer0Ticks;
}
//------------------------------------------------------------------------------

static inline uint32_t timer0_TickElapsed(uint32_t startTick)
{
  return (timer0Ticks - startTick);
}

//------------------------------------------------------------------------------

static inline bool timer0_TickCheckTimeout(uint32_t* tickCount, uint32_t timeoutTicks)
{
  if(timer0_TickElapsed(*tickCount) > timeoutTicks)
  {
    timer0_TickReset(tickCount);
    return true;
  }
  return false;
}

//------------------------------------------------------------------------------
*/

#ifdef __cplusplus
}
#endif

#endif
