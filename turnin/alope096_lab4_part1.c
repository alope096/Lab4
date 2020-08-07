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

int main(void) {
    /* Insert DDR and PORT initializations */
   DDRA=0X00;  PORTA=0XFF;
   DDRB=0XFF;  PORTB=0X00;

    /* Insert your solution below */
   unsigned char button=0;
   unsigned char led=0;
   
   while (1) {
       button = PINA & 0x01;
       
   switch(button){
      case 0x00:
      led = 0x01;
      break;
   
     case 0x01:
      led = 0x02;
      break;

   default:
      button = 0x00;
      break;
   
  }
   PORTB = led;       
    }
    return 1;
}
