#include<LiquidCrystal.h>
LiquidCrystal lcd(9,8,7,6,5,4);
char BYTE;
int buttonR = 11;
int buttonL = 10;
int droite =0;
int gauche =0;
void setup() 
{
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  pinMode(buttonR, INPUT_PULLUP);
  pinMode(buttonL, INPUT_PULLUP);
  lcd.begin(16,2);
  lcd.setCursor(1,0);
  // lcd.blink();
  lcd.print("Hsan El Kayla");
}

void loop() 
{
  droite = digitalRead(buttonR);
  gauche = digitalRead(buttonL);
  if(droite==0 && gauche!=0)
  {
    Serial.println(0);
    Serial.println("movement right ");
    digitalWrite(13,HIGH);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Hsan El Kayla");
    lcd.setCursor(1,1);
    lcd.print("moving right");
    delay(500);
    digitalWrite(13,LOW);
    Serial.println(-1);
   }
  else if(gauche==0 && droite!=0)
  {
    Serial.println(1);
    Serial.println("movement left");
    digitalWrite(12,HIGH);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Hsan El Kayla");
    lcd.setCursor(1,1);
    lcd.print("moving left");
    delay(500);
    digitalWrite(12,LOW);
    Serial.println(-1);
  }
  else if(droite==0 && gauche==0)
  {
    Serial.println(3);
    Serial.println("jump");
    digitalWrite(13,HIGH);
    digitalWrite(12,HIGH);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Hsan El Kayla");
    lcd.setCursor(1,1);
    lcd.print("jumping");
    delay(500);
    digitalWrite(13,LOW);
    digitalWrite(12,LOW);
    Serial.println(-1);
  }
  else
  {
    Serial.println("not moving");
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Hsan El Kayla");
    delay(500);
  }
  if(Serial.available()>0)
  {
    BYTE=Serial.read();
    if(BYTE=='1')
    {
      digitalWrite(12,HIGH);
      digitalWrite(13,LOW);
      Serial.println("collision droite\n");
    }
    else if(BYTE=='2')
    {
      digitalWrite(13,HIGH);
      digitalWrite(12,LOW);
      Serial.println("collision gauche\n");
    }
    else 
    {
      digitalWrite(12,LOW);
      digitalWrite(13,LOW);
      //Serial.write(0);
      Serial.println("pas de collision \n");
    }
  }
}
