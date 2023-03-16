#include <SoftwareSerial.h>

int LED = 2;
int botao = 3;
signed int Baudrate = 9600;

void setup() { 
  // Open serial communications and wait for port to open:
  pinMode(LED, OUTPUT);
  pinMode(botao, INPUT_PULLUP);
  Serial.begin(Baudrate);// iniciando o serviço de comunicação serial da placa Arduino com baudrate de 9600
  while (!Serial) {
    ; // aguarda a porta serial abrir 
  }
}

void loop() { 
  if (Serial.available()>0) {      
    Serial.write(Serial.read());
    int num = Serial.parseInt();   
    int x=0;  
    
    if(num>0 && num<10){
         /*
      do{
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        delay(1000);
        x++;
      }while(x<num);
      */

      for(x=0; x<num; x++){
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        delay(1000); 
      }
    }
  } 
}
