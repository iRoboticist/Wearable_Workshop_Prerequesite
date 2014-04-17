/*********************************************************************
iRoboticist Workshops: http://Workshop.iRoboticist.com

This is an example sketch of Adjustable Watch using Switch Mode

The code is developed for Arduino Micro with 1.3" Monochrome SHARP Memory Displays. 
These displays use Hardware SPI to communicate, 3 pins are required to  
interface

(***If you are using other Arduino without Hardware SPI 
define pins for SCK, SS & MOSI)

Written by Saurabh Palan/iRoboticist  for iRoboticist Workshop.  
Twitter: http://twitter.com/iRoboticist
Facebook: http://facebook.com/iRoboticist

All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include <Time.h>

Adafruit_SharpMem display(SCK, MOSI, SS);

#define BLACK 0
#define WHITE 1

//Assigning pin numbers for Mode & Adjust Buttons
const int ModeButton = 8;     
const int AdjustButton = 9;

const int ledPin =  13;

int adjState;
int mode = 0;
  
//Set initial time. The Clock will always start from here when reset.   
int Hr = 0; int Min = 0; int Sec = 0; //midnight (24hr Format)
int Day = 1; int Mnt = 1; int Yr = 2014; // Jan 1, 2014
  

void setup(void) 
{
  display.begin();
  display.clearDisplay();
  
  //Define Button Pins as Input
  pinMode(ModeButton, INPUT);
  pinMode(AdjustButton, INPUT);
  
  //Activate internal Pull-up
  //No need to connect external resistor. Connect button directly between Pin & GND
  digitalWrite(ModeButton, HIGH);  
  digitalWrite(AdjustButton, HIGH);
  
  pinMode(ledPin, OUTPUT); 
  setTime(Hr,Min,Sec,Day,Mnt,Yr);//(HH:MM:SS::DD:MM:YY)*/
}

void loop (void) 
{ 
  int buttonState = digitalRead(ModeButton);
  if (buttonState == LOW) {     
    // turn LED on:    
    mode= mode++;
    //digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
    
  switch (mode) {
    
    default: 
                                              // Screen must be refreshed at least once per second
      display.fillScreen(BLACK);
      display.setCursor(0,10);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      printDigits(hour());
      display.print(":");
      printDigits(minute());
      display.print(":");
      printDigits(second());
      display.println(" ");
      display.setTextSize(1);
      display.print(" "); 
      printWeekday(weekday());
      display.print(" "); 
      printDigits(month());
      display.print("/");
      printDigits(day());
      display.print("/");
      display.println(year()); 
      mode=0;
      break;
  
    case 1:                                     //Adjust Hour
      
      display.fillScreen(BLACK);
      display.setCursor(0,10);
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.println("  ADJUST TIME");
      display.println("");
      
      Hr = hour(); Min = minute(); 
      adjState = digitalRead(AdjustButton);
      if (adjState == LOW){
        Hr= Hr++;  
      } 
      if (Hr>>23){
        Hr=0;
      }
      display.setTextSize(2);
      display.print(" ");
      printDigits(Hr);
      display.print(":");
      printDigits(Min);
      //display.print(":");
      //printDigits(Sec);
      display.drawLine(11, 42, 33,42, WHITE);
      display.drawLine(11, 43, 33,43, WHITE);
      
      setTime(Hr,Min,Sec,Day,Mnt,Yr);
      
      break;
      
    case 2:                                       //Adjust Min
      display.fillScreen(BLACK);
      display.setCursor(0,10);
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.println("  ADJUST TIME");
      display.println("");
      
      Hr = hour(); Min = minute(); 
      adjState = digitalRead(AdjustButton);
      if (adjState == LOW){
        Min= Min++;  
      } 
      if (Min>>59){
        Min=0;
      }
      display.setTextSize(2);
      display.print(" ");
      printDigits(Hr);
      display.print(":");
      printDigits(Min);
      display.drawLine(47, 42, 69,42, WHITE);
      display.drawLine(47, 43, 69,43, WHITE);
      setTime(Hr,Min,Sec,Day,Mnt,Yr);
      
      break;
      
    case 3: //Adjust Date
      display.fillScreen(BLACK);
      display.setCursor(0,10);
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.println("  ADJUST DATE");
      display.println("");
      display.setTextSize(2);
      display.println(" Day");
      
      Day = day(); Mnt = month(); Yr = year();
      adjState = digitalRead(AdjustButton);
        if (adjState == LOW){
          Day= Day++;  
        } 
        if (Day>>31){
          Day=1;
        }
      display.print("    ");
      printDigits(Day);
      setTime(Hr,Min,Sec,Day,Mnt,Yr);
      break;
    
    case 4:                                        //Adjust Month
      display.fillScreen(BLACK);
      display.setCursor(0,10);
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.println("  ADJUST DATE");
      display.println("");
      display.setTextSize(2);
      display.println(" Month");
      
      Day = day(); Mnt = month(); Yr = year();
      adjState = digitalRead(AdjustButton);
      if (adjState == LOW){
        Mnt= Mnt++;  
      } 
      if (Mnt>>13){
        Mnt=1;
      }
      
      display.print("    ");
      printDigits(Mnt);
      setTime(Hr,Min,Sec,Day,Mnt,Yr);
      break;
     
    case 5:                                        //Adjust Year (UP)
      display.fillScreen(BLACK);
      display.setCursor(0,10);
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.println("   ADJUST DATE ");
      display.println("");
      display.setTextSize(2);
      display.println(" Year+");
      
      Day = day(); Mnt = month(); Yr = year();
      adjState = digitalRead(AdjustButton);
      if (adjState == LOW){
        Yr= Yr++;  
      } 
      display.print("    ");
      printDigits(Yr);
      setTime(Hr,Min,Sec,Day,Mnt,Yr);
      
      break;
     
     case 6:                                       //Adjust Year (DOWN)
      display.fillScreen(BLACK);
      display.setCursor(0,10);
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.println("   ADJUST DATE");
      display.println("");
      display.setTextSize(2);
      display.println(" Year-");
      
      Day = day(); Mnt = month(); Yr = year();
      adjState = digitalRead(AdjustButton);
      if (adjState == LOW){
        Yr= Yr--;  
      } 
      
      display.print("    ");
      printDigits(Yr);
      setTime(Hr,Min,Sec,Day,Mnt,Yr);
      break;
  }  

  
  display.refresh();
  delay(300);
  
 }


void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  //display.print(":");
  if(digits < 10)
    display.print('0');
  display.print(digits);
}


void printWeekday(int wd){
  if (wd == 1){
    display.print("Sun");
  }
  else if (wd == 2){
    display.print("Mon");
  }
  else if (wd == 3){
    display.print("Tue");
  }
  else if (wd == 4){
    display.print("Wed");
  }
  else if (wd == 5){
    display.print("Thu");
  }
  else if (wd == 6){
    display.print("Fri");
  }
  else if (wd == 7){
    display.print("Sat");
  }
}


/*********************************************************************
Some useful resources:

  http://arduino.cc  There are pleanty of example cofes & the reference section is handy while coding
  
  http://bildr.org Bildr is an awesome site where they have easy-to-follow articles that help you hit the ground running

  http://learn.adafruit.com Adafruit learning is helpful if you are using products from Adafruit 

  https://learn.sparkfun.com Sparkfun have great set of tutorials for almost any product suppiled by them 
  
*********************************************************************/
