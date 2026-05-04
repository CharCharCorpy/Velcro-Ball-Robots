#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Function declarations
void analogSetupAB(void);
void analogWriteA(uint8_t duty);
void analogWriteB(uint8_t duty);

