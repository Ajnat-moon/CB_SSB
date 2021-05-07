/************************************************************************/
/*                          Hammersoft G.S.                             */
/*                    CB 27MHz Am/SSB Transmitter  Arduino              */
/*                            AD8950.ino                                */
/*                                                                      */
/*                      Author: Gerd Scherzinger                        */
/*                      by Hammersoft April 2021                        */
/*                                                                      */
/************************************************************************/

//*****************************************************************
void AD0850_set_freq()
//*****************************************************************
{
  long AD_frequenz;
  AD_frequenz = freqenz[channel];
  AD9850.set_frequency(0, 0, AD_frequenz * 1000 - 12000000+offset_freq*10);
  //AD9850.set_frequency(0,0,2500);
  Serial.println(AD_frequenz);
  Serial.println(offset_freq);
  

}
