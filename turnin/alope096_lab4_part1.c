/*	Author: lab
 *  Partner(s) Name: None
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, lightOn, lightOff } state;

void tick() {
   unsigned char button= PINA & 0x01;
   unsigned char led = 0;
   switch(state){
      case start:
      state = lightOn;
      break;
      case lightOn:
      state = button? lightOff:lightOn;
      break;
      case lightOff:
      state = button? lightOn:lightOff;
      break;
      default:
      state = start;
      break;
}
   switch(state){
      case start:
      led = 0x01;
      break;
      case lightOn:
      led = 0x01;
      break;
      case lightOff:
      led = 0x02;
      break;
   }
  PORTB = led;
}


int main(void) {
    /* Insert DDR and PORT initializations */
   DDRA=0X00;  PORTA=0XFF;
   DDRB=0XFF;  PORTB=0X00;

    /* Insert your solution below */
   state = start;

   while (1) {
     tick();
   }
    return 1;
   
}
