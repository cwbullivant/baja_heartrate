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
