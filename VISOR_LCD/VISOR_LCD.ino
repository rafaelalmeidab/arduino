#include <LiquidCrystal.h>

int v=2;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() 
{
  pinMode(v, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  // Print a message to the LCD.
  lcd.print("Podcast Nano");
}

void loop()
{
  digitalWrite(v, HIGH);
  delay(1500);
  digitalWrite(v, LOW);
  delay(1500);
  
}
