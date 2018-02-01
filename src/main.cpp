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

} stateType;

int main(){

  // Serial.begin(9600);

  initLED();
  initSpeaker();
  initSwitches();
  initTimer0();

  // PORTH |= (1 << PORTH5);
  // DDRB |= (1 << DDB7);
  // PORTB |= (1 << PORTB7);

  unsigned int state = 0;
  while(1){
    PORTH ^= (1 << PORTH4);
    switch(state){
      case 0:
        unarmedState();
        if(!(PIND & (1 << PIND2))){
          state = 1;
          delayMicro(1000000);
        }
        break;
      case 1:
        unarmedState();
        if(!(PIND & (1 << PIND1))){
          state = 2;
          delayMicro(1000000);
        }
        else if(!(PIND & (1 << PIND2))){
          state = 0;
          delayMicro(1000000);
        }
        break;
      case 2:
        standbyState();
        delayMicro(3000000);
        state = 3;
        break;
      case 3:
        armedState();
        if(!(PIND & (1 << PIND2))){
          state = 4;
        }
        break;
      case 4:
        // alarmState();
        chirp();
        break;
    }
  }

  return 0;
}
