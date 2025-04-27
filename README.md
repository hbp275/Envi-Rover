🚀 EnviRover is a rover system controlled remotely over LoRa communication. It can move in all four directions and return environmental data (temperature and humidity) upon request.

Features
📡 LoRa-Based Wireless Communication (433 MHz)

🎮 Two Control Modes: Serial Monitor or Joystick

🌡️ Environmental Monitoring: Temperature and Humidity readings using DHT11 sensor

⏳ Timeout Handling: Waits for sensor data for 5 seconds to avoid blocking

🛠️ Motor Driver Integration: Smooth motor control using PWM signals

Hardware Components
Arduino Uno (x2)

LoRa SX1278 modules (x2)

Motor Driver (L298N / similar)

DHT11 Temperature and Humidity Sensor

4 DC Motors + Chassis

Joystick Module (x1) (optional for joystick control)

Jumper wires, Battery, etc.

Software Overview
1. Transmitter Arduino (Controller)
Option 1: Serial Monitor Controller

Control rover by typing commands (w, a, s, d, o) in Serial Monitor.

Useful for debugging or testing.

Option 2: Joystick Controller

Move joystick to send movement commands.

Press joystick button to request sensor data.

Offers more intuitive, real-time control.

2. Receiver Arduino (Rover)
Receives movement commands over LoRa.

Controls motors accordingly.

Sends sensor data back when requested.

Command Set

Command	Action
w	Move Forward
s	Move Backward
a	Turn Left
d	Turn Right
x	Stop
o	Request Sensor Data
