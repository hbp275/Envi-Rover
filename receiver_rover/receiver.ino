#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

// Define LoRa module pins
#define LORA_SS 10
#define LORA_RST 9
#define LORA_DIO0 2

// Define DHT11
#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Motor driver pins
#define IN1 4
#define IN2 5
#define ENA 6
#define IN3 7
#define IN4 8
#define ENB 11

void setup() {
  // No Serial.begin()

  // Set motor pins as OUTPUT
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Start motors disabled
  stopMotors();
  
  // Enable PWM always ON (important)
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);

  dht.begin();

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    while (1); // Stay here if LoRa fails
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize > 0) {
    String incoming = "";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }
    incoming.trim();  // Remove \n \r spaces

    if (incoming.length() > 0) {
      char command = incoming.charAt(0);  // Take only first clean character

      if (command == 'o') {
        sendSensorData();
      } else if (isValidMotorCommand(command)) {
        controlMotors(command);
      }
    }
  }
}

bool isValidMotorCommand(char c) {
  return (c == 'w' || c == 'a' || c == 's' || c == 'd' || c == 'x');
}

void controlMotors(char command) {
  // Always keep ENA and ENB powered
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);

  switch (command) {
    case 'w': // Forward
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    

    case 's': // Backward
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;

    case 'a': // Turn Left
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;

    case 'd': // Turn Right
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;

    case 'x': // Stop
      stopMotors();
      break;
  }
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void sendSensorData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  String sensorData = "";

  if (isnan(humidity) || isnan(temperature)) {
    sensorData = "Error: DHT Sensor!";
  } else {
    sensorData = "Humidity:" + String(humidity, 1) + "% Temp:" + String(temperature, 1) + "C";
  }

  LoRa.beginPacket();
  LoRa.print(sensorData);
  LoRa.endPacket();
}