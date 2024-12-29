#include <Wire.h> //Import wire library
#include <VL53L0X.h> //Import VL530X library
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
VL53L0X sensor;

int i;
float m=0, x=0;
 
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("VL53yftydL0X");
  delay(2000);
  lcd.clear();
  delay(200);
  Serial.println("Initializing continuous....");
  Wire.begin();
}
 
void loop()
{
  lcd.print("VISOR OK");
  delay(2000);
  lcd.clear();
  /*for(i=0;i<10;i++)
  {
    m=m+(sensor.readRangeContinuousMillimeters());
    if(sensor.timeoutOccurred())
    {
      Serial.print("TIMEOUT"); 
    }
  }
  x=m/10;
  x=x/10;
  lcd.clear();
  Serial.println(x);
  lcd.print(x);
  x=0;
  m=0;
  delay(2000);
  */
}
