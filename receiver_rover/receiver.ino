#include <SPI.h>
#include <LoRa.h>
#include <Servo.h>
#include <DHT.h>

#define LORA_SS 10
#define LORA_RST 9
#define LORA_DIO0 2

#define SERVO_PIN 3

// DHT Sensor setup
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Ultrasonic sensor
#define TRIG_PIN 5
#define ECHO_PIN 6

Servo myServo;

void setup() {
  Serial.begin(9600);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  myServo.attach(SERVO_PIN);
  dht.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("LoRa Rover Ready!");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedData = "";
    while (LoRa.available()) {
      receivedData += (char)LoRa.read();
    }

    if (receivedData == "m") {
      // Sensor data requested
      float temp = dht.readTemperature();
      float hum = dht.readHumidity();
      long duration;
      float distance;

      digitalWrite(TRIG_PIN, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);
      duration = pulseIn(ECHO_PIN, HIGH);
      distance = duration * 0.034 / 2;

      String sensorData = "T:" + String(temp) + "C, H:" + String(hum) + "%, D:" + String(distance) + "cm";
      Serial.println("Sending: " + sensorData);

      LoRa.beginPacket();
      LoRa.print(sensorData);
      LoRa.endPacket();
    } else {
      // Servo control
      int receivedAngle = receivedData.toInt();
      if (receivedAngle >= 0 && receivedAngle <= 180) {
        myServo.write(receivedAngle);
        Serial.println("Received Angle: " + String(receivedAngle));
      } else {
        Serial.println("Invalid Angle Received");
      }
    }
  }

  delay(100);
}
