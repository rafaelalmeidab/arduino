#include <SPI.h>
#include <Wire.h>
#include <VL53L0X.h>

#define CALIBRATE_DISTANCE_OFFSET                   (0x61)
#define CALIBRATE_SPAD                              (0x75)
#define TEMPERATURE_CALIBRATION                     (0x55)

void mm_to_bytes(uint8_t *bytes, uint16_t mm)
{
    bytes[0] = (mm >> 8 & 0xFF);
    bytes[1] = (mm & 0xFF);
}

void offset_calibration_routine()
{
  delay(500);
  
  /* Calibrate SPADs */
  Wire.beginTransmission(9600);
  Wire.write(CALIBRATE_SPAD);
  Wire.endTransmission();

  delay(1000);

  /* Calibrate Temperature */

  Wire.beginTransmission(9600);
  Wire.write(TEMPERATURE_CALIBRATION);
  Wire.endTransmission();

  delay(1000);

  /* Calibrate Offset */

  uint8_t calib_dist = 100; //In millimeters
  uint8_t dist_bytes[2];
  mm_to_bytes(dist_bytes, calib_dist);
  Wire.beginTransmission(9600);
  Wire.write(CALIBRATE_DISTANCE_OFFSET);
  Wire.write(dist_bytes[0]);
  Wire.write(dist_bytes[1]);
  Wire.endTransmission();

  delay(10000);

  Serial.println("Calibration Complete");
}
