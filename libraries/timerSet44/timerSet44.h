#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define Norm_rupt TIM1_OVF_vect

// Function declarations
void timerSetup(uint16_t prescaler);
uint16_t timerGet(void);

