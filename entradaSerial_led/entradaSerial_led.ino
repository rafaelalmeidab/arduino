signed int Baudrate = 9600;
int c = 0;
int estado = 0;

void setup() { 
  pinMode(2, OUTPUT);
  // Open serial communications and wait for port to open:
  Serial.begin(Baudrate);// iniciando o serviço de comunicação serial da placa Arduino com baudrate de 9600
  while (!Serial) {
    ; // aguarda a porta serial abrir 
  }

  Serial.write("Serial iniciada");// imprime na tela uma mensagem de aviso
  Serial.println();
  Serial.begin(Baudrate);
  digitalWrite(2, LOW);
}

void loop() { // run over and over
  if (Serial.available()) {
    c = Serial.read();
    Serial.write(c); // verificar o valor recebido
    int x = c - '0' ; // transforma um caracter em int retirando o número 48 decimal
    if(x>0 && x<10){
      piscaled(x);
    }
    digitalWrite(2, LOW);
   }  
}

void piscaled(int x)
{
    for(int k=0;k<x;k++){
        Serial.println();
        digitalWrite(2, HIGH);
        Serial.print("LED ACESSO!");
        Serial.println();
        delay(500);// aguarda 500ms
        digitalWrite(2, LOW);
        Serial.print("LED APAGADO!");
        Serial.println();
        delay(500);// aguarda 500ms
  }
  Serial.println();
}
