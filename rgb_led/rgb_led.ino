#include <SoftwareSerial.h>

int LED = 2;
int botao = 3;
signed int Baudrate = 9600;

int red_light_pin= 6;
int green_light_pin = 7;
int blue_light_pin = 8;

void setup() { 
  // Open serial communications and wait for port to open:
  pinMode(LED, OUTPUT);
  pinMode(botao, INPUT_PULLUP);
  Serial.begin(Baudrate);// iniciando o serviço de comunicação serial da placa Arduino com baudrate de 9600
  while (!Serial) {
    ; // aguarda a porta serial abrir 
  }
  digitalWrite(LED, HIGH);
  delay(2000);
  digitalWrite(LED, LOW);

  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}

void loop() { 
  /*
  if (Serial.available()>0) {      
    Serial.write(Serial.read());
    int num = Serial.parseInt();   
    int x=0;  
    
    if(num>0 && num<10){
         /*
      do{
        digitalWrite(LED, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
        delay(500);
        x++;
      }while(x<num);
      

      for(x=0; x<num; x++){
        digitalWrite(LED, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
        delay(500); 
      }
    }
  } 
  */
  delay(500);
  Serial.write("Green");
  RGB_color(0, 255, 0); // Green
  delay(500);
  RGB_color(0, 0, 255); // Blue
  delay(500);
  RGB_color(255, 255, 125); // Raspberry
  delay(500);
  RGB_color(0, 255, 255); // Cyan
  delay(500);
  RGB_color(255, 0, 255); // Magenta
  delay(500);
  RGB_color(255, 255, 0); // Yellow
  delay(500);
  RGB_color(255, 255, 255); // White
  delay(500);
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
