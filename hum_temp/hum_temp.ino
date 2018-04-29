//www.elegoo.com
//2016.06.13

#include <SimpleDHT.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 1;
SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
     
    if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
      Serial.printls("Read DHT11 failed");
      return;
    }
     
    Serial.print((int)temperature); Serial.print(",");
    Serial.println((int)humidity);
    
    // DHT11 sampling rate is 1HZ.
    delay(1000);
}
