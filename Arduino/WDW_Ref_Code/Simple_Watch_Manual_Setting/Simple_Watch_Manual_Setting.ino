/*********************************************************************
iRoboticist Workshops : http://Workshop.iRoboticist.com

This is an example sketch of Simple Watch 

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
//Set initial time. The Clock will always start from here when reset.   
int Hr = 0; int Min = 0; int Sec = 0;  //midnight (24hr Format)
int Day = 1; int Mnt = 1; int Yr = 2014; // Jan 1, 2014
  
void setup(void) 
{
  display.begin();
  display.clearDisplay();
  
  //Load Initial Time
  setTime(Hr,Min,Sec,Day,Mnt,Yr);//(HH:MM:SS::DD:MM:YY)
}

void loop (void) 
{ 
  // Screen must be refreshed at least once per second
  display.fillScreen(BLACK);  //Background Color is set to WHITE by default
  display.setTextColor(WHITE); // Text color has to be specified everytime 
  
  //Set the Start location (W,H) 
  display.setCursor(0,20); //(0,0) will start from top left corner.
  
  display.setTextSize(2);
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
  
  display.refresh();
  delay(500);
}


void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  //display.print(":");
  if(digits < 10)
    display.print('0');
  display.print(digits);
}

//Weekdays number are provided through time.h
//The following function helps convert it to appropriate names 
void printWeekday(int wd){
  if (wd == 1){
    display.print("Sun");}
  else if (wd == 2){
    display.print("Mon");}
  else if (wd == 3){
    display.print("Tue");}
  else if (wd == 4){
    display.print("Wed");}
  else if (wd == 5){
    display.print("Thu");}
  else if (wd == 6){
    display.print("Fri");}
  else if (wd == 7){
    display.print("Sat");}
}
/*********************************************************************
Some useful resources:

  http://arduino.cc  There are pleanty of example cofes & the reference section is handy while coding
  
  http://bildr.org Bildr is an awesome site where they have easy-to-follow articles that help you hit the ground running

  http://learn.adafruit.com Adafruit learning is helpful if you are using products from Adafruit 

  https://learn.sparkfun.com Sparkfun have great set of tutorials for almost any product suppiled by them 
    
    
**********************************************************************/
