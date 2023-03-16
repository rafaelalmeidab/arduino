int ledPin = 5;     // LED conectado ao pino digital 9
int analogPin = A3;  // potenciômetro conectado ao pino analógico 3
int val = 0;        // variável para guradar o valor lido

void setup() {
  Serial.begin(9600);
  pinMode(analogPin, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(ledPin, OUTPUT);  // configura  o pino como saída
  
  Serial.begin(9600);
  digitalWrite(ledPin, LOW); //LED INICIA DESLIGADO
  
  delay(2000);

 

}

void loop() 
{
  val = map(analogRead(analogPin), 0, 1023, 0, 255);
  Serial.println(val);
  analogWrite(ledPin, val); // analogRead retorna valores de 0 a 1023, analogWrite recebe de 0 a 255
  delay(50);
}
