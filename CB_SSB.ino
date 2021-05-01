/************************************************************************/
/*                          REVOX Ausbildung                            */
/*                    OLED Funktionsgenerator  Arduino                  */
/*                     Funktionsgenerator.ino (MAIN)                    */
/*                                                                      */
/*                      Author: Gerd Scherzinger                        */
/*                      by Hammersoft Dezember 2018                     */
/*                      Fuse_HIgh 0xD9 Fuse_Low  0xDE                   */
/************************************************************************/

#include "Globals.h"

//*****************************************************************
void setup()
//*****************************************************************
{
//pinMode(TasteForm, INPUT_PULLUP );
//pinMode(TasteFreq, INPUT_PULLUP);
//digitalWrite(TasteFreq, HIGH); //Pullups
analogReference(DEFAULT);
  
start_display(); 
Version();
mode();
chanel();
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
  
    delay(20);
   
  
}
