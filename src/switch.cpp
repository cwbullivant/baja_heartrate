// Author:         Garrett Vanhoy
// Net ID:         gvanhoy
// Date:
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

void initSwitches(){
  // input
  DDRD &= ~((1 << DDD2) | (1 << DDD1));
  DDRB &= ~(1 << DDB3);

  // enabling pull-up resistor
  PORTD |= ((1 << PORTD2) | (1 << PORTD1));
  PORTB |= (1 << PORTB3);

  // enable interrupt
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT3);
}
