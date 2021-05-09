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
     0=PD0 1=PD1 2=PD2 3=PD3 4=PD4 5=PD5 6=PD6 7=PD7
     8=PB0 9=PB1 10=PB2 11=PB3 12=PB4 13=PB5
     14=PC0->A0 15=PC1->A1 16=PC2->A2 17=PC3->A3 18=PC4->A4 19=PC5->A5
*************************************************************************/
#include <stdint.h>
#include <Rotary.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <AH_AD9850.h>
#include "myVersion.h"
myVersion Vers(16, false);

//*********************** OLED Display PIN defnition *******************
// pin definition for 1,8 zoll Display
#define TFT_CS   4
#define TFT_DC   6
#define TFT_RST  5


// For 1.44" and 1.8" TFT with ST7735 (including HalloWing) use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


//*********************** AD_converter PIN defnition *******************
int supply = A0;
int hf_signal = A1; 


//*********************** AD9850 PIN defnition *******************
const int CLK_PIN = 9;
const int FQ_PIN = 8;
const int Data_PIN = 7;
const int RESET_PIN = 10;


AH_AD9850 AD9850(CLK_PIN, FQ_PIN, Data_PIN, RESET_PIN);


const byte lcdW = 160 ;
const byte lcdH = 128 ;
const byte fontWidth = 10 ;
const byte fontHeigth = 20 ;



//*********************** Start Screen Time and Version *******************
#define VersionTime 2000
#define Version_Char "Vers: 0.10"
#define Versionsnummer 3 // LED Blinki

//*********************** Atmel Pin Definition *******************

Rotary r = Rotary(2, 3);

#define mode_sw 16
#define push_sw 12
#define dpush_sw 21


//*********************** Variable *******************
int freqenz[] = {0,
                 26965, 26975, 26985, 27005, 27015, 27025, 27035, 27055, 27065, 27075,
                 27085, 27105, 27115, 27125, 27135, 27155, 27165, 27175, 27185, 27205,
                 27215, 27225, 27255, 27235, 27245, 27265, 27275, 27285, 27295, 27305,
                 27315, 27325, 27335, 27345, 27355, 27365, 27375, 27385, 27395, 27405,
                 26565, 26575, 26585, 26595, 26605, 26615, 26625, 26635, 26645, 26655,
                 26665, 26675, 26685, 26695, 26705, 26715, 26725, 26735, 26745, 26755,
                 26765, 26775, 26785, 26795, 26805, 26815, 26825, 26835, 26845, 26855,
                 26865, 26875, 26885, 26895, 26905, 26915, 26925, 26935, 26945, 26955
                };
unsigned char mode_switch_flag;        //Variable  Switch Flag
unsigned char push_switch_flag;
unsigned char rotate_left_flag;
unsigned char rotate_right_flag;



unsigned char fine_bit=0;     // Variable for frequenz fine tune
int offset_freq =0;           // VAriable for frequenzy fine Offset
unsigned char mode_var = 1;   //Variable for AM,USB,LSB
unsigned char channel = 1;    //Variable channel
int  timer0=0;                //Variable für TImer2

#define R1 10
#define R2 4.7
#define voltage_divider ((R1+R2)/R2)   //R1+R2/R2 10k+4,7k/4,7k =
