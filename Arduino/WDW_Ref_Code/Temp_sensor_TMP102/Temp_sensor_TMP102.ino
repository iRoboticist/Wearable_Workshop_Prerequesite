/*********************************************************************
iRoboticist Workshops: http://Workshop.iRoboticist.com

This is an example sketch of using Temperatur Sensor TMP102 with LCD Dispplay

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

/* ABOUT I2C & TMP102
I2C is a 2-wire serial connection, SDA (Data) and SCL (Clock) – 
On your Arduino Micro SDA is on pin 2, and SCL is on analog pin 3. 
Like most I2C devices, when communicating with one on an Arduino, we will be using the Wire library.

The TMP102 is a very simple, yet accurate, ambient temperature sensor which is capable of detecting
0.0625ºC changes between -25 and +85°C, with an accuracy of 0.5°C. And it does all of this while 
only consuming 10µA

The sensor has an address pin (ADD0) that is used to change the address the sensor is located at. 
This is useful if you need more than one of these hooked up to one Arduino, 
you can still call them independently even on the same bus. 
We will ground this pin so that the sensor will use the address of 72 (0×48 in hex). 
Connecting this pin to V+ (3.3v on the arduino) would set the address to 73 (0×49 in hex), 
and you would just need to change that address at the top of the code ( int tmp102Address = 0×49; ).*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>

int tmp102Address = 0x48; //I2C address for TMP102 is 0x48

Adafruit_SharpMem display(SCK, MOSI, SS);

#define BLACK 0
#define WHITE 1

void setup(void) 
{
  display.begin();
  display.clearDisplay();
  Wire.begin(); //Initialize I2C
  }

void loop(void) 
{
  /* Get a new sensor event */ 
   display.fillScreen(BLACK);
   display.setTextColor(WHITE);
   display.setCursor(0,15);
   display.setTextSize(1);
   
   float celsius = getTemperature();
   display.println("  Temp TMP102  "); 
   display.println("");
   display.setTextSize(2);
   display.setCursor(06,30);
   display.print(celsius); 
   display.write(247); //Alt-code for Degree Symbol
   display.println("C");
   
   float fahrenheit = (1.8 * celsius) + 32;   
   display.setCursor(06,55);
   display.print(fahrenheit);
   display.write(247);
   display.print("F");
  
   display.refresh();
   delay(500);
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

/*********************************************************************
Some useful resources:

  http://arduino.cc  There are pleanty of example cofes & the reference section is handy while coding
  
  http://bildr.org Bildr is an awesome site where they have easy-to-follow articles that help you hit the ground running

  http://learn.adafruit.com Adafruit learning is helpful if you are using products from Adafruit 

  https://learn.sparkfun.com Sparkfun have great set of tutorials for almost any product suppiled by them like TMP102 here :)
  
*********************************************************************/
