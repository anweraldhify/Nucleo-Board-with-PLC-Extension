#include "trafficLight.h"

extern __IO uint16_t Loop_3sTime;  //time :3s
extern __IO uint16_t Loop_5sTime;  //time :5s
extern __IO uint16_t Loop1_10sTime; //time1 :10s
extern __IO uint16_t Loop2_10sTime; //time2 :10s
extern __IO uint16_t Loop_60sTime; //time :60s
extern __IO uint16_t Loop_cycleTime;
extern uint8_t Loop_cycleTime_flag ;
extern uint8_t State;
extern uint8_t Led_State ;

void loop(void)
{
  if(Loop_cycleTime_flag)   // Start the execution if the User button on the STM32 is pressed.
  {
    Loop_cycleTime_flag=0;
    
		if (Loop_5sTime)  
		{
			Loop_5sTime--;       // The time will be decremented by one until it reaches zero, then the 5 seconds are over.
			if (!Loop_5sTime)   
			{
				State++;           // Move to the next traffic light state
				Loop1_10sTime=10 * cycleCoefficient;   // Setting the time to 10 seconds
			}
		}
		else if (Loop1_10sTime)   
		{
			Loop1_10sTime--;     
			if (!Loop1_10sTime)
			{
      State++;
			Loop2_10sTime=10 * cycleCoefficient;
			}
		}
    else if (Loop2_10sTime)
		{
			Loop2_10sTime--;
			if (!Loop2_10sTime)
			{
			State++;
			Loop_3sTime=3 * cycleCoefficient;
			}
		}
    else if (Loop_3sTime)
		{
			Loop_3sTime--;
			if (!Loop_3sTime)
			{
				State++;
				Loop_60sTime=60 * cycleCoefficient;
			}
		}
		else if (Loop_60sTime)
		{
			Loop_60sTime--;
			if (!Loop_60sTime)
			{
      State=1;
			Loop_5sTime = 5 * cycleCoefficient;
			Loop_60sTime = 0;
			}
		}
  }
}

void trafficLightState()
{
  if (Request == 0)
  {
    if (State == Drive)
    {
      Loop_60sTime = 0;          
      State = 1;
      Loop_5sTime = 5 * cycleCoefficient;
			Loop_60sTime = 0;
    }
    else
		{
    State = 1;          // parameters for the loop initialization 
    Loop_5sTime = 5 * cycleCoefficient;
		Loop_60sTime = 0;
		}
  }

  switch (State)
  {
  case System:            // C_red(OUT1)  C_yello(OUT2)  C_green(OUT3)  P_red(OUT4)  P_green(OUT5)    
    Led_State = 0x00;     //      0            0              0              0            0
    break;
  case Ready:
    Led_State = 0x0a;     //      0            1              0              1            0
    break;
  case Go:
    Led_State = 0x11;     //      1            0              0              0            1
    break;
  case Stop:
    Led_State = 0x09;     //      1            0              0              1            0
    break;
  case Attention:
    Led_State = 0x0b;     //      1            1              0              1            0
    break;
  case Drive:
    Led_State = 0x0c;     //      0            0              1              1            0
    break;
  }
}
