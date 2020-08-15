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

enum States {start,startChoose, incrementPress,incrementRelease, decrementPress,decrementRelease, resetPress} state;

static unsigned char cntavail;

void tick() {
   unsigned char button_A0 = PINA & 0x01;
   unsigned char button_A1 = PINA & 0x02;
   switch(state){
      case start: 
         cntavail = 7;
        state = startChoose;
      break;
       case startChoose:
         if((button_A0) && (!button_A1) && (cntavail <9)){
            cntavail = cntavail +1;
            state = incrementPress;
           }
         else if((!button_A0) && (button_A1) && (cntavail >0)){
            cntavail = cntavail -1;
            state = decrementPress;
           }
          else if(button_A0 && button_A1){
            state = resetPress;
           }
         else{
          state = startChoose;
         }
      break;
      case incrementPress:
           if(!button_A0){
            state = incrementRelease;
           }
           else if(button_A0 && button_A1){
            state = resetPress;
           }
         else{
          
           state = incrementPress;
         }
      break;
      case incrementRelease:
        state = startChoose;
      break;

       case decrementPress:
           if(!button_A1){
            state = decrementRelease;
           }
           else if(button_A0 && button_A1){
            state = resetPress;
           }
         else{
           state = decrementPress; 
	 }     
      break;
       case decrementRelease:
         state = startChoose;
      break;

      case resetPress:
         if(!button_A0 && !button_A1){
            state = startChoose;
         }
         else{
            state = resetPress;
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
      case startChoose:
      break;
      case incrementPress:
      break;
      case decrementPress:
      break;
      case resetPress:
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
