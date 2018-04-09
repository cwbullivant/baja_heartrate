#ifndef SPI_H
#define SPI_H


void initSPI();
void sendPacket(char data, char collumn);
void sendData();
void setDataReg(char input);
void generateTriangleDebug();

#endif
