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

typedef enum switchState_struct{
  waitPress, dbPress, waitRelease, dbRelease
} switchState;

volatile switchState sw_1_state = waitPress;
volatile switchState sw_2_state = waitPress;
volatile switchState sw_3_state = waitPress;

volatile int count = 0;

int main(){

  initLED();
  // initSpeaker();
  initSwitches();
  // initTimer0();
  initTimer1();
  sei();

  while(1){
    switch(sw_1_state){
      case waitPress:
        break;
      case dbPress:
        break;
      case waitRelease:
        break;
      case dbRelease:
        PORTH ^= (1 << PORTH4);
        break;
    }
    switch(sw_2_state){
      case waitPress:
        break;
      case dbPress:
        break;
      case waitRelease:
        break;
      case dbRelease:
        PORTH ^= (1 << PORTH5);
        break;
    }
    switch(sw_3_state){
      case waitPress:
        break;
      case dbPress:
        break;
      case waitRelease:
        break;
      case dbRelease:
        PORTH ^= (1 << PORTH6);
        break;
    }
  }

  return 0;
}

ISR(INT0_vect){
  if(sw_1_state == waitPress){
    turnOnTimer0();
    sw_1_state = dbPress;
  }
  else if(sw_1_state == waitRelease){
    sw_1_state = dbRelease;
    turnOnTimer0();
  }
}

ISR(INT1_vect){
  if(sw_2_state == waitPress){
    turnOnTimer0();
    sw_2_state = dbPress;
  }
  else if(sw_2_state == waitRelease){
    sw_2_state = dbRelease;
    turnOnTimer0();
  }
}

ISR(INT2_vect){
  if(sw_3_state == waitPress){
    turnOnTimer0();
    sw_3_state = dbPress;
  }
  else if(sw_3_state == waitRelease){
    sw_3_state = dbRelease;
    turnOnTimer0();
  }
}
ISR(TIMER1_COMPA_vect){
  turnOffTimer0();
  if(sw_1_state == dbPress) sw_1_state = waitRelease;
  else if(sw_1_state == dbRelease) sw_1_state = waitPress;

  if(sw_2_state == dbPress) sw_2_state = waitRelease;
  else if(sw_2_state == dbRelease) sw_2_state = waitPress;

  if(sw_3_state == dbPress) sw_3_state = waitRelease;
  else if(sw_3_state == dbRelease) sw_3_state = waitPress;
}

// ISR(TIMER0_COMPA_vect){
//   turnOffTimer0();
//   if(sw_1_state == dbPress) sw_1_state = waitRelease;
//   else if(sw_1_state == dbRelease) sw_1_state = waitPress;
//
//   if(sw_2_state == dbPress) sw_2_state = waitRelease;
//   else if(sw_2_state == dbRelease) sw_2_state = waitPress;
//
//   if(sw_3_state == dbPress) sw_3_state = waitRelease;
//   else if(sw_3_state == dbRelease) sw_3_state = waitPress;
// }
