# IoT-Based Motor Speed Control Using ESP32 (PWM + Wi-Fi + L298N)

This project demonstrates how to control a DC motor’s speed and direction through a web interface using an ESP32 and an L298N motor driver. PWM is used to vary motor speed, while direction is set via digital control pins.

## Features
- Wi-Fi based motor control from any browser
- Forward, Reverse, and Stop buttons
- Speed slider using PWM
- Works on local Wi-Fi network (LAN)

## Hardware Required
- ESP32 Dev Board
- L298N Motor Driver Module
- DC Motor (6–12V)
- Battery Pack (6–12V)
- Jumper Wires

## Wiring
| L298N Pin | ESP32 Pin |
|----------|-----------|
| IN1 | GPIO 27 |
| IN2 | GPIO 26 |
| ENA | GPIO 25 (PWM) |
| OUT1/OUT2 | Motor Terminals |
| GND | ESP32 GND + Battery GND |
| +12V | Motor Power Supply |

## Usage
1. Update Wi-Fi credentials in the code.
2. Upload the code to the ESP32.
3. Check Serial Monitor for ESP32 IP Address.
4. Open the IP Address in a web browser.
5. Use buttons & slider to control the motor.

## Applications
- Robotics
- Model Cars
- Conveyor Control
- IoT Automation Projects

## License
For academic and hobby use.
