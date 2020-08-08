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

enum States {start, incrementPress, incrementRelease ,waitIncrement, decrementPress, decrementRelease, waitDecrement, resetPress, resetRelease } state;

static unsigned char cntavail;

void tick() {
   unsigned char button_A0 = PINA & 0x01;
   unsigned char button_A1 = (PINA & 0x02) >> 1;
   switch(state){
      case start:
         if(button_A0 && button_A1){
            state = resetPress;
         }
         else if(button_A0){
            state = incrementPress;
         }
         else if(button_A1){
            state = decrementPress;
         }
         else{
            state = start;
         }
      break;

      case incrementPress:
          if(button_A0 && button_A1){
            state = resetPress;
         }
         else if(button_A0 && cntavail==9){
            state = waitIncrement;
         }
         else if(button_A1){
            state = decrementPress;
         }
         else{
            state = incrementRelease;
         }
      break;
      case incrementRelease:
         if(!button_A0){
            state = incrementRelease;
         }
         else{
            state = incrementPress;
         }
      break;

      case waitIncrement:
         if(button_A0 && button_A1){
            state = resetPress;
         }
         else if(button_A1){
            state = decrementPress;
         }
         else{
            state = waitIncrement;
         }
      break;

      case decrementPress:
          if(button_A0 && button_A1){
            state = resetPress;
         }
         else if(button_A1 && cntavail==0){
            state = waitDecrement;
         }
         else if(button_A0){
            state = incrementPress;
         }
         else{
            state = decrementRelease;
         }
      break;
      case decrementRelease:
       if(!button_A1){
            state = decrementRelease;
         }
         else{
            state = decrementPress;
         }
      
      break;

      case waitDecrement:
         if(button_A0 && button_A1){
            state = resetPress;
         }
         else if(button_A0){
            state = incrementPress;
         }
         else{
            state = waitDecrement;
         }
      break;

      case resetPress:
         if(button_A0 && button_A1){
            state = resetPress;
         }
         else if(button_A0){
            state = incrementPress;
         }
         else{
            state = resetRelease;
         }
      break;
      case resetRelease:
         if(!(button_A0 && button_A1)){
            state = resetRelease;
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
      case incrementPress:
      cntavail = cntavail + 1;
      break;
      case incrementRelease:
      break;
      case waitIncrement:
      break;
      case decrementPress:
      cntavail = cntavail - 1;
      break;
      case decrementRelease:
      break;
      case waitDecrement:
      break;
      case resetPress:
       cntavail = 0;
      break;
      case resetRelease:
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
