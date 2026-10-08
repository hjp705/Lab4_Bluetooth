#include <SoftwareSerial.h>
// student B

SoftwareSerial BT(10,11);

const int ledPin = 8;
const int potPin = A0;

void setup()
{
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  BT.begin(9600);
}

void loop()
{
  // ===== 接收 A 的按鈕 =====
  if(BT.available())
  {
    char cmd = BT.read();
    //Serial.println(cmd);

    if(cmd == 'H')
      digitalWrite(ledPin,HIGH);

    if(cmd == 'L')
      digitalWrite(ledPin,LOW);
  }

  // ===== 傳送可變電阻 =====
  int value = analogRead(potPin);

  value = map(value,0,1023,0,255);

  BT.write(value);
  Serial.println(value);

  delay(100);
}
