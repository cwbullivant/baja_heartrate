// Author:         Garrett Vanhoy
// Net ID:         gvanhoy
// Date:
//----------------------------------------------------------------------//

#include <Arduino.h>
#include "led.h"
#include <avr/io.h>
#include <util/delay.h>

int main(){

  initLED();


  while(1){
    // armedState();
    // unarmedState();
    // standbyState();
    // alarmState();
    // frequency 18 kHz 1/10000

    PORTH |= (1 << PORTH5);
    // _delay_us(1);
    // PORTH &= ~(1 << PORTH5);
    // _delay_us(1000);
  }

  return 0;
}
