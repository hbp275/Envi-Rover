#include <SPI.h>
#include <LoRa.h>

// Define LoRa module pins
#define LORA_SS 10
#define LORA_RST 9
#define LORA_DIO0 2

// Joystick pins
#define JOY_X A0
#define JOY_Y A1
#define JOY_SW 3  // Button (SW)

void setup() {
  pinMode(JOY_SW, INPUT_PULLUP); // Button input with pull-up

  // Initialize LoRa
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    while (1); // Stop if LoRa fails
  }
}

void loop() {
  int xValue = analogRead(JOY_X);
  int yValue = analogRead(JOY_Y);
  int swValue = digitalRead(JOY_SW);

  char command = '\0'; // Default no command

  // Priority: Check push button
  if (swValue == LOW) {
    command = 'o'; // Request sensor data
  }
  else {
    // Joystick movement
    if (yValue > 800) {
      command = 'w'; // Forward
    } else if (yValue < 200) {
      command = 's'; // Backward
    } else if (xValue < 200) {
      command = 'a'; // Left
    } else if (xValue > 800) {
      command = 'd'; // Right
    } else {
      command = 'x'; // Joystick centered → STOP
    }
  }

  // Send the detected command
  if (command != '\0') {
    LoRa.beginPacket();
    LoRa.print(command);
    LoRa.endPacket();
    delay(200); // Small delay to avoid spamming
  }
}
