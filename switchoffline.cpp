/*===========================================
 *Project Name : Manhole Indication System 
 *Author List : Sankalp Singh
 *Filename : switchoffline.cpp
 *Functions : switching_offline(void)
 *Global Variables : NONE
============================================*/

#include "declaration.h"
#include "motor_control.h"
#include "switchoffline.h"
#include "Arduino.h"

motor_control control_offline;

/*======================================================================================================
 * Function Name : switching_offline()
 * Input : NONE
 * Output : NONE
 * Logic : This function checks the current state of the switch and then check what is value of the flag 
 *         of the switch and accordingly it triggers the motor
 * Example Call : obj.switching_offline();
========================================================================================================*/

void switchoffline :: switching_offline(){
  int state_offline = digitalRead(button_offline);
	if(state_offline == HIGH){
	  if(dir_offline == true){
	    dir_offline = false;
	  	control_offline.operate(1);
	  }
  }	
	else if(state_offline == LOW){
	  if(dir_offline == false){
		  dir_offline = true;
		  control_offline.operate(0);      
		}
  }
}
