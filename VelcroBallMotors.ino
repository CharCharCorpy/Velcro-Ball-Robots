#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <analogWrite44.h>
#include <analogWrite44.c>

#include <clkPrescale44.h>
#include <clkPrescale44.c>
#include <timerSet44.h>
#include <timerSet44.c>
#include <timerCTC44.h>
#include <timerCTC44.c> //Don't need anything after this
#include <i2c44.h>
#include <i2c44.c>
#include <AS5600Read44.h>
#include <AS5600Read44.c>

///note that the angle and frequency measurements both use the same filter. Probably should be changed

//Sample Rate Determination
uint16_t timer_prescaler = 8;                                                         // 1 8 64 256 1024
uint16_t CTC_clearBit = 10000; //set the interupt to every 0.01 second // 0  to  2^16 -1
volatile float rate = 8000000.0 / (float(timer_prescaler) * (float(CTC_clearBit) + 1));  //Hz to sample at  //WHY THE +1??
volatile float dt = 1.0 / rate;                                                          //seconds between samples  

volatile float batVolt = 3.3; //most possible volts avaliable to me (not the actual volts of the battery)

volatile float voltOut;
volatile int switches=2;
//to send out the correct voltage it should be (voltOut/batVolt)255 then divide by 4 and convert to bits

//when dir is connected to 0 (CW is +), OC0B must be the higher motor
//CCWpin is OCR0A is PB2 //con to rdwir of motor (mot2)  //may swap mot1 and mot2 later, then all that needs to change is dir
//CWPin is OCR0B is PA7  //con to blkwir of motor (mot1)


//To create a time pattern
#define Norm_rupt TIM1_OVF_vect //Timer 1 overflow
#define CTC_rupt TIM1_COMPA_vect ///Timer 1 compare A
 int counter = 0;
//interupt service routine: What happens after a certain time interval //below function runs at the same time count as CTC_clearbit
ISR(CTC_rupt) {
  //voltOut = 3;
  int duty = abs(int(voltOut / batVolt * 255.0)); //Calcuating the duty cycle aka the way to start sending out the correct voltage
  voltOut = 3;

  if(switches<2){ //switches every one second
    if(counter<100){
      counter++;
    } else if(counter>=100) {
      counter = 0;
      if(switches!=0){
        switches=0;
        analogWriteA(0); //Motor A movement volts
        analogWriteB(50); //Motor B volts
      } else {
        switches=1;
        analogWriteA(duty); //Motor A movement volts
        analogWriteB(0); //Motor B volts
      }
    } 
  } else if(switches>=2){
    counter++;
    if(counter>=100){
      counter=0;
      switches++;
    } if(switches==10){
      switches = 0;
    }
  }


  if (duty > 255) {
    duty = 255;  // safety
  }

  // if (voltOut >= 0.0) {
  //   analogWriteB(duty); //Motor A movement volts
  //   analogWriteA(duty); //Motor B volts
  // }

  else if (voltOut < 0.0) {
    //analogWriteA(duty); //Motor A movement volts
    //analogWriteB(0); //Motor B movement volts
    analogWriteA(0); //Motor A movement volts
    analogWriteB(duty); //Motor B volts
  }

  //PORTA |= (1 << PORTA0);  //BlueLED on
  //PORTA &= ~(1 << PORTA0);  //BlueLED off





}


void setup() {
  cli();
  clkSetup(); //clock setup: sets clock speed
  timerSetup(timer_prescaler);  //select timer prescaler
  timerCTC(CTC_clearBit);       //select val to clear at. 16 bit (up to 65536)
  analogSetupAB();              //sets them to outputs and activates PC_PWM
  DDRA |= (1 << PORTA0);        //BlueLED set as output //DDRA is the registers for PORTA's, PORTA0 is a location name (A port 0)
  DDRA |= (1 << PORTA1);        //Dir set as output   //<< is a bitwise operator (look up later)

  PORTA |= (1 << PORTA0);   //BlueLED on
  PORTA &= ~(1 << PORTA0);  //BlueLED off

  //|=, &=, ~  are operators

  analogWriteA(0); //Setting motor to 0 at the start
  analogWriteB(0);
  sei(); //set enables interrupts (allows isr to run)
}

void loop() {
  //nothing here
}





