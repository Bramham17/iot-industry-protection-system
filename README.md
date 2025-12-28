# IoT Industry Protection System Using Arduino Node MCU

## Project Overview

A comprehensive **IoT-based Industrial Protection System** designed to monitor and protect industrial environments from potential hazards. This system uses Arduino Node MCU microcontroller with multiple sensors to detect dangerous conditions in real-time and send alerts via Blynk cloud platform.

 **Guided by:** Dr. M. Mathan Kumar
**Institution:** Malla Reddy University, Hyderabad
**Year:** 2022-2023

---

## Features

- Real-time monitoring via Blynk cloud platform
- Multi-sensor integration (Temperature, Gas, Fire, Light)
- Emergency SMS and app notifications
- 20x4 LCD display for on-site monitoring
- WiFi-based wireless communication
- Cost-effective design (50% reduction vs traditional systems)
- Automated emergency response (buzzer, relay control)
- Scalable architecture with 16-CH analog multiplexer

---

## Hardware Components

### Microcontrollers
- ESP8266 Node MCU (Main IoT platform with WiFi)
- Arduino UNO R3 (Sensor processing)

### Sensors
| Sensor | Purpose | Specifications |
|--------|---------|----------------|
| DHT22 | Temperature & Humidity | -40C to +80C, +/-0.5C accuracy |
| MQ2 Gas Sensor | Gas Leakage Detection | Detects LPG, CH4, CO, Alcohol, Smoke |
| Fire Sensor (RKI-3100) | Flame Detection | 760nm-1100nm Detection Range |
| Light Dependent Resistor | Light Intensity | Adjustable threshold sensitivity |
| LM-35 | Temperature Measurement | 10mV/C sensitivity |
 
## System Algorithm

1. Initialize WiFi and Blynk connection
2. Continuously read sensor values
3. Check against critical thresholds:
   - Temperature > 40C
   - Gas Level > 500 ppm
   - Fire Detected
   - Light < 200 lux
4. Display readings on LCD
5. Update Blynk app in real-time
6. On emergency detection:
   - Activate buzzer
   - Turn on relay device
   - Send SMS alert
   - Update app notification
7. Loop with 2-second delay

### DHT22 Humidity Sensor
- Temperature Range: -40C to +80C
- Humidity Range: 0-100% RH
- Accuracy: +/-0.5C temp, +/-2% humidity
- Resolution: 16-bit
