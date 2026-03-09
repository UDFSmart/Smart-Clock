# 🕒 Smart Clock (lcd 1602)

**Smart Clock** is a firmware for a smart digital clock based on the ESP32-C3 microcontroller and an LCD 1602 (I2C) display. The device synchronizes time and date automatically and receives commands from the UDFSmart central control server via a secure connection (HTTPS).

The project is designed with a focus on autonomy, remote control, and easy integration into a smart home ecosystem.


[More Information](https://smart.udfsoft.com/)

---

## Photos

<img src="/Smart-Clock-1602/photos/photo_2026-02-22_13-36-16.jpg" alt="Device preview" width="400">
<img src="/Smart-Clock-1602/photos/photo_2026-02-20_02-44-16.jpg" alt="Device preview" width="400">
<img src="/Smart-Clock-1602/photos/photo_2026-02-22_13-04-21.jpg" alt="Device preview" width="400">
<img src="/Smart-Clock-1602/photos/photo_2026-02-20_02-44-15.jpg" alt="Device preview" width="400">
<img src="/Smart-Clock-1602/photos/photo_2026-02-20_02-44-14.jpg" alt="Device preview" width="400">

---

## Wiring Diagram

<img src="/Smart-Clock-1602/photos/wiring_diagram.jpg" alt="Device preview" width="400">

---

## 3D Models

[Table Clock](https://www.crealitycloud.com/ru/model-detail/699a4d285a776968b630fd7a)

[Wall Clock](https://www.crealitycloud.com/ru/model-detail/69a20e3c7666bb3e94a0b0a9)

---

### Requirements
### Hardware
* ESP32-C3
* LCD1602 I2C

### Software
* Arduino IDE 2.3.8 or higher
* WiFiManager (tzapu)
* LiquidCrystal_I2C
* WiFiManager
* Standard ESP32 libraries (WiFi, HTTPClient, WiFiClientSecure).

---

## 🛠 Hardware & Wiring
The project is configured for the following hardware (based on the source code):

  * Microcontroller: ESP32-C3 (or compatible ESP32 board).
  * Display: LCD 1602 with I2C module (Address 0x27).

Wiring Diagram (I2C):

| LCD 1602  |	ESP32-C3 (GPIO) |
| --------- | --------------- |
| SDA	      | GPIO 4          |
| SCL	      | GPIO 5          |
| VCC	      | 5V / 3.3V       |
| GND	      | GND             |

_Note: I2C pins are initialized in main.cpp as: Wire.begin(4, 5);._
---

## ⚙️ Installation & Configuration

1. **Dependencies**
To compile the project, you need PlatformIO or Arduino IDE with the following libraries installed:

  * LiquidCrystal_I2C
  * WiFiManager
  * Standard ESP32 libraries (WiFi, HTTPClient, WiFiClientSecure).

2. **Configuration (config.h)**

Before flashing, you must edit the config.h file to include your unique credentials.

```cpp
// config.h

#pragma once

#define DEVICE_ID "xxxx-xxxx-xxxx-xxxx"    // YOUR DEVICE ID, to get it write to us: support@udfsoft.com

#define DEVICE_TYPE "clock"                // type of your device
#define DEVICE_CONTROLLER_TYPE "esp32-c3"  // type of your device


#define API_KEY "xxxxxxxxxxxxxxxxxxxxxx"  // YOUR API Key, to get it write to us: support@udfsoft.com

#define APP_VERSION "1"

static const uint8_t customMAC[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // if needed!
```

ℹ️ How to get keys? To obtain your DEVICE_ID and API_KEY, please contact support: support@udfsoft.com.
---



```Smart-Clock-1602.ino``` - Entry Point

---

## 📄 License
This project is licensed under the Apache License 2.0. See the LICENSE file or source code headers for details.

```Plaintext
Copyright 2026 UDFOwner

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
```
**Developed by UDFSoft** More details: [udfsoft.com](https://udfsoft.com/?utm_source=github-smart-clock)
