/*                          Hammersoft G.S.                             */
/*                    CB 27MHz Am/SSB Transmitter  Arduino              */
/*                            CB_SSB.ino                                */
/*                                                                      */
/*                      Author: Gerd Scherzinger                        */
/*                      by Hammersoft April 2021                        */
/************************************************************************/

#include "Globals.h"

//*****************************************************************
void setup()
//*****************************************************************
{
 Serial.begin(9600);
 pinMode(mode_sw, INPUT_PULLUP );
//pinMode(TasteFreq, INPUT_PULLUP);
//digitalWrite(TasteFreq, HIGH); //Pullups
 analogReference(DEFAULT);
 AD9850.reset();                   //reset module
 
  
 start_display(); 
 Version();
 mode_dsp(mode_var);
 channel_dsp(channel);
 AD0850_set_freq();
 voltage();
 s_meter();
 

// Configure interrupt for rotary encoder and enable.
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT19);
  sei();


}

//*****************************************************************
void loop()
//*****************************************************************
{
    button_check();
    delay(20);
   
  
}

//*****************************************************************
ISR(PCINT2_vect) 
//*****************************************************************
{
  unsigned char result = r.process();
  if (result == DIR_NONE) {
    //Serial.println("ups");// do nothing
  }
  else if (result == DIR_CW) {
    Serial.println("ClockWise");
    channel++;
    if(channel >80)channel=1;
    channel_dsp(channel);
  }
  else if (result == DIR_CCW) {
    Serial.println("CounterClockWise");
    
    channel--;
    if(channel<1)channel=80;
    channel_dsp(channel);
  }
    AD0850_set_freq();
}
//*****************************************************************
void button_check()
//*****************************************************************
{
 if(digitalRead(mode_sw)==LOW)
   {
    delay(1);
    if(mode_sw_flag == LOW)
     {
      mode_var++;
      mode_dsp(mode_var);
      if (mode_var > 2) mode_var=0;
      mode_sw_flag = HIGH;
      
     }
   } else if(mode_sw_flag== HIGH) mode_sw_flag =LOW;
}
