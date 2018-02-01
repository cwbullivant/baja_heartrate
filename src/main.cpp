// Author:         Garrett Vanhoy
// Net ID:         gvanhoy
// Date:
//----------------------------------------------------------------------//

#include <Arduino.h>
#include "led.h"
#include "speaker.h"
#include "switch.h"
#include "timers.h"
#include <avr/io.h>
#include <util/delay.h>

typedef enum stateType_num{
  waitPress, dbPress, waitRelease, dbRelease
} stateType;

volatile stateType state = waitPress;
volatile int count = 0;

int main(){

  initLED();
  // initSpeaker();
  initSwitches();
  initTimer0();
  sei();

  while(1){
    switch(state){
      case waitPress:
        break;
      case dbPress:
        break;
      case waitRelease:
        break;
      case dbRelease:
        break;
    }
  }

  return 0;
}

ISR(PCINT0_vect){
  // put the flag low
  PCIFR |= (1 << PCIF0);
  if(state == waitPress){
    turnOnTimer0();
    state = dbPress;
  }
  else if(state == waitRelease){
    state = dbRelease;
    turnOnTimer0();
    PORTH ^= (1 << PORTH4);
  }
}

ISR(TIMER0_COMPA_vect){
  turnOffTimer0();
  if(state == dbPress) state = waitRelease;
  else if(state == dbRelease) state = waitPress;
}
