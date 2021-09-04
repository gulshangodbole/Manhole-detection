/*===========================================
 *Project Name : Manhole Indication System 
 *Author List : Sankalp Singh
 *Filename : declaration.h
 *Functions : NONE
 *Global Variables : NONE
============================================*/

#ifndef DECLARATION_H
#define DECLARATION_H

#include "Arduino.h"

class declaration{
	public :
		void data();

    //in_1 -> This variable has the pin number for input 1 of motor 
    int in_1 = D5 ;
    
    //in_2 -> This variable has the pin number for input 2 of motor
    int in_2 = D6 ;
    
    //button -> This variable has the pin number for the button
    int button = D0;
    
    //volt -> This variable is used to store the reading from the voltage sesnor
    int volt;
    
    //dir -> This flag is used to limit the execution of conditions of the switch
    bool dir = true;
    
    //ledPin_in -> This variable has the pin number for the LED indicator 
    int ledPin_in = D1;
    
    //down -> This flag is used to limit the system's down movement
    bool down = true;
    
    //up -> This flag is used to limit the system's up movement
    bool up = false;  
};
#endif
