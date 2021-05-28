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
  analogReference(DEFAULT);
  Wire.begin();
  AD9850.reset();                   //reset module

  
  
  start_display();
  //Version();
  mode_dsp(mode_var);
  audio_mode(Audio_in);
  channel_dsp(channel, offset_freq);
  AD0850_set_freq();



  // Configure interrupt for rotary encoder and enable.
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT19);

  //************Timern interrupt ***********************************
  TCCR2B = 0x00;
  TCCR2A = 0x00;
  TCNT2 = 130;
  TCCR2B |= (1 << CS22) | (1 << CS20); // Prescale 128 (Timer/Counter started)
  TCCR2B &= ~(1 << CS21);        // CS22=1 CS21=0 CS20=1 -> prescale = 128
  TIMSK2 |= (1 << TOIE2); //Set the interrupt request
  sei();
  
}

//*****************************************************************
void loop()
//*****************************************************************
{
  button_check();
  rotate_check();
  ad_convert();


}

//*****************************************************************
void ad_convert()
//*****************************************************************
{
  int val;
  int val1;
  int val2;
  int mic_Switch_Val;
  int audio_Switch_Val;
  byte i;
 mic_Switch_Val = analogRead(mic_Switch);
//--------------------Taste Mic CH- +----------------------------------- 
  if (mic_Switch_Val < 100 )
  {
    delay(1);
    if (mic_switch_flag1 == LOW)
    {

      channel--;
      if (channel < 1)channel = 80;
      offset_freq = 0;
      fine_bit =0;
      channel_dsp(channel, offset_freq);
      AD0850_set_freq();
      mic_switch_flag1 =HIGH;
    }
  } else if (mic_switch_flag1 == HIGH) mic_switch_flag1 = LOW;
//--------------------Taste Mic CH+ ----------------------------------- 
if (mic_Switch_Val > 580 && mic_Switch_Val < 750)
  {
    delay(1);
    if (mic_switch_flag2 == LOW)
    {

      channel++;
      if (channel > 80)channel = 1;
      offset_freq = 0;
      fine_bit =0;
      channel_dsp(channel, offset_freq);
      AD0850_set_freq();
      mic_switch_flag2 =HIGH;
    }
  } else if (mic_switch_flag2 == HIGH) mic_switch_flag2 = LOW;


//--------------------Taste Audio ----------------------------------- 
audio_Switch_Val = analogRead(audio_push);
if (audio_Switch_Val < 880)
  {
    delay(10);
    if (audio_switch_flag == LOW)
    {

      Audio_in++;
      if (Audio_in > 1)Audio_in = 0;
      audio_mode(Audio_in);
      audio_switch_flag =HIGH;
    }
  } else if (audio_switch_flag == HIGH) audio_switch_flag = LOW;


//--------------------Taste TX +----------------------------------- 

  if (timer0 > 500)        //500ms
  {
    val = analogRead(supply);
    val1 = analogRead(hf_signal);
    val2 = analogRead(tx_push);
    s_meter(val1, val2);
    voltage(val);
    timer0 = 0;
  }


}


//*****************************************************************
ISR(TIMER2_OVF_vect)    //This is the interrupt request Timer
//*****************************************************************
{
  TCNT2 = 130;
  timer0++;

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

  int temp;
  temp = analogRead(mic_Switch);

//--------------------Taste mode ---------------------------------- 

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

//--------------------Taste push fine Mic ---------------------------
 
  if ((digitalRead(push_sw) == LOW) || (temp > 200 && temp < 400))
  {
    Serial.println(temp);
    delay(1);
    if (push_switch_flag == LOW)
    {

      fine_bit = !fine_bit;
      channel_dsp(channel, offset_freq);
      push_switch_flag = HIGH;

    }
  } else if (push_switch_flag == HIGH) push_switch_flag = LOW;



}
