# SwordFish
Open Source Underwater Scooter. Made by MakerMods

## Overview
This project is part of MakerMods' initiative to develop an underwater scooter that uses hall effect sensors to control two thrusters. The code provided allows the scooter to read values from the hall effect sensors and adjust the speed of the thrusters accordingly.

## Features
1. Hall Effect Sensor Integration: Reads analog values from hall effect sensors to determine throttle input.
2. ESC Control: Utilizes DShot protocol to communicate with the Electronic Speed Controllers (ESCs) controlling the thrusters.
3. Auto Calibration: Automatically calibrates the range of hall effect sensor values to ensure accurate throttle control.
4. Deadzone Handling: Implements deadzones to prevent unintended minor adjustments in throttle.

## Hardware Requirements
1. 2 ESCs compatible with DShot protocol (Link)
2. 2 Blue Robotics T200 Thrusters (Link)
3. 2 Hall Effect Sensors (Link)
4. Arduino Board (I forgot which board)

## Software Requirements
1. Arduino IDE
2. DShot library for Arduino. For more information on how to download the library [gueei/Dshot-Arduino](https://github.com/gueei/DShot-Arduino)

## Pin Configuration
1. Left ESC: Pin 11
2. Right ESC: Pin 10
3. Left Hall Effect Sensor: A0
4. Right Hall Effect Sensor: A1

## Getting Started

1. **Hardware Setup**:
    - Connect the ESCs to pins 11 and 10.
    - Connect the hall effect sensors to A0 and A1.

2. **Software Setup**:
    - Install the DShot library in Arduino IDE.
    - Upload the provided code to the Arduino.

3. **Calibration and Testing**:
    - The system will auto-calibrate the hall effect sensors during operation.
    - Observe the serial monitor for calibration data and throttle values.
  
## Contributing
Contributions to improve the code and functionality are welcome. Please fork the repository and create a pull request with your enhancements.

## License
This project is open-source and licensed under the MIT License. For more details, refer to the LICENSE file.

---

Developed by the MakerMods Team. For more information, visit [MakerMods](https://github.com/RapidCAMO/SwordFish).
