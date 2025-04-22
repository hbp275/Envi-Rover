# EnviRover

**EnviRover** is a LoRa-based environmental monitoring rover that can be remotely controlled. It collects real-time data like temperature, humidity, and distance from obstacles and sends it wirelessly to the controller through the LoRa.

## Features
- Remote servo control
- LoRa-based long-range communication
- Sensor data reporting (DHT11 + Ultrasonic)
- Two-way communication between controller and rover (Half Duplex)

## Hardware Used
- Arduino UNO (x2)
- LoRa Modules (x2)
- DHT11 Sensor
- HC-SR04 Ultrasonic Sensor
- DC Motor (Weels)
- Servo Motor
- Open Board, Breadboards, jumper wires, etc.

## Code Structure
- `/transmitter_controller`: Code for controller (transmitter)
- `/receiver_rover`: Code for rover (receiver + sensors)

## How It Works
- The controller sends servo directions via LoRa based on the keywords (W,A,S,D) position.
- When the user presses `m` in the Serial Monitor, the rover responds with sensor data.
- The rover reads temperature, humidity, and obstacle distance, and sends the data back via LoRa.

## Author
Harish A Electronics & Communication Engineering, 6th Sem

