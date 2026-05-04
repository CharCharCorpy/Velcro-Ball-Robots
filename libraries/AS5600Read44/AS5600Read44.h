#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

//Specific to the ATtiny44
#include <i2c44.h>

//Specific to the AS5600
#define B_ADDRESS 0x36  //Device address for AS5600
#define RAW 0x0C        //Register location of raw angle data
#define FILT 0x0E       //Register location of raw angle data


// Function Declaration
uint16_t I2C_ReadAngle(uint8_t B_REGISTER);



