#include "clkPrescale44.h"

// Function definition

void clkSetup(){
    uint8_t sreg;
    /* Save global interrupt flag */
    sreg = SREG;
    /*Disable interrupts temporarily*/
    cli();

    CLKPR = 0b10000000; //all is 0 except for the 7th bit (CLKPCE) pg.38 datasheet

    //Uncomment the line you need. I can't use the code above because bits need to be set within 4 clock cycles
        CLKPR = 0 | (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0); // 1 prescaling. counts every 1/8us
        //CLKPR |= (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (1 << CLKPS0); // 2 prescaling. counts every 1/4us
        //CLKPR |= (0 << CLKPS3) | (0 << CLKPS2) | (1 << CLKPS1) | (0 << CLKPS0); // 4 prescaling. counts every 1/2us
        //CLKPR |= (0 << CLKPS3) | (0 << CLKPS2) | (1 << CLKPS1) | (1 << CLKPS0); // 8 prescaling. counts every 1us
        //CLKPR |= (0 << CLKPS3) | (1 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0); // 16 prescaling. counts every 2us
        //CLKPR |= (0 << CLKPS3) | (1 << CLKPS2) | (0 << CLKPS1) | (1 << CLKPS0); // 32 prescaling. counts every 4us
        //CLKPR |= (0 << CLKPS3) | (1 << CLKPS2) | (1 << CLKPS1) | (0 << CLKPS0); // 64 prescaling. counts every 8us
        //CLKPR |= (0 << CLKPS3) | (1 << CLKPS2) | (1 << CLKPS1) | (1 << CLKPS0); // 128 prescaling. counts every 16us
        //CLKPR |= (1 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0); // 256 prescaling. counts every 32us

    /* Restore global interrupt flag */
    SREG = sreg;

    return;
}

