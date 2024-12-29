
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

/////////////////////////////////////////////////////////////////////////////////////
// Definição de variáveis globais ///////////////////////////////////////////////////
const char *ssid = "301";
const char *password = "encaut301";
AsyncWebServer server(80); // Definindo o servidor assíncrono HTTP na porta 80
const long interval = 1000;
int aux = 0;
/////////////////////////////////////////////////////////////////////////////////////
// Subrotinas ///////////////////////////////////////////////////////////////////////
void conectar_WiFi(const char *ssid, const char *password);
/////////////////////////////////////////////////////////////////////////////////////
// criação da página Web ////////////////////////////////////////////////////////////
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .my-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>ESP32 Server</h2>
  <p>
    <span class="my-labels">Leitura</span> 
    <span id="leitura">%LEITURA%</span>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("leitura").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/leitura", true);
  xhttp.send();
}, 1000 ) ;
</script>
</html>)rawliteral";

// Replaces placeholder with values
String processor(const String &var) {
  //Serial.println(var);
  if (var == "LEITURA") return read_function();
  return String();
}

void setup(){
  Serial.begin(115200);
  Serial.println("");
  Serial.println("");
  Serial.println("");
  conectar_WiFi(ssid, password);
}
void loop() {
}

void conectar_WiFi(const char *ssid, const char *password){
  Serial.print("Conectando a rede: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //Inicia a conexão WiFi
  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
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

  // Route for root / web page
  //server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    //request->send_P(200, "text/html", index_html, processor);
  //});
  server.on("/leitura", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", read_function().c_str());
  });
  server.begin(); // inicializando o servidor
  Serial.println("Servidor inicializado");
}

String read_function() {
  aux += 1;
  Serial.println(aux);
  return String(aux);
}
