#include <SoftwareSerial.h>

// 藍牙軟體序列埠 (RX, TX)
// Pin 10 接 HC-05 TXD, Pin 11 接 HC-05 RXD
SoftwareSerial BTSerial(10, 11);

const int buttonPin = 2;   // 按鈕腳位
const int motorEnablePin = 9; // 接 L293D Pin 1 (PWM 控制轉速)

int lastButtonState = -1;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(motorEnablePin, OUTPUT);

  Serial.begin(9600);    // 序列埠監控視窗
  BTSerial.begin(9600);  // HC-05 鮑率預設 9600

  Serial.println("Master Node Initialized with L293D.");
}

void loop() {
  // 1. 讀取按鈕並傳送給 Slave
  int currentButtonState = digitalRead(buttonPin);
  if (currentButtonState != lastButtonState) {
    if (currentButtonState == LOW) {
      BTSerial.write('H'); // 按下按鈕，命令 Slave 開燈
      Serial.println("Button Pressed -> Sent: H");
    } else {
      BTSerial.write('L'); // 放開按鈕，命令 Slave 關燈
      Serial.println("Button Released -> Sent: L");
    }
    lastButtonState = currentButtonState;
  }

  // 2. 接收 Slave 傳來的可變電阻轉速 (0 ~ 255)
  if (BTSerial.available() > 0) {
    int motorSpeed = BTSerial.read();
    
    // 輸出 PWM 到 L293D 的 Enable 腳位
    analogWrite(motorEnablePin, motorSpeed);

    Serial.print("Motor Speed: ");
    Serial.println(motorSpeed);
  }

  delay(20);
}
