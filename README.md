# EnviRover

**EnviRover** is a LoRa-based environmental monitoring rover that can be remotely controlled using a joystick. It collects real-time data like temperature, humidity, and distance from obstacles and sends it wirelessly to the controller.

## Features
- Remote servo control via joystick
- LoRa-based long-range communication
- Sensor data reporting (DHT11 + Ultrasonic)
- Two-way communication between controller and rover

## Hardware Used
- Arduino UNO (x2)
- LoRa SX1278 Modules (x2)
- DHT11 Sensor
- HC-SR04 Ultrasonic Sensor
- Joystick Module
- Servo Motor
- Breadboards, jumper wires, etc.

## Code Structure
- `/transmitter_controller`: Code for joystick controller (transmitter)
- `/receiver_rover`: Code for rover (receiver + sensors)
- `/extras`: Optional files (e.g., circuit diagrams)

## How It Works
- The controller sends servo directions via LoRa based on the keywords (W,A,S,D) position.
- When the user presses `m` in the Serial Monitor, the rover responds with sensor data.
- The rover reads temperature, humidity, and obstacle distance, and sends the data back via LoRa.

## Author
Harish (Electronics & Communication Engineering, 6th Sem)

