#include "i2c44.h"

//This library primarily uses code from "https://www.bitbanging.space/posts/bitbang-i2c"

// Function Definitions


inline void dly(){ __asm__("NOP"); }; // Optional: adjust for your delay

void i2cSetup(){
    T_DD_REG |= (1 << T_SDA_PIN) | (1 << T_SCL_PIN); //setting both pins as outputs
}


/* Start I2C sequence */
void start() {
    SDA_ON;
    dly();
    SCL_ON;
    dly();
    SDA_OFF;
    dly();
    SCL_OFF;
    dly();
}

/* Stop I2C sequence */
void stop() {
    SDA_OFF;
    dly();
    SCL_ON;
    dly();
    SDA_ON;
    dly();
}


/* Transmit data from trunk to branch */
bool Tx(uint8_t dat){
    //Returns the acknowledgement bit as a bool
        for (uint8_t i = 8; i; i--) {
        (dat & 0x80) ? SDA_ON : SDA_OFF;
        dat <<= 1;
        dly();
        SCL_ON;
        dly();
        SCL_OFF;
        dly();
    }
    SDA_ON;
    SCL_ON;
    dly();
    bool ack = !SDA_READ; // Check for acknowledgment
    SCL_OFF;
    return ack;
}


/* Receive data from branch to trunk*/
uint8_t Rx(bool ack) {
 //Receive 8-bit data and send ACK/NACK
    uint8_t dat = 0;
    SDA_ON;
    for (uint8_t i = 0; i < 8; i++) {
        dat <<= 1;
        do {
            SCL_ON;
        } while (SCL_READ == 0); // Clock stretching
        dly();
        if (SDA_READ)
            dat |= 1;
        dly();
        SCL_OFF;
    }
    ack ? SDA_OFF : SDA_ON;
    SCL_ON;
    dly();
    SCL_OFF;
    SDA_ON;
    return dat;
}