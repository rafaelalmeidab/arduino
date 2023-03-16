/*#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int pinoBotao = 3; //PINO DIGITAL UTILIZADO PELO PUSH BUTTON
const int pinoLed =2; //PINO DIGITAL UTILIZADO PELO LED7
int cont=0;
String ans;
 
void setup() 
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.print("TESTE");
  delay(2000);
  lcd.clear();
  pinMode(pinoBotao, INPUT_PULLUP); //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
  //DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)  
  pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoLed, LOW); //LED INICIA DESLIGADO
}
void loop(){
  lcd.clear();
  if(digitalRead(pinoBotao)==0)//QUANDO FOR PRESSIONADO
  {
    cont++;
    delay(250); 
  }
  else
  {
    
  }  
  if(cont%2==0)
  {
    lcd.print("LED LIGADO");
    digitalWrite(pinoLed, HIGH);
  }
  else
  {    
    lcd.print("LED DESLIGADO");
    digitalWrite(pinoLed, LOW);
  }
  delay(50);

}
*/

const int VERM=10,VERDE=4, AMARELO=7, BT=3;
int I=0;
void setup() 
{
  Serial.begin(9600);
  pinMode(BT, INPUT_PULLUP); //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
  pinMode(VERM, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(VERDE, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(AMARELO, OUTPUT); //DEFINE O PINO COMO SAÍDA
}

void loop()
{
  if(digitalRead(BT)==0)
  {
    delay(300);
    if(I==0)
    {
      digitalWrite(AMARELO, LOW);
      digitalWrite(VERM, HIGH);
    }
    if(I==1)
    {
      digitalWrite(VERM, LOW);
      digitalWrite(VERDE, HIGH);
    }
    if(I==2)
    {
      digitalWrite(VERDE, LOW);
      digitalWrite(AMARELO, HIGH);
      I=-1;
    }
    I++;
  }
  else
  {
    
  }
}
