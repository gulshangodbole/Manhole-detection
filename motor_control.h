/*===========================================
 *Project Name : Manhole Indication System 
 *Author List : Sankalp Singh
 *Filename : motor_control.h
 *Functions : NONE
 *Global Variables : NONE
============================================*/

#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

class motor_control{
	public :
		void operate(int move);
	private :
		void forward();
		void reverse();
		void brake();
};
#endif
