/*===========================================
 *Project Name : Manhole Indication System 
 *Author List : Sankalp Singh
 *Filename : aws.h
 *Functions : NONE
 *Global Variables : NONE
============================================*/

#ifndef AWS_H
#define AWS_H

class aws{
	public: 
		void web(int state);
		void setupAWS();
		void callback(char* topic, byte* payload, unsigned int length);
   
	private: 
		void reconnect();
		void setup_wifi();	
};
#endif
