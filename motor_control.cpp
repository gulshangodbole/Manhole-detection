/*=======================================================
 *Project Name : Manhole Indication System 
 *Author List : Sankalp Singh
 *Filename : motor_control.cpp
 *Functions : operate(int), forward(), reverse(), brake() 
 *Global Variables : NONE
=========================================================*/

#include "declaration.h"
#include "motor_control.h"
#include "Arduino.h"

declaration motorObj;

/*====================================================================================================
 * Function Name : operate
 * Input : move -> This variable contains the value which dictates how the system should move
 * Output : NONE
 * Logic : This function dictates how the system should move by using the value stored in the variable 
 *         move. The value of move is passed into the switch case which then sees the current position 
 *         of the system and decides whether to perform the current instruction or not which helps 
 *         avoid malfunctioning of the system  
 * Example Call : obj.operate(0);
======================================================================================================*/

void motor_control :: operate(int move) {
  switch (move) {
    case 0:

      //Here the if statement checks whether the system is already in the up state
      if(motorObj.up == false){
        forward();
        //Lets the motor rotate for 50 seconds
        delay(50000);
        brake();
        //Here the flags are set to the values such that it indicates that it cannot be given the command for setting the motor in the forward direction
        motorObj.up = true;
        motorObj.down = false;
      }
      else
        break;
      break;
    case 1:
    
      //Here the if statement checks whether the system is already in the down state
        if(motorObj.down == false){
          reverse();
          //Lets the motor rotate for 50 seconds
          delay(50000);
          brake();
          //Here the flags are set to the values such that it indicates that it cannot be given the command for setting the motor in the reverse direction
          motorObj.up = false;
          motorObj.down = true;
        }
        else
          break;
        break;
    default:
      Serial.println("Error received");
      break;
    }
}

/*======================================================================================================
 * Function Name : forward()
 * Input : NONE
 * Output : NONE
 * Logic : This function rotates the motor in clockwise of Indication system by setting the input 1 as  
 *         LOW and input 2 as HIGH also it turns off the LED of the system by setting the LED pin to LOW
 * Example Call : forward();
========================================================================================================*/

void motor_control :: forward(){
  delay(5000);
  
  Serial.println("System going UP");
  digitalWrite(motorObj.ledPin_in,LOW);
  
  delay(1000);
  
  digitalWrite(motorObj.in_1, LOW) ;
  digitalWrite(motorObj.in_2, HIGH) ;
}

/*======================================================================================================
 * Function Name : reverse()
 * Input : NONE
 * Output : NONE
 * Logic : This function rotates the motor in anti-clockwise of Indication system by setting the input 1 
 *         as HIGH and input 2 as LOW also it turns off the LED of the system by setting the LED pin to 
 *         HIGH
 * Example Call : reverse();
========================================================================================================*/

void motor_control :: reverse(){    
  delay(5000);
  
  digitalWrite(motorObj.in_1, HIGH);
  digitalWrite(motorObj.in_2, LOW);

  delay(1000);
  
  Serial.println("System going down");
  digitalWrite(motorObj.ledPin_in,HIGH);
  
}

/*======================================================================================================
 * Function Name : brake()
 * Input : NONE
 * Output : NONE
 * Logic : This function switches off the motor rotation by setting the input 1 and input 2 as HIGH
 * Example Call : brake();
========================================================================================================*/

void motor_control :: brake() {
  Serial.println("System stopped");
  digitalWrite(motorObj.in_1, HIGH);
  digitalWrite(motorObj.in_2, HIGH);
}
