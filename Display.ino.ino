/************************************************************************/
/*                          Hammersoft G.S.                             */
/*                    CB 27MHz Am/SSB Transmitter  Arduino              */
/*                            Display.ino                               */
/*                                                                      */
/*                      Author: Gerd Scherzinger                        */
/*                      by Hammersoft April 2021                        */
/*                                                                      */
/************************************************************************/

//*****************************************************************
void start_display()
//*****************************************************************
{
     tft.initR(INITR_BLACKTAB);
     Serial.println("init");
     tft.fillScreen(ST77XX_BLACK);
}

//*****************************************************************
void Version()
//*****************************************************************
{
      tft.setTextColor(ST77XX_YELLOW);
            
      tft.setRotation(1);
      tft.setTextSize(2);
      tft.setCursor(15, 20);
      tft.println("Hammersoft");
      tft.setCursor(15, 50);
      tft.setTextColor(ST77XX_GREEN);
      tft.println(Version_Char);
      delay(VersionTime);
      tft.fillScreen(ST77XX_BLACK);
}
//*****************************************************************
void mode_dsp(unsigned char mod)
//*****************************************************************
{
      Serial.print("mod_dsp: ");
      Serial.println(mod);     
      tft.setTextColor(ST77XX_RED);
      tft.setRotation(1);
      tft.setTextSize(2);
      tft.fillRect(115, 35 , 40 ,15, ST77XX_BLACK);
      tft.setCursor(115, 35);
      switch (mod)
      {
        case 1:
        tft.print("AM");
         break;
        case 2:
         tft.print("USB");
         break; 
        case 3:
         tft.print("LSB");
         break; 
       }
}


//*****************************************************************
void channel_dsp(unsigned char  data)
//*****************************************************************
{ 
    char frequenz_string[10] ;
      
      tft.setRotation(1);
      tft.setCursor(15, 27);
      tft.setTextColor(ST77XX_GREEN);
      tft.setTextSize(3);
      tft.print("Ch ");
      tft.fillRect(50, 26 , 60 ,23, ST77XX_BLACK);
      tft.println(data);
      tft.setTextSize(2);
      tft.setTextColor(ST77XX_WHITE);
      tft.setCursor(20, 63);
      tft.fillRect(20, 63 , 120 ,18, ST77XX_BLACK);
     
      tft.print(freqenz[channel]*0.001,3);
      tft.println(" MHz");
}
//*****************************************************************
void voltage()
//*****************************************************************
{
  tft.setRotation(1);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setCursor(105, 6
  );
  tft.println("12.00 V");
}
//*****************************************************************
void s_meter()
//*****************************************************************
{
  tft.setRotation(1);
 
  tft.fillRect(20, 100 , 80,10, ST77XX_RED);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(5, 115);
  tft.setTextSize(1);
  tft.println("S  1  3  5  7  9  +10 +20 ");
  
  tft.drawRect(0 , 0 , 160,128, ST77XX_YELLOW);
  tft.drawLine(0 , 19 , 160,19, ST77XX_YELLOW);
  tft.drawLine(0 , 90 , 160,90, ST77XX_YELLOW);
}
