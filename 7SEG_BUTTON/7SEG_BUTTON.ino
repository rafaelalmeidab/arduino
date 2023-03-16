byte seven_seg_digits[16][7] = { 
 { 0,0,0,0,0,0,1 },  //DIGITO 0
 { 1,0,0,1,1,1,1 },  //DIGITO 1
 { 0,0,1,0,0,1,0 },  //DIGITO 2
 { 0,0,0,0,1,1,0 },  //DIGITO 3
 { 1,0,0,1,1,0,0 },  //DIGITO 4
 { 0,1,0,0,1,0,0 },  //DIGITO 5
 { 0,1,0,0,0,0,0 },  //DIGITO 6
 { 0,0,0,1,1,1,1 },  //DIGITO 7
 { 0,0,0,0,0,0,0 },  //DIGITO 8
 { 0,0,0,1,1,0,0 },  //DIGITO 9
 { 0,0,0,1,0,0,0 },  //DIGITO A
 { 1,1,0,0,0,0,0 },  //DIGITO B
 { 0,1,1,0,0,0,1 },  //DIGITO C
 { 1,0,0,0,0,1,0 },  //DIGITO D
 { 0,1,1,0,0,0,0 },  //DIGITO E
 { 0,1,1,1,0,0,0 }   //DIGITO F
};

const int pBT1=11; 
const int pBT2=12;
String bt1="LOW";
String bt2="LOW";
 
void setup() 
{
  pinMode(pBT1, INPUT_PULLUP);
  pinMode(pBT2, INPUT_PULLUP);
  
  pinMode(2, OUTPUT); //PINO 2 -> SEGMENTO A  
  pinMode(3, OUTPUT); //PINO 3 -> SEGMENTO B
  pinMode(4, OUTPUT); //PINO 4 -> SEGMENTO C
  pinMode(5, OUTPUT); //PINO 5 -> SEGMENTO D
  pinMode(6, OUTPUT); //PINO 6 -> SEGMENTO E
  pinMode(7, OUTPUT); //PINO 7 -> SEGMENTO F
  pinMode(8, OUTPUT); //PINO 8 -> SEGMENTO G
  pinMode(9, OUTPUT); //PINO 9 -> SEGMENTO PONTO
  ligaPonto(0);
}

void ligaPonto(byte dot)
{
  digitalWrite(9, dot);
}
void ligaSegmentosDisplay(byte digit)
{
  byte pino = 2;
  for (byte contadorSegmentos = 0; contadorSegmentos < 7; ++contadorSegmentos)
  { 
    digitalWrite(pino, seven_seg_digits[digit][contadorSegmentos]); //PERCORRE O ARRAY E LIGA OS
    ++pino;
    break;
  }
  ligaPonto(1);
  delay(100); 
  ligaPonto(0);
}

//MÉTODO RESPONSÁVEL PELA CONTAGEM DE 0 A 9 E CONTAGEM DE "A" ATÉ "F" (NA CONTAGEM HEXADECIMAL "A"=10
// "B"=11 / "C"=12 / "D"=13 / "E"=14 / "F"=15)
void loop()
{
   if(digitalRead(pBT1&&pBT2)==0)
   {
    bt1="HIGH";
    bt2="HIGH";
    if(bt1&&bt2=="HIGH")
    {
      do
      {
        if(digitalRead(pBT1)==0)
        {
          for (byte contador=9;contador<16; contador++)
          {
            delay(500);
            ligaSegmentosDisplay(contador);
            break;
          }
        }
        else
        {
        
        }
      }while(digitalRead(pBT1&&pBT2)==0);
      bt1="LOW";
      bt2="LOW";
    }
  }
  
  if(digitalRead(pBT1&&pBT2)==1)
  {
    bt1="LOW";
    bt2="LOW";
    if(bt1&&bt2=="LOW")
    {
      do
      {
        if(digitalRead(pBT1)==0)
        {
          for (byte contador=0;contador<9; contador++)
          {
            delay(500);
            ligaSegmentosDisplay(contador);
            break;
          }
        }
        else
        {
        
        }
      }while(digitalRead(pBT1&&pBT2)==0);
      bt1="HIGH";
      bt2="HIGH";
    }
  }
}
