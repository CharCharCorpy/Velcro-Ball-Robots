#include "analogWrite44.h"

// Function definitions
void analogSetupAB(){
    //just in case arduino is setting it prior
    TCCR0A = 0;
    TCCR0B = 0;

    DDRA |= 1 << PORTA7; //use DDRA to set PA# to outputs
    DDRA |= 1 << PORTA3;
    DDRA |= 1 << PORTA2;
    DDRB |= 1 << PORTB2; //use DDRB to set PB# to outputs (1 is output, 0 is input)



    TCCR0A |= 1 << COM0A1 | 1 << COM0B1 |  1 << WGM01 | 1 << WGM00; //Fast PWM mode, non inverted mode
    TCCR0B |= 0 << CS02 | 1 << CS01 | 0 << CS00; //prescaler 8 (prescaled from CLKps aka CLKi/o)
    return;
}

void analogWriteB(uint8_t duty){
    PORTA &= ~(1 << PORTA2);
    OCR0A = duty;
    return;
}

void analogWriteA(uint8_t duty){
    PORTA &= ~(1 << PORTA3);
    OCR0B = duty;
    return;
}
