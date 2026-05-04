#include "timerCTC44.h"

// The overflow vector for CTC mode is TIM1_COMPA_vect

// Function definition
// clearBit is the number of ticks before interuption
void timerCTC(uint16_t clearBit){

    // Clears previous config
    TCCR1B &= ~((1 << WGM13) | (1 << WGM12)); //sets the WGM1[] bits to 0000.
    TCCR1A &= ~((1 << WGM11) | (1 << WGM10));

    // Clears other overflow interrupt types
    TIMSK1 &= ~((1 << TOIE1) | (1 << OCIE1A) | (1 << OCIE1B));


    // Configure Timer/Counter 1 to CTC mode (pg. 114)
    TCCR1B |= (0 << WGM13) | (1 << WGM12); //sets the WGM1[] bits to 0100.
    TCCR1A |= (0 << WGM11) | (0 << WGM10);

    TIMSK1 |= (1 << OCIE1A); // Enable Timer/Counter 1 CTC overflow interrupt

    // Set the bit to clear on (CTC)
    OCR1AH = clearBit >> 8;       //(low bit must be set before the high bit) pg.109
    OCR1AL = (clearBit & 0000000011111111);

    return;
}

