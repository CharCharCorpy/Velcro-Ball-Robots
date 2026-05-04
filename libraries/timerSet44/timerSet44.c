#include "timerSet44.h"

// Function definitions
void timerSetup(uint16_t prescaler){
    //just in case Arduino is setting it prior.
    // Automatically sets to Normal Mode
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1C = 0;

    // Configure Timer/Counter 1 to be prescaled
    // CLKps is the name of the register
    if (prescaler == 1){
        TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10); // 1 prescaling. counts every CLKps*1
    }
    else if (prescaler == 8){
        TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10); // 8 prescaling. counts every CLKps*8
    }
    else if (prescaler == 64){
        TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10); // 64 prescaling. counts every CLKps*64
    }
    else if (prescaler == 256){
        TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10); // 256 prescaling. counts every CLKps*256
    }
    else if (prescaler == 1024){
        TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10); // 1024 prescaling. counts every CLKps*1024
    }
    


    //otherwise, timer is disabled
    

    // Enable overflow interrupt
    TIMSK1 |= (1 << TOIE1); // Enable Timer/Counter 1 [Normal Mode] overflow interrupt

    // Enable global interrupts
    sei();

    return;
}

uint16_t timerGet(){
    uint8_t tlowByte, thighByte;
    uint8_t sreg;
    /* Save global interrupt flag */
    sreg = SREG;

    /*Disable interrupts temporarily*/
    cli();

    // Read the low byte first (cause of the way the timer works)
    tlowByte = TCNT1L;  // Read low byte
    // Read the high byte
    thighByte = TCNT1H; // Read high byte

    /* Restore global interrupt flag */
    SREG = sreg;

    // Combine the two bytes to form the 16-bit count
    return (thighByte << 8) | tlowByte;
}
