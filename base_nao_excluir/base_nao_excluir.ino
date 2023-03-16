// Autor: Rafael Almeida Borges da Silva

#include <Adafruit_Sensor.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <ESPAsyncWebServer.h>
#include <esp_system.h>
#include <FS.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <OneWire.h>
#include <SD.h>
#include <SPI.h>
#include <sys/time.h>
#include <time.h>
#include <WiFi.h>

//PINOS MICRO_SD
#define SD_CS 5
#define SD_CLK 18
#define SD_MISO 19
#define SD_MOSI 23

#define DHTPIN 15
#define DHTTYPE DHT11
#define oneWireBus 4

const char* ssid = "FresCow 2.0";
const char* senha_rede = "cacique97";

char data_formatada[64];
int i=1,f=0,j=0, LED_AZUL=33, LED_AMARELO=26, LED_VERDE=14, LED_VERMELHO=13, control=0;
float h = 0, t=0, ds18b20_temp = 0, temp_ant = 0, umi_ant = 0;
String umi, temp, prod, litros, dataMessage, dataMessage_litros, hora_unix, inString="", currentLine; 
struct tm data_D;
unsigned long hora=0;

IPAddress ip(192, 168, 0, 91);
IPAddress gateway(192, 168, 0, 2);
IPAddress subnet(255, 255, 255, 0);

DHT dht(DHTPIN, DHTTYPE);
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

WiFiServer server(80);
void IniciaSD()
{
  //Inicializando MicroSD
  SD.begin(SD_CS);
  if (!SD.begin(SD_CS))
  {
    Serial.println("Montagem do cartão falhou");
    return;
  }
  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE)
  {
    Serial.println("Não há um cartão SD inserido");
    return;
  }
  Serial.println("Inicializando o cartão SD...");
  if (!SD.begin(SD_CS))
  {
    Serial.println("ERRO - Inicialização do cartão SD falhou!");
    return; //Falha na inicialização do cartão
  }
  //Se o arquivo txt não existe, um novo arquivo é criado no cartão
  File file = SD.open("/Temperatura_e_Umidade.txt");
  if (!file)
  {
    Serial.println("Arquivo não existe");
    Serial.println("Criando arquivo...");
    writeFile(SD, "/Temperatura_e_Umidade.txt", "Temperatura e Umidade\r\n");
  }
  else
  {
    Serial.println("Arquivo já existe");
  }
  file.close();

  File file1 = SD.open("/Producao.txt");
  if (!file1)
  {
    Serial.println("Arquivo não existe");
    Serial.println("Criando arquivo...");
    writeFile(SD, "/Producao.txt", "Producao\r\n");
  }
  else
  {
    Serial.println("Arquivo já existe");
  }
  file1.close();
}

void erro_SD()
{
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AZUL, LOW);
    digitalWrite(LED_AMARELO, LOW);
    Serial.println("Falha ao abrir arquivo para escrita");
    digitalWrite(LED_AZUL, HIGH);
    digitalWrite(LED_AMARELO, HIGH);
    delay(250);
    digitalWrite(LED_AZUL, LOW);
    digitalWrite(LED_AMARELO, LOW);
    delay(250);
    digitalWrite(LED_AZUL, HIGH);
    digitalWrite(LED_AMARELO, HIGH);
    delay(250);
    digitalWrite(LED_AZUL, LOW);
    digitalWrite(LED_AMARELO, LOW);
    delay(250);
    digitalWrite(LED_AZUL, HIGH);
    digitalWrite(LED_AMARELO, HIGH);
    delay(250);
    digitalWrite(LED_AZUL, LOW);
    digitalWrite(LED_AMARELO, LOW);
    delay(250);
    digitalWrite(LED_AZUL, HIGH);
    digitalWrite(LED_AMARELO, HIGH);
    delay(250);
    digitalWrite(LED_AZUL, LOW);
    digitalWrite(LED_AMARELO, LOW);  
}

void Hora_Atual()
{
  digitalWrite(LED_VERMELHO, HIGH);
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_AMARELO, HIGH);
  digitalWrite(LED_AZUL, HIGH);
  
  do
  {
    WiFiClient client = server.available();
    if (client)
    {
      Serial.println("Novo Client - Atualização Hora do Sistema");
      String currentLine = "";
      while (client.connected())
      {
        if (client.available())
        {
          //client.println("hr");
          char c = client.read();
          Serial.write(c);
          if (c == '\n') //linha completa
          {
            if(currentLine.indexOf("GET /")!= -1)//ler parametro
            {
              Serial.println("CL:");
              Serial.println(currentLine);   
              i = currentLine.indexOf("GET /");
              f = currentLine.indexOf(" ", 5);
              hora_unix = currentLine.substring(i + 5, f);
              if (hora_unix.length())
              {
                Serial.println("Hora unix:");
                hora_unix.remove(0,33);
                hora_unix.remove(10, hora_unix.length());
                hora=hora_unix.toInt();
                hora=hora-(3*3600);
                Serial.println(hora);
                control=1;
                client.stop();
                Serial.println("Client desconectado.");
              }
            }
            if (currentLine.length() == 0)//final do cabeçalho
            {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
            }
            else
            {
              currentLine = "";
            }
          }
          else if (c != '\r')
          {
            currentLine += c;
          }
        }
      }
    } 
    
  }while(control==0);

}

void getReadings() //Leitura dos sensores
{
  sensors.requestTemperatures();
  ds18b20_temp = sensors.getTempCByIndex(0);
  h = dht.readHumidity();
  if (ds18b20_temp > 32)
  {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  }
  if (ds18b20_temp <= 32)
  {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_VERDE, HIGH);
  }
  if (isnan(ds18b20_temp) || isnan(h) || isnan(ds18b20_temp) && isnan(h) || ds18b20_temp < -5)
  {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    delay(500);
    digitalWrite(LED_AMARELO, LOW);
    delay(500);
    digitalWrite(LED_AMARELO, HIGH);
    delay(500);
    digitalWrite(LED_AMARELO, LOW);
    delay(500);
  }
  Serial.print("Temperatura: " + String(ds18b20_temp) + " Umidade: " + String(h) + "\n");
}

