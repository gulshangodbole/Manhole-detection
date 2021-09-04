/*===========================================
 *Project Name : Manhole Indication System 
 *Author List : Sankalp Singh
 *Filename : declaration.cpp
 *Functions : data(void)
 *Global Variables : NONE
============================================*/

#include "switchoffline.h"
#include "aws.h"
#include "declaration.h"

aws setupObj;
switchoffline setSwitch;

/*====================================================================================================
 * Function Name : data
 * Input : NONE 
 * Output : NONE
 * Logic : This function is used to set the Baudrate, pinModes and also to setup the AWS for our ESP 
 * Example Call : obj.data();
======================================================================================================*/

void declaration :: data() {
  Serial.begin(115200);
  pinMode(ledPin_in, OUTPUT);
  pinMode(in_1, OUTPUT) ;
  pinMode(in_2, OUTPUT) ;

  pinMode(button, INPUT_PULLUP) ;
  pinMode(setSwitch.button_offline, INPUT_PULLUP) ;

  digitalWrite(ledPin_in,HIGH);
  digitalWrite(in_1,HIGH);
  digitalWrite(in_2,HIGH);
  
  setupObj.setupAWS();
}
