// Author:         Garrett Vanhoy
// Net ID:         gvanhoy
// Date:
//----------------------------------------------------------------------//

#include <avr/io.h>
#include <util/delay.h>

void initSpeaker(){
  DDRE |= (1 << DDE3);
}

// frequency 18 kHz 1/10000
void chirp(){
    PORTE |= (1 << PORTE3);
    _delay_us(1000);
    PORTE &= ~(1 << PORTE3);
    _delay_us(1000);
}
