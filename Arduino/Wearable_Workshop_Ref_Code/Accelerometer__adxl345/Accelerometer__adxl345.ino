/*********************************************************************
iRoboticist Workshops: http://Workshop.iRoboticist.com

This is an example sketch of using Accelerometer ADXL345 with LCD Display

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
/*Acclerometer 
Accelerometer measures acceleration :)
How fast something is speeding up or slowing down. You’ll see acceleration displayed either in 
units of meters per second squared (m/s2), or G-force (g), which is about 9.8m/s2 
(the exact value depends on your elevation and the mass of the planet you’re on)

Accelerometers are used to sense both static (e.g. gravity) and dynamic (e.g. sudden starts/stops) acceleration. 
One of the more widely used applications for accelerometers is tilt-sensing. Because they are affected by the 
acceleration of gravity, an accelerometer can tell you how it’s oriented with respect to the Earth’s surface. 

Characteristics of accelerometer:

*Range - The upper and lower limits of what the accelerometer can measure is also known as its range. 
In most cases, a smaller full-scale range means a more sensitive output; so you can get a more precise 
reading out of an accelerometer with a low full-scale range.

You want to select a sensing range that will best fit your project, if your project will only be subjected 
to accelerations between +2g and -2g, a ±250g-ranged accelerometer won’t give you much, if any, precision. 

*Interface - This is another one of the more important specifications. Accelerometers will have either an analog,
pulse-width modulated (PWM), or digital interface. 

*Number of axes measured - This one’s very straightforward: out of the three axes possible (x, y, and z), how many 
can the accelerometer sense? Three-axis accelerometers are usually the way to go; they are the most common and 
they are really no more expensive than equivalently sensitive one or two axis accelerometers.

*Power Usage - If your project is battery powered, you might want to consider how much power the accelerometer will 
consume. The required current consumption will usually be in the 100s of µA range. Some sensors also feature sleep 
functionality to conserve energy when the accelerometer isn’t needed.

*Bonus Features - Many more recently developed accelerometers may have a few nifty features, beyond just producing 
acceleration data. These newer accelerometers may include features like selectable measurement ranges, 
sleep control, 0-g detection, and tap sensing.

http://en.wikipedia.org/wiki/Accelerometer
http://en.wikipedia.org/wiki/G-force

*/

/*ADXL345 http://www.analog.com/en/mems-sensors/mems-inertial-sensors/adxl345/products/product.html
The sensor has three axes of measurements, X Y Z, and pins that can be used either as I2C or SPI digital interfacing.
You can set the sensitivity level to either +-2g, +-4g, +-8g or +-16g. 
The lower range gives more resolution for slow movements, the higher range is good for high speed tracking. 
The ADXL345 is the latest and greatest from Analog Devices, known for their exceptional quality MEMS devices. 
The VCC takes up to 5V in and regulates it to 3.3V with an output pin. 
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>

// Assign a unique ID to this sensor at the same time 

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

/*'sensorID' is a device identifier. It will be returned in the sensor_event in each call to getEvent(). 
The sensorID has no effect on the operation of the driver or device, 
but is useful in managing sensor events in systems with multiple sensors.*/

Adafruit_SharpMem display(SCK, MOSI, SS);

#define BLACK 0
#define WHITE 1

void setup(void) 
{
  display.begin();
  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("  Acclrmtr Test"); 
    
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    display.println("Oops, no ADXL345 detected. Check your wiring!");
    display.refresh();
    delay(5000);
    while(1);
  }
  

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_2_G);
  /* displaySetRange(ADXL345_RANGE_8_G);
     displaySetRange(ADXL345_RANGE_4_G);
     displaySetRange(ADXL345_RANGE_16_G); */
  
  /* Display some basic information on this sensor */
  displaySensorDetails_adxl();
  display.refresh();
  delay(5000);
  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setCursor(0,10);
  display.setTextSize(1);
  
  /* Display additional settings (outside the scope of sensor_t) */
  displayDataRate();    
  displayRange();
  display.refresh();
  delay(2000);
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  
  accel.getEvent(&event);
  
  /* Display the results (acceleration is measured in m/s^2) */
  
  display.fillScreen(BLACK);
  display.setTextColor(WHITE);
  display.setCursor(0,15);
  display.setTextSize(1);
  display.print (" G: 9.81"); display.print(" m/s"); display.write (252); display.println(""); display.println("");
  display.print(" X: "); display.print(event.acceleration.x); display.print(" m/s"); display.write (252); display.println("");
  display.print(" Y: "); display.print(event.acceleration.y); display.print(" m/s"); display.write (252); display.println("");
  display.print(" Z: "); display.print(event.acceleration.z); display.print(" m/s"); display.write (252); display.println("");
  display.refresh();
  delay(100);
  
}

