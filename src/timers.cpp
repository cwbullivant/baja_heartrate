// Author:         Garrett Vanhoy
// Net ID:         gvanhoy
// Date:
//----------------------------------------------------------------------//

#include "timers.h"
#include <avr/io.h>
#include <Arduino.h>

void initTimer1(){
  // sets CTC Mode
  TCCR1B |= (1 << WGM12);

  // pre-scaler of 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // 50 ms timer (781)
  unsigned int num_ticks = 781;
  OCR1AL = num_ticks & 0x00FF;
  OCR1AH = num_ticks >> 8;

  // enable interrupt
  TIMSK1 |= (1 << OCIE1A);
}

// void initTimer0(){
//   // sets CTC Mode
//   TCCR0A |= (1 << WGM01);
//   TCCR0A &= ~((1 << WGM00));
//
//   // pre-scaler of 1024
//   TCCR0B &= ~((1 << WGM02) | (1 << CS01));
//   TCCR0B |= (1 << CS02) | (1 << CS00);
//
//   // enable interrupt
//   TIMSK0 |= (1 << OCIE0A);
//   OCR0A = 255;
// }

void turnOnTimer0(){
  TCCR0B &= ~((1 << CS02) | (1 << CS00));
  TCCR0B |= (1 << CS01);
}

void turnOffTimer0(){
  TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
}
// delay 1000
// void delayMicro(unsigned long int delay){
//
//   unsigned long int num_ticks = 2*delay;
//
//   // "resetting the timer"
//   TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
//   TCNT0 = 0;
//   TIFR0 |= (1 << OCF0A);
//
//   // set value of OCR0A
//   OCR0A = 255;
//
//   // delay 255 ticks x times
//   TCCR0B &= ~((1 << CS02) | (1 << CS00));
//   TCCR0B |= (1 << CS01);
//   // Serial.println("Before timer");
//
//   for(unsigned long int i = 0; i < num_ticks/256; i++){
//     while(!(TIFR0 & (1 << OCF0A)));   // wait for the flag raise
//     TIFR0 |= (1 << OCF0A);            // put the flag down
//   }
//
//   // Serial.println("After timer");
//
//   OCR0A = num_ticks % 256;
//   TCNT0 = 0;
//   while(!(TIFR0 & (1 << OCF0A)));   // wait for the flag raise
//   TIFR0 |= (1 << OCF0A);            // put the flag down
//   TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
// }
