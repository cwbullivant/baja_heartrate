// Author:         Garrett Vanhoy
// Net ID:         gvanhoy
// Date:
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

void initSwitches(){
  // input
  DDRD &= ~((1 << DDD2) | (1 << DDD1);

  // enabling pull-up resistor
  PORTD |= (1 << PORTD2) | (1 << PORTD1) | (1 << PORTD0);

  // enable interrupt
  EIMSK |= (1 << INT2) | (1 << INT1) | (1 << INT0);
}

void print(){

}
