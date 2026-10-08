#include <SoftwareSerial.h>

// RX 接 HC-05 TXD, TX 接 HC-05 RXD
SoftwareSerial BTSerial(10, 11);

void setup() {
  Serial.begin(9600);    // 電腦端的 Serial Monitor 鮑率
  BTSerial.begin(38400); // HC-05 AT 模式預設固定為 38400
  Serial.println("AT Command Mode Ready. Enter AT commands:");
}

void loop() {
  // 從 HC-05 讀取回應並顯示在電腦
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }
  // 將電腦輸入的指令送給 HC-05
  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }
}
