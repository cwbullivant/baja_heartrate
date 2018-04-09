#include "spi.h"
#include "avr/io.h"
#include "timer.h"
#define time 2000
void initSPI() {
  // set SS, SCK, MOSI to outputs
  DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2);
  // set ss high by default
  PORTB |= (1 << PORTB0);
  //turns on master interupt clock and prescalar
  SPCR |= (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);


  DDRL |= (1 << DDL0) | (1 << DDL2) | (1 << DDL4);  //set port l 024 to output
  PORTL |= (1 << PORTL0) | (1 << PORTL2); //sets 02 high by default
  PORTL &= ~(1 << PORTL4); //sets oe low by default
  return;
}


void setDataReg(char input){  //sets data register
  SPDR = input;
  return;
}

void sendData(){  //sets ss low to start transmission
  PORTB &= ~(1 << PORTB0); //starts interanal SPI clock
  return;
}

void sendPacket(char data, char collumn){ //sends a data byte and a collumn byte
  setDataReg(data); //set data
  PORTL |= (1 << PORTL4); //set oe off
  sendData(); //send data

  delayUs(150); //wait to complete

  setDataReg(collumn); // set data
  sendData(); //send data
  delayUs(150); //wait to complete
  PORTL &= ~(1 << PORTL4);  //set oe on


  //need this from example file
  PORTL &= ~(1 << PORTL0);  //set latch low
  PORTL |= (1 << PORTL0);   //set lacth high
}


void generateTriangleDebug(){ //generates debug wave to view on matirx
  int count = 0;  //timer counter
  char dot = 0x01; //current dot
  char wave = 0x01; //current start
  char triangle = 0x02; //waxing value
  while(1){
    sendPacket(dot, 0b01111111); //sends data for first collumn
    delayUs(time);               //waits so visible
    dot = dot << 1;              //shift the dot
    sendPacket(dot, 0b10111111); //""
    delayUs(time);
    dot = dot << 1;
    sendPacket(dot, 0b11011111);
    delayUs(time);
    dot = dot << 1;
    sendPacket(dot, 0b11101111);
    delayUs(time);
    dot = dot << 1;
    sendPacket(dot, 0b11110111);
    delayUs(time);
    dot = dot << 1;
    sendPacket(dot, 0b11111011);
    delayUs(time);
    dot = dot << 1;
    sendPacket(dot, 0b11111101);
    delayUs(time);
    dot = dot << 1;
    sendPacket(dot, 0b11111110);
    delayUs(time);
    dot = dot << 1;
    count++;    //iterate count
    if(count == 4){ //if 4 progress to next wave state
      wave = triangle;
      triangle = triangle << 1;
      if(triangle == 0) { triangle = 0x1;}
      count = 0;
    }
    dot = wave; //reset the dot
  }

}
