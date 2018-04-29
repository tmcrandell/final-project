/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include <SimpleDHT.h>
#include <string.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int pinDHT11 = 7;
SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600); //begin serial
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
}

void loop(){
     
  char in=Serial.read();
  if(in=='a')
  {
     // read with raw sample data.
    byte temperature = 0;
    byte humidity = 0;
           
    if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) 
    {
      Serial.print("Read DHT11 failed");
      return;
    }
           
    Serial.print((int)temperature); Serial.print(",");
    Serial.println((int)humidity);
          
    // DHT11 sampling rate is 1HZ.
    delay(1000); 
  }
  else if(in=='b')
  {
    lcd.clear();
    lcd.setCursor(0,0);
    char name[8]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    char message[15]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    char temp=NULL;
        
    for(int i=0; i<8; i++)
    {
      temp=Serial.read();
      if(temp!=';')
      {
        name[i]=temp;
      }
      else
      {
        break;
      }
    }
    
    for(int j=0; j<15; j++)
    {
      temp=Serial.read();
      if(temp!=':')
      {
        message[j]=temp;
      }
      else
      {
        break;
      }
    }
           
    lcd.print(name);
    lcd.print(" cheeps:");
    lcd.setCursor(0,1);
    lcd.print(message);
    }
}


