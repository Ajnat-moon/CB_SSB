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
  pinMode(push_sw, INPUT_PULLUP );
  //pinMode(TasteFreq, INPUT_PULLUP);
  //digitalWrite(TasteFreq, HIGH); //Pullups
  analogReference(DEFAULT);
  AD9850.reset();                   //reset module


  start_display();
  //Version();
  mode_dsp(mode_var);
  channel_dsp(channel, offset_freq);
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
  rotate_check();
  


}

//*****************************************************************
ISR(PCINT2_vect)
//*****************************************************************
{
  unsigned char result = r.process();
  if (result == DIR_NONE) {
    //Serial.println("ups");// do nothing
  }
  else if (result == DIR_CW)
  {
    rotate_left_flag = true;
  }
  else if (result == DIR_CCW)
  {
    rotate_right_flag = true;
  }
 
}


//*****************************************************************
void rotate_check()
//*****************************************************************
{
  if (rotate_left_flag)
  {
    if (!fine_bit)
    {
      channel++;
      if (channel > 80)channel = 1;
      offset_freq = 0;
      channel_dsp(channel, offset_freq);
    } else
    {
      offset_freq  ++;
      channel_dsp(channel, offset_freq);
    }
    AD0850_set_freq();
    rotate_left_flag = false;
  }
  if (rotate_right_flag)
  {
    if (!fine_bit)
    {
      channel--;
      if (channel < 1)channel = 80;
      offset_freq = 0;
      channel_dsp(channel, offset_freq);
    } else
    {
      offset_freq  --;
      channel_dsp(channel, offset_freq);
    }
    AD0850_set_freq();
    rotate_right_flag = false;
  }
}

//*****************************************************************
void button_check()
//*****************************************************************
{
  if (digitalRead(mode_sw) == LOW)
  {
    delay(1);
    if (mode_switch_flag == LOW)
    {
      mode_var++;
      mode_dsp(mode_var);
      if (mode_var > 2) mode_var = 0;
      mode_switch_flag = HIGH;

    }
  } else if (mode_switch_flag == HIGH) mode_switch_flag = LOW;

  if (digitalRead(push_sw) == LOW)
  {
    delay(1);
    if (push_switch_flag == LOW)
    {

      fine_bit = !fine_bit;
      channel_dsp(channel, offset_freq);
      push_switch_flag = HIGH;

    }
  } else if (push_switch_flag == HIGH) push_switch_flag = LOW;



}
