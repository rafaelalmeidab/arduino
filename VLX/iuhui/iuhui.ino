#include <Wire.h> //Import wire library
#include <VL53L0X.h> //Import VL530X library
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
VL53L0X myDistanceSensor;

int i;
float m, x=0;
 
void setup(){
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.print("VL53L0X");
    delay(2000);
    lcd.clear();
    delay(200);
    Serial.println("Initializing continuous....");
    Wire.begin();
    myDistanceSensor.init();
    myDistanceSensor.setTimeout(500);
    myDistanceSensor.startContinuous(200); //Using continuous time mode place inter-measurement period in ms ex: .startContinuous(100)).
}
 
void loop(){
    lcd.clear();
    for(i=0;i<5;i++)
    {
      m=myDistanceSensor.readRangeContinuousMillimeters();
      if(myDistanceSensor.timeoutOccurred())
      {
        Serial.println("TIMEOUT............................");
        Serial.println();
      }
      x=x+m;
    }
    m=x/5;
    m=m/10;
    x=0;
    lcd.print(m);
    delay(5000);
}
