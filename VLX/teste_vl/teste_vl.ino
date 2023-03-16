/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>

float m=0, x=0;
int i;

VL53L0X sensor;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous(200);
}

void loop()
{
  for(i=0;i<300;i++)
  {
    m=m+(sensor.readRangeContinuousMillimeters());
    if(sensor.timeoutOccurred())
    {
      Serial.print(" TIMEOUT"); 
    }
  }
  x=m/300;
  x=x/10;
  Serial.println(x);
  x=0;
  m=0;
}
