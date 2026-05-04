#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

//This part is specific to the microcontroller (trunk)
//      Consult datasheet
#define T_OUT_REG PORTA  //This register controls whether pins are high or low
#define T_IN_REG PINA    //Data is read/stored at the PINx register

#define T_DD_REG DDRA   //Data direction register, used for setup
#define T_SDA_PIN PA6   //PORTA pin 6
#define T_SCL_PIN PA4   //PORTA pin 4


// Functions to activate or deactivate the trunk SDA and SCL lines
#define SDA_ON (T_OUT_REG |= (1<< T_SDA_PIN))
#define SDA_OFF (T_OUT_REG &= ~(1<< T_SDA_PIN))
#define SCL_ON (T_OUT_REG |= (1<< T_SCL_PIN))
#define SCL_OFF (T_OUT_REG &= ~(1<< T_SCL_PIN))

// Functions to allow the trunk SDA or SCL to read incoming information
#define SDA_READ (T_IN_REG & (1 << T_SDA_PIN))
#define SCL_READ (T_IN_REG & (1 << T_SCL_PIN))


// I2C read/write definitions
//  These must be appended to the end of the initial device address to determine whether the trunk is reading or writing
#define I2C_READ 0x01
#define I2C_WRITE 0x00

// Function declarations
void i2cSetup();
void start();
void stop();
bool Tx(uint8_t dat);
uint8_t Rx(bool ack);