void logSDCard() //Aloca dados no MicroSD
{
  time_t tt = time(NULL);//Obtem o tempo atual em segundos. Utilize isso sempre que precisar obter o tempo atual
  data_D = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura
  strftime(data_formatada, 64, "'%Y/%m/%d', '%H:%M:%S'", &data_D);//Cria uma String formatada da estrutura "data"
  dataMessage="INSERT INTO registro VALUES("+String(ds18b20_temp)+","+String(h)+","+data_formatada+");"+"\r\n";
  Serial.println(dataMessage);
  appendFile(SD, "/Temperatura_e_Umidade.txt", dataMessage.c_str());
}

// Escreve dados ao cartão MicroSD (NÃO MODIFICAR ESSA FUNÇÃO)
void writeFile(fs::FS &fs, const char * path, const char * message) //Acesso ao MicroSD para acesso e registro de pastas
{
  Serial.printf("Writing file: %s\n", path);
  File file = fs.open(path, FILE_APPEND);

  if (!file)
  {
    erro_SD();
    return;
  }
  if (file.print(message))
  {
    Serial.println("Arquivo escrito");
  }
  else
  {
    erro_SD();
  }
  file.close();
}

// Acrescenta dados ao cartão MicroSD (NÃO MODIFICAR ESSA FUNÇÃO)
void appendFile(fs::FS &fs, const char * path, const char * message) 
{
  Serial.printf("Appending to file: %s\n", path);
  File file = fs.open(path, FILE_APPEND);
  if (!file)
  {
    erro_SD();
    return;
  }
  if (file.print(message)) 
  {
    digitalWrite(LED_AZUL, HIGH);
    delay(100);
    digitalWrite(LED_AZUL, LOW);
    Serial.println("Mensagem acrescentada ao MicroSD");
  }
  else 
  {
    erro_SD();
  }
  file.close();
}

unsigned long t_log;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  sensors.begin();
  dht.begin();
  delay(100);
  Serial.println();
  Serial.println();
  Serial.print("Conectando à ");
  Serial.println(ssid);

  WiFi.begin(ssid, senha_rede);
  WiFi.config(ip, gateway, subnet);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  digitalWrite(LED_VERMELHO, HIGH);
  delay(100);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, HIGH);
  delay(100);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, HIGH);
  delay(100);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_AZUL, HIGH);
  delay(100);
  digitalWrite(LED_AZUL, LOW);
  
  Serial.println("WiFi conectado.");
  Serial.println("Endereço de IP: ");
  delay(2000);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  Serial.println(ip);
  server.begin();
  
  timeval tv;//Cria a estrutura temporaria para funcao abaixo.
  Hora_Atual();  //Atualizando a hora do sistema por meio da hora do celular que estiver conectado na rede
  
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_AZUL, LOW);
  Serial.println("Passou depois\n");
  tv.tv_sec = hora;//Atribui minha data e hora atual
  settimeofday(&tv, NULL);//Configura o RTC para manter a data atribuida atualizada.
  IniciaSD();
}

void loop()
{
  IniciaSD();
  WiFiClient client = server.available();
  if (client)
  {
    Serial.println("Novo Client.");
    String currentLine = "";
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') //linha completa
        {

          if (currentLine.indexOf("GET /") != -1)//leitura parâmetro
          {
            i = currentLine.indexOf("GET /");
            f = currentLine.indexOf(" ", 5);
            litros = currentLine.substring(i + 5, f);
            if (litros.length()&&litros.length()<22)
            {
              time_t tt = time(NULL);//Obtem o tempo atual em segundos
              data_D = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura
              strftime(data_formatada, 64, "'%Y/%m/%d', '%H:%M:%S'", &data_D);//Cria uma String formatada da estrutura "data"
              Serial.println("Producao de leite diaria = " + litros + " litros");
              dataMessage_litros = "INSERT INTO registro_prod VALUES("+String(litros)+","+data_formatada+");"+"\r\n";
              Serial.println(dataMessage_litros);
              appendFile(SD, "/Producao.txt", dataMessage_litros.c_str());
              digitalWrite(LED_AZUL, HIGH);
              delay(100);
              digitalWrite(LED_AZUL, LOW);
            }
          }

          if (currentLine.length() == 0)//final do cabeçalho
          {
            delay(2100);
            getReadings();
            if (isnan(ds18b20_temp) || isnan(h) || isnan(ds18b20_temp) && isnan(h) || ds18b20_temp < -5)
            {
              Serial.println("Nan - Nada registrado no MicroSD\n");
            }
            else
            {
              if (temp_ant == ds18b20_temp && umi_ant == h)
              {

              }
              else
              {
                logSDCard();
              }
            }
            temp = (String)ds18b20_temp;
            umi = (String)h;

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print(temp + "/");
            client.println(umi);
            client.println();
            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("Client desconectado.");
  }
  else
  {
    delay(2100);
    getReadings();
    if (isnan(ds18b20_temp) || isnan(h) || isnan(ds18b20_temp) && isnan(h) || ds18b20_temp < -5)
    {
      Serial.println("Nan - Nada registrado no MicroSD\n");
    }
    else
    {
      if (temp_ant == ds18b20_temp && umi_ant == h)
      {
        
      }
      else
      {
        logSDCard();
      }
    }
  }
  temp_ant = ds18b20_temp;
  umi_ant = h;
}
