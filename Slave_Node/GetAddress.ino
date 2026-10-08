#include <SoftwareSerial.h>

SoftwareSerial BT(10,11);

void setup()
{
  Serial.begin(9600);
  BT.begin(38400);

  Serial.println("Ready");
}

void loop()
{
  if (BT.available())
  {
    Serial.write(BT.read());
  }

  if (Serial.available())
  {
    BT.write(Serial.read());
  }
}
