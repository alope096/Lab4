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

enum States {start, buttonReleaseOff, buttonPressOn, buttonReleaseOn, buttonPressOff } state;

void tick() {
   unsigned char button = PINA & 0x01;
   static unsigned char led;
   switch(state) {
      case start:
         state = buttonReleaseOff;
      break;
      case buttonReleaseOff:
         state = button? buttonPressOn:buttonReleaseOff;
      break;
      case buttonPressOn:
         state = button? buttonPressOn:buttonReleaseOn;
      break;
      case buttonReleaseOn:
         state = button? buttonPressOff:buttonReleaseOn;
      break;
      case buttonPressOff:
         state = button? buttonPressOff:buttonReleaseOff;
      break;
      default:
         state = start;
   }
   switch(state) {
      case start:
         led = 0x01;
      break;
      case buttonReleaseOff:
         led = 0x01;
      break;
      case buttonPressOn:
         led = 0x02;
      break;
      case buttonReleaseOn:
      break;
      case buttonPressOff:
         led = 0x01;
      break;
   }
PORTB = led;
}
int main(void) {
DDRA = 0x00; DDRA = 0x00;
DDRA = 0x00; DDRA = 0x00;

state = start;

 while(1){
   tick();
  }
return 1;
}

  