void displaySensorDetails_adxl(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  
  display.print   ("Sensor: ");     display.println(sensor.name);
  display.print   ("Driver V.: ");  display.println(sensor.version);
  display.print   ("Unique ID: ");  display.println(sensor.sensor_id);
  display.println ("Max Value: ");  display.print(sensor.max_value);   display.print(" m/s"); display.write (252); display.println("");
  display.println ("Min Value: ");  display.print(sensor.min_value);   display.print(" m/s"); display.write (252); display.println("");
  display.println ("Resolution: "); display.print(sensor.resolution);  display.print(" m/s"); display.write (252); display.println("");  
  
  delay(500);
}


void displayDataRate(void)
{
  display.print ("Data Rate:");      //The setDataRate() function sets the rate at which the sensor output                                
  switch(accel.getDataRate())        //is updated. Rates above 100 Hz will exhibit increased noise.                                   
  {                                  //Rates below 6.25 Hz will be more sensitive to temperature variations. 
    case ADXL345_DATARATE_3200_HZ:
      display.print  ("3200"); 
      break;
    case ADXL345_DATARATE_1600_HZ:
      display.print  ("1600"); 
      break;
    case ADXL345_DATARATE_800_HZ:
      display.print  ("800"); 
      break;
    case ADXL345_DATARATE_400_HZ:
      display.print  ("400"); 
      break;
    case ADXL345_DATARATE_200_HZ:
      display.print  ("200"); 
      break;
    case ADXL345_DATARATE_100_HZ:
      display.print  ("100"); 
      break;
    case ADXL345_DATARATE_50_HZ:
      display.print  ("50"); 
      break;
    case ADXL345_DATARATE_25_HZ:
      display.print  ("25"); 
      break;
    case ADXL345_DATARATE_12_5_HZ:
      display.print  ("12.5"); 
      break;
    case ADXL345_DATARATE_6_25HZ:
      display.print  ("6.25"); 
      break;
    case ADXL345_DATARATE_3_13_HZ:
      display.print  ("3.13"); 
      break;
    case ADXL345_DATARATE_1_56_HZ:
      display.print  ("1.56"); 
      break;
    case ADXL345_DATARATE_0_78_HZ:
      display.print  ("0.78"); 
      break;
    case ADXL345_DATARATE_0_39_HZ:
      display.print  ("0.39"); 
      break;
    case ADXL345_DATARATE_0_20_HZ:
      display.print  ("0.20"); 
      break;
    case ADXL345_DATARATE_0_10_HZ:
      display.print  ("0.10"); 
      break;
    default:
      display.print  ("????"); 
      break;
  }  
  display.println(" Hz");  
}


/*sets the operating range for the sensor. 
Higher values will have a wider measurement range. 
Lower values will have more sensitivity.*/

void displayRange(void)            
                                   
{
  display.print ("Range:+/- "); 
  
  switch(accel.getRange())
  {
    case ADXL345_RANGE_16_G:
      display.print  ("16 "); 
      break;
    case ADXL345_RANGE_8_G:
      display.print  ("8 "); 
      break;
    case ADXL345_RANGE_4_G:
      display.print  ("4 "); 
      break;
    case ADXL345_RANGE_2_G:
      display.print  ("2 "); 
      break;
    default:
      display.print  ("?? "); 
      break;
  }  
  display.println("g");  
}

/*********************************************************************
Some useful resources:

  http://arduino.cc  There are pleanty of example cofes & the reference section is handy while coding
  
  http://bildr.org Bildr is an awesome site where they have easy-to-follow articles that help you hit the ground running

  http://learn.adafruit.com Adafruit learning is helpful if you are using products from Adafruit like the ADXL345 :)

  https://learn.sparkfun.com Sparkfun have great set of tutorials for almost any product suppiled by them.
  *********************************************************************/
