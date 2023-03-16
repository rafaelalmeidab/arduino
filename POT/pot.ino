int sensorPin = A3;    // select the input pin for the potentiometer
int ledPin = 2;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int valor = 0;
int sensorMin = 1023;
int sensorMax = 0;
void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
 
}

void loop() {
 //5V / 1024 = 1 unidade vale 4,888mV /*
  sensorValue = map(analogRead(sensorPin), 1023, 0, 0, 255);
  //sensorValue = analogRead(sensorPin); // 0 ATE 1023
  valor =sensorValue/4;
  Serial.println("sensor");
  Serial.println(sensorValue);
  analogWrite(ledPin,sensorValue); //255
  Serial.println(analogRead(sensorPin));
  delay(100);
 }
