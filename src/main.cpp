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
        if(!(PIND & (1 << PIND3))){
          state = dbPress;
          turnOnTimer0();
        }
        break;
      case dbPress:
        break;
      case waitRelease:
        if(PIND & (1 << PIND3)){
          state = dbRelease;
          turnOnTimer0();
          PORTH ^= (1 << PORTH4);
        }
        break;
      case dbRelease:
        break;
    }
  }

  return 0;
}

ISR(TIMER0_COMPA_vect){
  turnOffTimer0();
  if(state == dbPress) state = waitRelease;
  else if(state == dbRelease) state = waitPress;
}
