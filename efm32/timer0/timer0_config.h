
#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

//------------------------------------------------------------------------------
// Timer 0 config settings (adjust the parameters in this section)
//
// Timer 0 is intended to be used to provide a high frequency (1 to 10 KHz)
// clock tick for general purpose user space software timer(s)

#define TIMER0_PRESCALE 8
#define TIMER0_PRESCALE_CODE timerPrescale8 // must complement TIMER0_PRESCALE

#define TIMER0_FREQ_Hz 1000 // timer 0 tick frequency


//------------------------------------------------------------------------------

#endif
