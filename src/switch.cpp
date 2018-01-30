// Author:         Garrett Vanhoy
// Net ID:         gvanhoy
// Date:
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

void initSwitches(){
  // input
  DDRD &= ~((1 << DDD3) | (1 << DDD2) | (1 << DDD1));
  
  // enabling pull-up resistor
  PORTD |= (1 << PORTD3) | (1 << PORTD2) | (1 << PORTD1);
}
