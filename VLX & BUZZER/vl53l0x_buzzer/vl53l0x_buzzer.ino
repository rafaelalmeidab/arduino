#include "Adafruit_VL53L0X.h"
const int buzzer = 9;
#include <Wire.h>
//A4 - SDA
//A5 - SCL
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
float x=0;

void setup() {
  Serial.begin(115200);
    Wire.begin();
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    x=measure.RangeMilliMeter;
    x=x/10;
    
    if(x<80)
    {
      tone(buzzer, 100); // Send 1KHz sound signal...
      delay(100);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(100);        // ...for 1sec
    }
    
    Serial.print("Distance (cm): "); 
    Serial.println(x);
  } else {
    Serial.println(" out of range ");
  }
    
  delay(15);
}
