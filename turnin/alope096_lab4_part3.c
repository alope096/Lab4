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

enum States {locked, buttonHashPressed, buttonHashrelease, buttonYpress,buttonYrelease, insideButton} state;

void tick(){
   unsigned char button_Y = PINA & 0x02;
   unsigned char button_H = PINA & 0x04;
   unsigned char button_PA7 = PINA & 0x80;
   unsigned char lockedUnlocked;
   
   switch(state){
      case locked:
         state = button_H? buttonHashPressed : locked;
      break;   
      case buttonHashPressed:
         if(button_Y){
           state = buttonYpress;
         }
         else if(button_PA7){
           state = insideButton;
         }
         else{
           state = button_H? buttonHashPressed : buttonHashrelease;
         }
      break; 

      case buttonHashrelease:
         state = button_Y? buttonYpress : buttonHashrelease;
      break;

      case buttonYpress:
          if(button_H){
           state = buttonHashPressed;
         }
         else if(button_PA7){
           state = insideButton;
         }
         else{
           state = button_Y? buttonYpress : buttonYrelease;
         }
      break; 
      case buttonYrelease:
         state = button_PA7? insideButton : buttonYpress;
      break; 
      case insideButton:
         state = locked;
      break;
      default:
         state = locked;
      break;
   }
   switch(state){
      case locked:
         lockedUnlocked = 0x00; 
      break;   
      case buttonHashPressed:
      break; 
      case buttonHashrelease:
      break; 
      case buttonYpress: 
      break;
      case buttonYrelease:
         lockedUnlocked = 0x01; 
      break;
      case insideButton:
         lockedUnlocked = 0x00; 
      break;
   }
   PORTB = lockedUnlocked;
}

int main(void) {
    /* Insert DDR and PORT initializations */
   DDRA=0X00;  PORTA=0XFF;
   DDRB=0XFF;  PORTB=0X00;
   

    /* Insert your solution below */
   state = locked;

   while (1) {
     tick();
   }
    return 1;
   
}
