#include <SPI.h>
#include <LoRa.h>
#include <Servo.h>

#define LORA_SS 10
#define LORA_RST 9
#define LORA_DIO0 2

#define SERVO_PIN 3
#define JOY_X_PIN A0
#define JOY_BUTTON_PIN 7

Servo myServo;

void setup() {
  Serial.begin(9600);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  pinMode(JOY_BUTTON_PIN, INPUT_PULLUP);
  myServo.attach(SERVO_PIN);

  Serial.println("LoRa Controller Ready!");
}

void loop() {
  // Read joystick and send angle
  int joystickX = analogRead(JOY_X_PIN);
  int angle = map(joystickX, 0, 1023, 0, 180);

  LoRa.beginPacket();
  LoRa.print(angle);
  LoRa.endPacket();

  myServo.write(angle);
  Serial.println("Sent Angle: " + String(angle));

  // Check for button press in Serial Monitor
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 'm') {
      // Send request for sensor data
      LoRa.beginPacket();
      LoRa.print("m");  // Trigger signal
      LoRa.endPacket();
      Serial.println("Requested Sensor Data");
    }
  }

  // Check for incoming sensor data
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedData = "";
    while (LoRa.available()) {
      receivedData += (char)LoRa.read();
    }
    Serial.println("Sensor Data Received: " + receivedData);
  }

  delay(200);
}
