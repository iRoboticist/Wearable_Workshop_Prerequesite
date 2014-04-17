/*********************************************************************
 * iRoboticist Workshops: http://Workshop.iRoboticist.com
 * 
 * This is an example sketch for learning to use LCD Display.
 * 
 * The code is developed for Arduino Micro with 1.3" Monochrome SHARP Memory Displays. 
 * These displays use Hardware SPI to communicate, 3 pins are required to  
 * interface
 * 
 * (***If you are using other Arduino without Hardware SPI 
 * define pins for SCK, SS & MOSI)
 * 
 * Written by Saurabh Palan/iRoboticist  for iRoboticist Workshop.  
 * Twitter: http://twitter.com/iRoboticist
 * Facebook: http://facebook.com/iRoboticist
 * 
 * All text above, and the splash screen must be included in any redistribution
 *********************************************************************/

#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include <Time.h>

Adafruit_SharpMem display(SCK, MOSI, SS);

#define BLACK 0
#define WHITE 1

void setup(void) 
{
  // start & clear the display
  display.begin();
  display.clearDisplay();

  // draw a single pixel // (Pixel Location (x,y), Color)
  display.drawPixel(10, 10, BLACK);
  display.refresh();
  delay(2000);
  display.clearDisplay();

  // draw a single line // (Start point(x,y), End point(x,y), Color)
  display.drawLine(0,0,display.height()-1, display.width()-1, BLACK);
  display.refresh();
  delay(1000);
  display.drawLine(display.width()/2,0,display.width()/2,display.height()/2, BLACK);
  display.refresh();
  delay(2000);
  display.clearDisplay();

  //Draw line Horizontal or Vertical (Different thickness)
  //(Start point(x,y), End point(x,y), Color)
  display.drawLine(20,20,20,60,BLACK); //Horizontal Line
  display.refresh();
  delay(1000);

  display.drawLine(22,60,62,60, BLACK); //Vertical Line
  display.drawLine(22,61,62,61, BLACK); //Vertical Line shifter Horizontally for thickness

  display.refresh();
  delay(2000);
  display.clearDisplay();

  //draw Circle // (Center cordinates (x,y), radius, color)
  display.drawCircle(display.width()/2, display.height()/2, 25, BLACK);
  display.refresh();
  delay(1000);
  display.fillCircle(display.width()/2, display.height()/2, 15, BLACK); //Solid Fill
  display.refresh();
  delay(1000);
  display.clearDisplay();

  //draw Rectangle // (Co-ordinates of Left corner of rectangle (x,y),Width, Height, Color)  
  display.drawRect(10,10,40,40, BLACK);
  display.refresh();
  delay(1000);

  display.fillRect(50, 50, 40, 40, BLACK); //Solid Fill Rectangle
  display.refresh();
  delay(1000);

  display.drawRoundRect(60,10,30,30,5,BLACK); //Rounded Rectangle
  //(Co-ordinates of Left corner of rectangle (x,y),Width, Height,Corner Radius, Color)
  display.refresh();
  delay(1000);

  display.fillRoundRect(10,60,30,30,5,BLACK); //Filled Rounded Rectangle
  //(Co-ordinates of Left corner of rectangle (x,y),Width, Height,Corner Radius, Color)
  display.refresh();
  delay(1000);
  display.clearDisplay();

  //Triangles
  display.drawTriangle(10,10,10,86,86,86,BLACK); //(x1,y1,x2,y2,x3,y3,Color)
  display.refresh();
  delay(1000);
  display.fillTriangle(12,10,86,10,86,84,BLACK); //Solid Fill Tirangle
  display.refresh();
  delay(1000);
  display.clearDisplay();

  //Change Background Color
  display.fillScreen(BLACK);
  display.refresh();
  delay(1000);

  //repeating triangle example to see in inverted display
  display.drawTriangle(10,10,10,86,86,86,WHITE); //(x1,y1,x2,y2,x3,y3,Color)
  display.refresh();
  delay(1000);
  display.fillTriangle(12,10,86,10,86,84,WHITE); //Solid Fill Tirangle
  display.refresh();
  delay(1000);
  display.clearDisplay(); //Clear display will change the background to White 

  //Text & Characters. 
  //Using Alt Code http://www.alt-codes.net/ 
  display.setTextSize(12); //Size of each Character
  display.setTextColor(BLACK); //Color of Text/Character
  display.setCursor(20,5); 
  display.write(2); ///use Alt-Code of the Character
  display.refresh();
  delay(1000);
  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setCursor(20,5); 
  display.setTextSize(5);
  display.write(14); ///use Alt-Code of the Character
  display.println("");

  //Printing Text
  display.setTextSize(1);
  display.println(" Party Time!!");
  display.println(""); //Adding a Line
  display.setTextSize(2);
  display.setTextColor(WHITE, BLACK); // 'inverted' text
  display.print(" ");//Adding space 
  display.println(3282014);  // Print Numbers Directly
  display.refresh();
  delay(1000);

}

void loop(void) 
{
  // Screen must be refreshed at least once per second
  display.refresh();
  delay(500);
}

/*************************************************************************************************************************
 * Some useful resources:
 * 
 * http://arduino.cc  There are pleanty of example cofes & the reference section is handy while coding
 * 
 * http://bildr.org Bildr is an awesome site where they have easy-to-follow articles that help you hit the ground running
 * 
 * http://learn.adafruit.com Adafruit learning is helpful if you are using products from Adafruit 
 * 
 * https://learn.sparkfun.com Sparkfun have great set of tutorials for almost any product suppiled by them 
 *
 **************************************************************************************************************************/

