// Author:         Garrett Vanhoy
// Net ID:         gvanhoy
// Date:
//----------------------------------------------------------------------//

#include "timers.h"
#include <avr/io.h>
#include <Arduino.h>

void initTimer0(){
  // sets CTC Mode
  TCCR0A |= (1 << WGM01);
  TCCR0A &= ~((1 << WGM00));

  // pre-scaler of 8
  TCCR0B &= ~((1 << WGM02) | (1 << CS02) | (1 << CS00));
  TCCR0B |= (1 << CS01);

}

// delay 1000
void delayMicro(unsigned long int delay){

  unsigned long int num_ticks = 2*delay;

  // "resetting the timer"
  TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
  TCNT0 = 0;
  TIFR0 |= (1 << OCF0A);

  // set value of OCR0A
  OCR0A = 255;

  // delay 255 ticks x times
  TCCR0B &= ~((1 << CS02) | (1 << CS00));
  TCCR0B |= (1 << CS01);
  // Serial.println("Before timer");

  for(unsigned long int i = 0; i < num_ticks/256; i++){
    while(!(TIFR0 & (1 << OCF0A)));   // wait for the flag raise
    TIFR0 |= (1 << OCF0A);            // put the flag down
  }

  // Serial.println("After timer");

  OCR0A = num_ticks % 256;
  TCNT0 = 0;
  while(!(TIFR0 & (1 << OCF0A)));   // wait for the flag raise
  TIFR0 |= (1 << OCF0A);            // put the flag down
  TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
}
