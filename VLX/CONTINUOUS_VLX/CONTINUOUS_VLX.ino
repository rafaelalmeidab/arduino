/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <Adafruit_VL53L0X.h>

float m=0, x=0;
int i; 
const int buzzer = 9;

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup()
{
  Serial.begin(112500);
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

  //sensor.init();
//  sensor.setTimeout(500);

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
//  sensor.startContinuous(250);
}

void loop()
{
    VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
    
  delay(100);

  
  //Serial.println(sensor.readRangeContinuousMillimeters());
  delay(50);
//
  
  
  Serial.println();
}
