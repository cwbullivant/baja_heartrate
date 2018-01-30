// Author:         Garrett Vanhoy
// Net ID:         gvanhoy
// Date:
//----------------------------------------------------------------------//

#include <Arduino.h>
#include "led.h"
#include "speaker.h"
#include "switch.h"
#include <avr/io.h>
#include <util/delay.h>

typedef enum stateType_num{

} stateType;

int main(){

  Serial.begin(9600);

  initLED();
  initSpeaker();
  initSwitches();
  unsigned int state = 0;

  while(1){
    switch(state){
      case 0:
        unarmedState();
        if(!(PIND & (1 << PIND2))){
          state = 1;
          _delay_ms(1000);
        }
        break;
      case 1:
        unarmedState();
        if(!(PIND & (1 << PIND1))){
          state = 2;
          _delay_ms(1000);
        }
        else if(!(PIND & (1 << PIND2))){
          state = 0;
          _delay_ms(1000);
        }
        break;
      case 2:
        standbyState();
        _delay_ms(3000);
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
