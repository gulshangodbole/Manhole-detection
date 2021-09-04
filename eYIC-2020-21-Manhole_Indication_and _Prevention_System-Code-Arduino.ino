/*============================================================
 *Project Name : Manhole Indication System 
 *Author List : Sankalp Singh
 *Filename : web_sheet.ino
 *Functions : switching(void)
 *Global Variables : stateSwitch
=============================================================*/
#include "declaration.h"
#include "aws.h"
#include "motor_control.h"

aws awsObj;
declaration instance;
motor_control control;

//stateSwitch : It will store the state of switch which will be passed to the web frunction from aws
int stateSwitch = 0;

/*==============================================================================================================================
 * Function Name : switching
 * Input : NONE
 * Output : NONE
 * Logic : The digitalRead() function reads the current state of the switch and then according to the logic if the state is
 *         HIGH the the value of stateSwitch is set to 0 and the operate function of the motor control library is passed 
 *         to turn off the motor and similarly vice versa
 * Example Call : switching();
================================================================================================================================*/

void switching()
{
  int state = digitalRead(instance.button);
    
    //Checking whether the state of the switch is HIGH 
    if(state == HIGH){
      
      //Checking whether the value of flag is true  
      if(instance.dir == true){
        instance.dir = false;
        
        //Calling motor control object and passing the value to stop the motor
        control.operate(0);
        stateSwitch = 0;
        
        //Calling the AWS object and passing the stateSwitch value for posting it to the IoT Core of the AWS
        awsObj.web(stateSwitch);
      }
    }

    //Checking whether the state of the switch is LOW
    else if(state == LOW){
      
      //Checking whether the value of flag is false
      if(instance.dir == false){
        instance.dir = true;
        
        //Calling motor control object and passing the value to start the motor
        control.operate(1);
        stateSwitch = 1;

        //Calling the AWS object and passing the stateSwitch value for posting it to the IoT Core of the AWS
        awsObj.web(stateSwitch);      
    }
  } 
}
void setup()
{
  //Calling the setup function from the declaration library
  instance.data();
}

void loop()
{
  //Calling the switching 
  switching();

  //Calling the AWS web object
  awsObj.web(stateSwitch);
}
