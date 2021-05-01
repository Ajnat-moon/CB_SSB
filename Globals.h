/************************************************************************/
/*                          Hammersoft G.S.                             */
/*                    CB 27MHz Am/SSB Transmitter  Arduino              */
/*                            Globals.h                                 */
/*                                                                      */
/*                      Author: Gerd Scherzinger                        */
/*                      by Hammersoft April 2021                        */
/*                                                                      */
/************************************************************************/
/************************************************************************
*    0=PD0 1=PD1 2=PD2 3=PD3 4=PD4 5=PD5 6=PD6 7=PD7
*    8=PB0 9=PB1 10=PB2 11=PB3 12=PB4 13=PB5
*    14=PC0->A0 15=PC1->A1 16=PC2->A2 17=PC3->A3 18=PC4->A4 19=PC5->A5
*************************************************************************/
#include <stdint.h>
#include <Rotary.h> 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <AH_AD9850.h> //http://www.arduino-projekte.de/index.php?n=7
#include "myVersion.h"
myVersion Vers(16,false);

//*********************** OLED Display defnition *******************
// pin definition for 1,8 zoll Display
#define TFT_CS   4
#define TFT_DC   6
#define TFT_RST  5

// For 1.44" and 1.8" TFT with ST7735 (including HalloWing) use:
    Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

const byte lcdW = 160 ;
const byte lcdH = 128 ;
const byte fontWidth = 10 ;
const byte fontHeigth = 20 ;



//*********************** Start Screen Time and Version *******************
#define VersionTime 2000
#define Version_Char "Vers: 0.10"
#define Versionsnummer 3 // LED Blinki

//*********************** Atmel Pin Definition *******************

 
