#include <SPI.h>
#include <LoRa.h>

// Define LoRa module pins
#define LORA_SS 10
#define LORA_RST 9
#define LORA_DIO0 2

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize LoRa module
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed!");
    while (1);
  }

  Serial.println("LoRa Transmitter Initialized!");
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();  // Read user input from Serial Monitor

    // Send the command via LoRa
    LoRa.beginPacket();
    LoRa.print(command);
    LoRa.endPacket();

    // Print the command and its meaning
    printCommandDescription(command);

    // If 'o' command is sent, wait for the sensor data from the receiver
    if (command == 'o') {
      Serial.println("Requested Sensor Data...");
      String receivedData = "";
      long startTime = millis();
      
      // Wait for a response for 5 seconds
      while (millis() - startTime < 5000) {
        int packetSize = LoRa.parsePacket();
        if (packetSize) {
          while (LoRa.available()) {
            receivedData += (char)LoRa.read();  // Collect data from LoRa
          }
          break;
        }
      }

      // Display received sensor data or timeout message
      if (receivedData.length() > 0) {
        Serial.println("Received Sensor Data: " + receivedData);
      } else {
        Serial.println("No Sensor Data Received!");
      }
    }
  }
}

void printCommandDescription(char command) {


  // Print the meaning of each command
  switch (command) {
    case 'w':
      Serial.println("Forward");
      break;
    case 's':
      Serial.println("Backward");
      break;
    case 'a':
      Serial.println("Left");
      break;
    case 'd':
      Serial.println("Right");
      break;
    case 'o':
      Serial.println("Request Sensor Data");
      break;
    
  }
}