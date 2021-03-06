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
  tft.fillRect(115, 33 , 40 , 15, ST77XX_BLACK);
  tft.setCursor(115, 33);
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
void audio_mode(unsigned char audio)
//*****************************************************************
{
  Serial.print("audio_mode: ");
  Serial.println(audio);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setRotation(1);
  tft.setTextSize(1);
  tft.fillRect(10, 6 , 100 , 10, ST77XX_BLACK);
  tft.setCursor(10, 6);
  switch (audio)
  {
    case 0:
      tft.print("Voice");
      Wire.beginTransmission(PCF8574_mic);
      Wire.write(0x01);
      Wire.endTransmission();
      break;
    case 1:
      tft.print("Dual_Tone");
      Wire.beginTransmission(PCF8574_mic);
      Wire.write(0x00);
      Wire.endTransmission();
      break;

  }

}

//*****************************************************************
void channel_dsp(unsigned char  data, int offset)
//*****************************************************************
{
  char frequenz_string[10] ;

  tft.setRotation(1);
  tft.setCursor(15, 27);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.print("Ch ");
  tft.fillRect(50, 26 , 60 , 23, ST77XX_BLACK);
  tft.println(data);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(17, 63);
  tft.fillRect(17, 63 , 142 , 18, ST77XX_BLACK);

  tft.print(freqenz[channel] * 0.001, 3);
  if (fine_bit)
  {
    tft.setTextSize(1);
    tft.setCursor(85, 70);
    tft.print(" MHz");
    tft.setTextSize(2);
    tft.setCursor(118, 63);
    tft.println(offset);
  } else
  {
    tft.setTextSize(2);
    tft.println(" MHz");
  }

}
//*****************************************************************
void voltage(int value)
//*****************************************************************
{
  float voltage;
  tft.setRotation(1);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_YELLOW);
  tft.fillRect(110, 6 , 30 , 10, ST77XX_BLACK);
  tft.setCursor(110, 6);
  voltage = value * 0.0049 * voltage_divider;
  tft.print(voltage);
  tft.println(" V");

}
//*****************************************************************
void s_meter(int value, int temp)
//*****************************************************************
{
  tft.setRotation(1);
  tft.fillRect((20 + value / 6), 100 , (135 - value / 6), 10, ST77XX_BLACK);
  if (temp > 100)tft.fillRect(20, 100 , (value / 6), 10, ST77XX_GREEN);
  else tft.fillRect(20, 100 , (value / 6), 10, ST77XX_RED);

  tft.setTextSize(1);
  tft.setCursor(4, 101);
  if (temp > 100)
  {
    tft.fillRect(6 , 100 , 14, 10, ST77XX_GREEN);
    tft.setTextColor(ST77XX_BLACK);
    tft.setCursor(7, 101);
    tft.println("RX");
  } else
  {
    tft.fillRect(6 , 100 , 14, 10, ST77XX_RED);
    tft.setTextColor(ST77XX_BLACK);
    tft.setCursor(7, 101);
    tft.println("TX");
  }
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(5, 115);
  tft.println("S  1  3  5  7  9  +10 +20 ");
  tft.drawLine(4 , 98 , 4, 111, ST77XX_WHITE);
  tft.drawLine(4 , 98 , 155, 98, ST77XX_WHITE);
  tft.drawLine(155, 98 , 155, 111, ST77XX_WHITE);
  tft.drawLine(4 , 111 , 155, 111, ST77XX_WHITE);
  if (temp > 100)
  {
    tft.drawRect(0 , 0 , 160, 128, ST77XX_YELLOW);
    tft.drawLine(0 , 19 , 160, 19, ST77XX_YELLOW);
    tft.drawLine(0 , 93 , 160, 93, ST77XX_YELLOW);
  } else
  {
    tft.drawRect(0 , 0 , 160, 128, ST77XX_RED);
    tft.drawLine(0 , 19 , 160, 19, ST77XX_RED);
    tft.drawLine(0 , 93 , 160, 93, ST77XX_RED);
  }
}
