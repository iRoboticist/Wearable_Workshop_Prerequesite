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
#include <Wire.h>
#include <ADXL345.h>

Adafruit_SharpMem display(SCK, MOSI, SS);
ADXL345 adxl;
#define BLACK 0
#define WHITE 1

//Assigning pin numbers for Mode, Up & Down Buttons

const int ModeButton = 8;     
const int UpButton = 9;
const int DownButton = 10;

const int vMtr=6; //Vibration Motor

const int ledPin =  13;
int steps = 4790; int taps = 0; int dtaps =0;
int UpState;
int DownState;
int mode = 0;
int tmp102Address = 0x48; //I2C address for TMP102 is 0x48
float celcius;
float fahrenheit;
//Set initial time. The Clock will always start from here when reset.   
int Hr = 23; int Min = 00; int Sec = 0; //midnight (24hr Format)
int Day = 18; int Mnt = 4; int Yr = 2014; // Jan 1, 2014
  

void setup(void) 
{
  display.begin();
  display.clearDisplay();
  Wire.begin(); //Initialize I2C
  
  //Define Button Pins as Input
  pinMode(ModeButton, INPUT);
  pinMode(UpButton, INPUT);
  pinMode(DownButton, INPUT);
  
  //Define Motor & LED pin as Output
  pinMode(vMtr, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  //Activate internal Pull-up
  //No need to connect external resistor. Connect button directly between Pin & GND
  digitalWrite(ModeButton, HIGH);  
  digitalWrite(UpButton, HIGH);
  digitalWrite(UpButton, HIGH);
  
  adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(50); //62.5mg per increment
  adxl.setInactivityThreshold(50); //62.5mg per increment
  adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
 
  //look of activity movement on this axes - 1 == on; 0 == off 
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);
 
  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);
 
  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);
 
  //set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(50); //62.5mg per increment
  adxl.setTapDuration(15); //625μs per increment
  adxl.setDoubleTapLatency(80); //1.25ms per increment
  adxl.setDoubleTapWindow(200); //1.25ms per increment
 
  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
 
  //setting all interupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );
 
  //register interupt actions - 1 == on; 0 == off  
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);
 
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
  float celsius = getTemperature();
  float fahrenheit = (1.8 * celsius) + 32;
  int x,y,z;  
  adxl.readAccel(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z
  //activity
  byte interrupts = adxl.getInterruptSource();
  if(adxl.triggered(interrupts, ADXL345_ACTIVITY)){
    display.println("activity"); 
    steps = steps++;
     //add code here to do when activity is sensed
  }
  switch (mode) {
    
    default: //Watch Face
                                              // Screen must be refreshed at least once per second
      display.fillScreen(BLACK);
      display.setCursor(0,8);
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
      display.println("________________");
      display.print(" ");display.setTextSize(2); display.write(2); 
      display.setTextSize(1);
      display.println("  Steps"); 
      //display.drawLine(20,73,50,73,WHITE);
      display.println ("  ");display.setTextSize(2);display.print ("  ");display.print(steps); //display.print(" / 10,000");
      mode=0;
      break;
      
    case 1: //Display Temperature 
      /* Get a new sensor event */ 
       display.fillScreen(BLACK);
       display.setTextColor(WHITE);
       display.setCursor(0,5);
       display.setTextSize(2);
       
       display.println("  Temp  "); 
       display.println(" ");
       display.setTextSize(1);
       display.setCursor(10,40);
       display.print(celsius); 
       display.write(247); //Alt-code for Degree Symbol
       display.println("C");
   
       display.setCursor(40,55);
       display.print(fahrenheit);
       display.write(247);
       display.print("F");
       
       break;
  
    case 2:
       display.fillScreen(BLACK);
       display.setTextColor(WHITE);
       display.setCursor(0,5);
       display.setTextSize(1);
       display.print (" G: 255"); display.println(""); 
       display.print("    X: "); display.print(x); display.println("");
       display.print("      Y: "); display.print(y); display.println("");
       display.print("        Z: "); display.print(z); display.println("");
       display.println("");
       display.print(" Steps = "); display.println(steps);
       //display.print(" Taps = "); display.println(taps);
       //display.print(" D.Taps = "); display.println(dtaps);
       break;
    
    case 3:     //Adjust Hour
      
      display.fillScreen(BLACK);
      display.setCursor(0,10);
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.println("  ADJUST TIME");
      display.println("");
      
      Hr = hour(); Min = minute(); 
      UpState = digitalRead(UpButton);
      DownState = digitalRead(DownButton);
      if (UpState == LOW){
        Hr= Hr++;  
      } 
      else if (DownState == LOW){
        Hr=Hr--;
      }
      
      if (Hr==-1) {Hr =23;}
      
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
      
    case 4:                                       //Adjust Min
      display.fillScreen(BLACK);
      display.setCursor(0,10);
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.println("  ADJUST TIME");
      display.println("");
      
      Hr = hour(); Min = minute(); 
      UpState = digitalRead(UpButton);
      DownState = digitalRead(DownButton);
      if (UpState == LOW){
        Min= Min++;  
      } 
      else if (DownState == LOW){
        Min=Min--;
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
      
    case 5: //Adjust Date
      display.fillScreen(BLACK);
      display.setCursor(0,10);
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.println("  ADJUST DATE");
      display.println("");
      display.setTextSize(2);
      display.println(" Day");
      
      Day = day(); Mnt = month(); Yr = year();
      UpState = digitalRead(UpButton);
      DownState = digitalRead(DownButton);
        if (UpState == LOW){
          Day= Day++;  
        } 
        else if (DownState == LOW){
          Day=Day--;
        }
        if (Day>>31){
          Day=1;
        }
      display.print("    ");
      printDigits(Day);
      setTime(Hr,Min,Sec,Day,Mnt,Yr);
      break;
    
    case 6:                                        //Adjust Month
      display.fillScreen(BLACK);
      display.setCursor(0,10);
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.println("  ADJUST DATE");
      display.println("");
      display.setTextSize(2);
      display.println(" Month");
      
      Day = day(); Mnt = month(); Yr = year();
      UpState = digitalRead(UpButton);
      DownState = digitalRead(DownButton);
      if (UpState == LOW){
        Mnt= Mnt++;  
      } 
      else if (DownState == LOW){
        Mnt=Mnt--;
      }
      if (Mnt>>13){
        Mnt=1;
      }
      
      display.print("    ");
      printDigits(Mnt);
      setTime(Hr,Min,Sec,Day,Mnt,Yr);
      break;
     
    case 7:                                        //Adjust Year (UP)
      display.fillScreen(BLACK);
      display.setCursor(0,10);
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.println("   ADJUST DATE ");
      display.println("");
      display.setTextSize(2);
      display.println(" Year");
      
      Day = day(); Mnt = month(); Yr = year();
      UpState = digitalRead(UpButton);
      DownState = digitalRead(DownButton);
      if (UpState == LOW){
        Yr= Yr++;  
      }
      else if (DownState == LOW){
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


float getTemperature(){
  Wire.requestFrom(tmp102Address,2); 

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  //it's a 12bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  float celsius = TemperatureSum*0.0625;
  return celsius;
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
