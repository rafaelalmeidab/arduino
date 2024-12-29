#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;

// Definição de variáveis globais
const char *ssid = "301";
const char *password = "encaut301";
const char *serverName = "http://10.0.0.167/leitura";
const long interval = 1000;
unsigned long previousMillis = 0;

// Subrotinas
void conectar_WiFi(const char *ssid, const char *password);

void setup(){
    Serial.begin(115200);
    Serial.println("");
    Serial.println("");
    Serial.println("");
    conectar_WiFi(ssid, password);
}

void loop(){
// Check WiFi connection status
    if ((WiFiMulti.run() == WL_CONNECTED)) {
      String leitura = httpGETRequest(serverName);
      Serial.print("Leitura: ");
      Serial.println(leitura);
      // save the last HTTP GET Request
      //previousMillis = currentMillis;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}

void conectar_WiFi(const char *ssid, const char *password){
  Serial.print("Conectando a rede: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //Inicia a conexão WiFi
  int count = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
      delay(500);
      count += 1;
      if (count % 10 == 0)
          Serial.println();
      Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi Conectado");
  Serial.println("Endereço de IP: ");
  Serial.print(WiFi.localIP());
  Serial.println();
}

String httpGETRequest(const char *serverName) {
  WiFiClient client;
  HTTPClient http;
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    //Serial.print("Error code: ");
    //Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
