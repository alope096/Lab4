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

enum States {start, increment,waitIncrement, decrement, waitDecrement, reset } state;

void tick() {
   unsigned char button_A0 = PINA & 0x01;
   unsigned char button_A1 = (PINA & 0x02) >> 1;
   static unsigned char cntavail;
   switch(state){
      case start:
         if(button_A0 && button_A1){
            state = reset;
         }
         else if(button_A0){
            state = increment;
         }
         else if(button_A1){
            state = decrement;
         }
         else{
            state = start;
         }
      break;

      case increment:
         if(button_A0 && button_A1){
            state = reset;
         }
         else if(button_A0 && cntavail==9){
            state = waitIncrement;
         }
         else if(button_A1){
            state = decrement;
         }
         else{
            state = increment;
         }
      break;

      case waitIncrement:
         if(button_A0 && button_A1){
            state = reset;
         }
         else if(button_A1){
            state = decrement;
         }
         else{
            state = waitIncrement;
         }
      break;

      case decrement:
         if(button_A0 && button_A1){
            state = reset;
         }
         else if(button_A1 && cntavail==0){
            state = waitDecrement;
         }
         else if(button_A0){
            state = increment;
         }
         else{
            state = decrement;
         }
      break;

      case waitDecrement:
         if(button_A0 && button_A1){
            state = reset;
         }
         else if(button_A0){
            state = increment;
         }
         else{
            state = waitDecrement;
         }
      break;

      case reset:
         if(button_A0 && button_A1){
            state = reset;
         }
         else if(button_A0){
            state = increment;
         }
         else{
            state = reset;
         }
      break;

      default:
         state = start;
      break;
}
   switch(state){
      case start:
         cntavail = 7;
      break;
      case increment:
          cntavail = cntavail + 1;
      break;
      case waitIncrement:
      break;
      case decrement:
          cntavail = cntavail - 1;
      break;
      case waitDecrement:
      break;
      case reset:
          cntavail = 0;
      break;
   }
  PORTC = cntavail;
}


int main(void) {
    /* Insert DDR and PORT initializations */
   DDRA=0X00;  PORTA=0XFF;
   DDRB=0XFF;  PORTB=0X00;
   DDRC=0XFF;  PORTC=0X00;

    /* Insert your solution below */
   state = start;

   while (1) {
     tick();
   }
    return 1;
   
}
