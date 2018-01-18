// Author:         Garrett Vanhoy
// Net ID:         gvanhoy
// Date:
//----------------------------------------------------------------------//

#include "led.h"
#include <avr/io.h>
#include <util/delay.h>

void initLED(){
  // set the LEDs as output
  // pin 7 (DDH4), 8 (DDH5), 9 (DDH6)

  DDRH |= (1 << DDH4) | (1 << DDH5) | (1 << DDH6);

}

void armedState(){
  PORTH |= (1 << PORTH6);
  PORTH &= ~((1 << PORTH5) | (1 << PORTH4));
}

void unarmedState(){
  PORTH |= (1 << PORTH5);
  PORTH &= ~((1 << PORTH6) | (1 << PORTH4));
}

void standbyState(){
  PORTH |= (1 << PORTH4);
  PORTH &= ~((1 << PORTH5) | (1 << PORTH6));
}

void alarmState(){
  PORTH |= (1 << PORTH6) | (1 << PORTH5) | (1 << PORTH4);
  _delay_ms(1000);

  PORTH &= ~((1 << PORTH6) | (1 << PORTH5) | (1 << PORTH4));
  _delay_ms(1000);

}
