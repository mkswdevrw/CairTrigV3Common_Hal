
#include "timer0.h"
#include "em_cmu.h"

//------------------------------------------------------------------------------
//volatile uint32_t timer0Ticks = 4294964000;
volatile uint32_t timer0_tick = 0;

//------------------------------------------------------------------------------


// initialise the specified timer
void timer0_init()
{
  TIMER_Init_TypeDef timerConfig = TIMER_INIT_DEFAULT;
  uint32_t topVal;

  // do NOT Start counting when init completed
  timerConfig.enable = false;

  // divide peripheral clock by 16 for timer 0
  timerConfig.prescale = TIMER0_PRESCALE_CODE;

  topVal = TIMER0_TOP;

  // enable peripheral clock for timer0
  CMU_ClockEnable(cmuClock_TIMER0, true);

  // enable TIMER0 interupts for NVIC
  NVIC_EnableIRQ(TIMER0_IRQn);

  // set timer0 config registers
  TIMER_Init(TIMER0, &timerConfig);

  // load the timer's top value (i.e. the value that is counts up from to, from zero)
  TIMER_TopSet(TIMER0, topVal);

  // enable timer0 overflow interrupt
  TIMER_IntEnable(TIMER0, TIMER_IEN_OF);
}

//------------------------------------------------------------------------------

// enable the specified timer
void timer0_enable()
{
  TIMER_Enable(TIMER0, true); // start
}

//------------------------------------------------------------------------------

/*void timer0_delay(const uint32_t dlyTicks)
{
  uint32_t curTicks;

  curTicks = timer0Ticks;
  while ((timer0Ticks - curTicks) < dlyTicks) ;
}

//------------------------------------------------------------------------------

void timer0_delay_mS(const uint32_t _dlyTicks)
{
  uint32_t curTicks, dlyTicks;

  dlyTicks = _dlyTicks * TIMER0_mS_MULTIPLIER;

  curTicks = timer0Ticks;
  while ((timer0Ticks - curTicks) < dlyTicks) ;
}

//------------------------------------------------------------------------------

void timer0_delay_mS_debugPrint(const uint32_t _dlyTicks)
{
  uint32_t curTicks, dlyTicks;

  dlyTicks = _dlyTicks * TIMER0_mS_MULTIPLIER;

  curTicks = timer0Ticks;
  do
  {
	  //MAIN_DEBUG_TX();
	  //SAP_DEBUG_UART_TX;
  }
  while ((timer0Ticks - curTicks) < dlyTicks);
}
*/
//------------------------------------------------------------------------------

void TIMER0_IRQHandler(void)
{
  // Must clear TIMER0 interrupt(s) in software (here is overflow interrupt)
  TIMER_IntClear(TIMER0, TIMER_IF_OF);

  timer0_tick++;
}

//------------------------------------------------------------------------------
