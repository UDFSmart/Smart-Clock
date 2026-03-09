# 🕒 Умные часы (LCD 1602)

**Умные часы** — это прошивка для умных цифровых часов на базе микроконтроллера ESP32-C3 и ЖК-дисплея 1602 (I2C). Устройство автоматически синхронизирует время и дату и получает команды от центрального сервера управления UDFSmart через защищенное соединение (HTTPS).

Проект разработан с акцентом на автономность, дистанционное управление и простую интеграцию в экосистему умного дома.

[Дополнительная информация](https://smart.udfsoft.com/)

---

## Фотографии

<img src="/Smart-Clock-1602/photos/photo_2026-02-22_13-36-16.jpg" alt="Предварительный просмотр устройства" width="400">
<img src="/Smart-Clock-1602/photos/photo_2026-02-20_02-44-16.jpg" alt="Предварительный просмотр устройства" width="400">
<img src="/Smart-Clock-1602/photos/photo_2026-02-22_13-04-21.jpg" alt="Предварительный просмотр устройства" width="400">
<img src="/Smart-Clock-1602/photos/photo_2026-02-20_02-44-15.jpg" alt="Предварительный просмотр устройства" width="400">
<img src="/Smart-Clock-1602/photos/photo_2026-02-20_02-44-14.jpg" alt="Предварительный просмотр устройства" width="400">

---

## Схема подключения

<img src="/Smart-Clock-1602/photos/wiring_diagram.jpg" alt="Device preview" width="400">

---

## 3D-модели

[Настольные часы](https://www.crealitycloud.com/ru/model-detail/699a4d285a776968b630fd7a)

[Настенные часы](https://www.crealitycloud.com/ru/model-detail/69a20e3c7666bb3e94a0b0a9)

---

### Требования
### Аппаратное обеспечение
* ESP32-C3
* LCD1602 I2C

### Программное обеспечение
* Arduino IDE 2.3.8 или выше
* WiFiManager (tzapu)
* LiquidCrystal_I2C
* WiFiManager
* Стандартные библиотеки ESP32 (WiFi, HTTPClient, WiFiClientSecure).

---

## 🛠 Аппаратное обеспечение и подключение
Проект настроен для следующего оборудования (на основе исходного кода):

* Микроконтроллер: ESP32-C3 (или совместимая плата ESP32).

* Дисплей: LCD 1602 с модулем I2C (адрес 0x27).

Схема подключения (I2C):

| LCD 1602  |	ESP32-C3 (GPIO) |
| --------- | --------------- |
| SDA	      | GPIO 4          |
| SCL	      | GPIO 5          |
| VCC	      | 5V / 3.3V       |
| GND	      | GND             |

_Примечание: контакты I2C инициализируются в main.cpp следующим образом: Wire.begin(4, 5);._
---

## ⚙️ Установка и настройка

1. **Зависимости**
Для компиляции проекта вам потребуется PlatformIO или Arduino IDE со следующими установленными библиотеками:

* LiquidCrystal_I2C

* WiFiManager

* Стандартные библиотеки ESP32 (WiFi, HTTPClient, WiFiClientSecure).

2. **Конфигурация (config.h)**

Перед прошивкой необходимо отредактировать файл config.h, добавив в него ваши уникальные учетные данные.

```cpp
// config.h

#pragma once

#define DEVICE_ID "xxxx-xxxx-xxxx-xxxx" // ВАШ ИДЕНТИФИКАТОР УСТРОЙСТВА. Чтобы получить его, напишите нам: support@udfsoft.com

#define DEVICE_TYPE "clock" // тип вашего устройства
#define DEVICE_CONTROLLER_TYPE "esp32-c3" // тип вашего устройства

#define API_KEY "xxxxxxxxxxxxxxxxxxxxxx" // ВАШ API-ключ. Чтобы получить его, напишите нам: support@udfsoft.com

#define APP_VERSION "1"

static const uint8_t customMAC[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // при необходимости!

```

ℹ️ Как получить ключи? Чтобы получить DEVICE_ID и API_KEY, обратитесь в службу поддержки: support@udfsoft.com.

--

```Smart-Clock-1602.ino``` - Точка входа

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
