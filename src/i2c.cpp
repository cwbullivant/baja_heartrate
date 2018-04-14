#include "i2c.h"

/*
Flow guidelines:
1) Configure TWCR
2) Poll TWINT until high
3) Read TWSR
4) Change states
5) Repeat as needed
*/

typedef enum enumI2Cstate {start, devAddr, data, stop} i2cInternal;

void initI2CMaster() {
  //TWCR |= (1 << TWIE); // this doesn't seem to be wanted here
  TWSR |= (1 << TWPS0) | (1 << TWPS1);
  TWBR = 255; // set to lowest possible, easy to change if needed
}

void initI2CSlave() {
  // might not need this
}

void sendData(unsigned char addr, unsigned char data) {
  i2cInternal i2c_s = start;
  unsigned char twint;

  while (i2c_s != stop) {
    twint = TWSR & 0xF8;
    switch (i2c_s) {
      case start:
        TWCR |= (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
        i2c_s = devAddr;
        break;
      case devAddr:
        if (twint != 0x08 && twint != 0x10) {
          i2c_s = start;
        }
        else {
          TWDR = (addr << 1);
          TWCR = (1 << TWINT) | (1 << TWEN);
          i2c_s = data;
        }
        break;
      case data:
        if (twint != 0x18) {
          i2c_s = start;
        }
        else {
          TWDR = data;
          TWCR = (1 << TWINT) | (1 << TWEN);
          i2c_s = stop;
        }
        break;
      case stop:
        if (twint != 0x28) {
          i2c_s = start;
        }
        else {
          TWCR = (1 << TWINT) | (1 << TWEN);
        }
    }

    if (i2c_s != stop) {
      while (!(TWCR & (1 << TWINT)));
      if (twint == 0x38 || twint == 0x00) {
        i2c_s = start;
      }
    }
  }
}

void receiveData(unsigned char addr, unsigned char data) {
  i2cInt i2c_s = start;
  unsigned char twint = TWSR & 0xF8;
  while (i2c_s != stop) {
    switch(i2c_s) {
      case start:
        TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
        i2c_s = devAddr;
        break;
      case devAddr:
        TWDR = (addr << 1) & 0xFF;
        TWCR = (1 << TWINT) | (1 << TWEN);
        break;
      case data:
        break;
      case stop:
        break;
    }
    if () {

    }
    while
  }
}
