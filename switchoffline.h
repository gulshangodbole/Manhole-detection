/*===========================================
 *Project Name : Manhole Indication System 
 *Author List : Sankalp Singh
 *Filename : switchoffline.h
 *Functions : NONE
 *Global Variables : NONE
============================================*/

#ifndef SWITCHOFFLINE_H
#define SWITCHOFFLINE_H

#include "Arduino.h"
class switchoffline{
	public :
		void switching_offline();

    //button_offline -> This variable has the pin number of the button
    int button_offline = D0;

    //dir_offline -> This flag is used to control the continous execution of the conditional statements
    bool dir_offline = true;
};
#endif
