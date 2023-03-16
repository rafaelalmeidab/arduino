#include <Adafruit_Sensor.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN2 5
#define DHTPIN3 19
#define DHTPIN4 23
#define DHTTYPE DHT11

String t2, h2, t3, h3, t4, h4;


DHT dht2 (DHTPIN2, DHTTYPE);
DHT dht3 (DHTPIN3, DHTTYPE);
DHT dht4 (DHTPIN4, DHTTYPE);

void setup() {
  
  Serial.begin(115200);
  dht2.begin();
  dht3.begin();
  dht4.begin();
  
  delay(100);
}

void loop() {
  
  h2=dht2.readHumidity();
  t2=dht2.readTemperature();
  Serial.print("DHT2: "+h2+"/"+t2);
  Serial.println();
  h3=dht3.readHumidity();
  t3=dht3.readTemperature();
  Serial.print("DHT3: "+h3+"/"+t3);
  Serial.println();
  h4=dht4.readHumidity();
  t4=dht4.readTemperature();
  Serial.print("DHT4: "+h4+"/"+t4);
  Serial.println();
  Serial.println();
  delay(2000);
  
}
