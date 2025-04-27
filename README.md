# EnviRover

**EnviRover** is a LoRa-based environmental monitoring rover that can be remotely controlled using either a Serial Monitor or a Joystick module. It collects real-time temperature and humidity data using a DHT11 sensor and sends it wirelessly back to the controller.

## Code Structure
- `/serial_monitor_controller ` : Code for controlling the rover via Serial Monitor Serial Monitor Controller 
- `/joystick_controller` : Code for controlling the rover using Joystick Module
- `/receiver_rover` : Code for rover-side motor control and sensor data transmission

## How It Works
- The transmitter Arduino sends movement commands (`w`, `a`, `s`, `d`) to the rover over LoRa.
- Pressing `o` (or pressing the joystick button) requests temperature and humidity data.
- The rover receives the commands, drives the motors accordingly, and sends back sensor readings when requested.
- If no sensor data is received within 5 seconds, the transmitter triggers a timeout to prevent blocking.

### Command Set
- `w` →  Move Forward
- `s` →  Move Backward
- `a` →  Turn Left
- `d` →  Turn Right
- `x` →  Stop
- `o` →  Request Sensor Data

## Author
Harish (Electronics & Communication Engineering, 6th Sem)
