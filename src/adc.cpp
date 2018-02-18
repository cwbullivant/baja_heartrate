// Author:         Garrett Vanhoy
// Net ID:         gvanhoy
// Date:
//----------------------------------------------------------------------//

#include "adc.h"
#include <avr/io.h>

void initADC(){
  // Use Avcc as the ref dont' set ADMUX bits at all (use ADC0)
  ADMUX |= (1 << REFS0);

  // right-shift results
  ADMUX &= ~(1 << ADLAR);

  DIDR0 |= (1 << ADC0D); // disable digital input

  ADCSRA |= (1 << ADEN) | (1 << ADATE);

  ADCSRA |= (1 << ADSC);
}
