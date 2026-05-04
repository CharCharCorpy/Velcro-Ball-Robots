#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <timerSet44.h> //brings in timerSetup() and timerGet()
// ^--arduino has issues with this

#define CTC_rupt TIM1_COMPA_vect

// Function declarations
void timerCTC(uint16_t clearBit);

