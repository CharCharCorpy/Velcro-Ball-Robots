#include "AS5600Read44.h"

// Function Definition
uint16_t I2C_ReadAngle(uint8_t B_REGISTER){
    //"Data Read with Address Pointer Reload" Mode from the AS5600 Datasheet
    start();
    bool ACK = Tx((B_ADDRESS << 1)|I2C_WRITE);
    ACK = Tx(B_REGISTER);
    start();
    ACK = Tx((B_ADDRESS << 1)|I2C_READ);
    uint8_t highByte = Rx(1); //sends a ACK to continue
    uint8_t lowByte = Rx(0);  //sends a NACK to end the transmission
    stop();
    return((highByte << 8) | lowByte);
}