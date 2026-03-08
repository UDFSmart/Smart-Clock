# 🕒 Умные часы (LCD 1602)

**Умные часы** — это прошивка для умных цифровых часов на базе микроконтроллера ESP32-C3 и ЖК-дисплея 1602 (I2C). Устройство автоматически синхронизирует время и дату и получает команды от центрального сервера управления UDFSmart через защищенное соединение (HTTPS).

Проект разработан с акцентом на автономность, дистанционное управление и простую интеграцию в экосистему умного дома.

[Дополнительная информация](https://smart.udfsoft.com/)

---

## Фотографии

<img src="Smart-Clock-1602/photos/photo_2026-02-22_13-36-16.jpg" alt="Device preview" width="400">
<img src="Smart-Clock-1602/photos/photo_2026-02-20_02-44-16.jpg" alt="Device preview" width="400">
<img src="Smart-Clock-1602/photos/photo_2026-02-22_13-04-21.jpg" alt="Device preview" width="400">
<img src="Smart-Clock-1602/photos/photo_2026-02-20_02-44-15.jpg" alt="Device preview" width="400">
<img src="Smart-Clock-1602/photos/photo_2026-02-20_02-44-14.jpg" alt="Device preview" width="400">

---
---

## 3D-модели

[Настольные часы](https://www.crealitycloud.com/ru/model-detail/699a4d285a776968b630fd7a)

[Настенные часы](https://www.crealitycloud.com/ru/model-detail/69a20e3c7666bb3e94a0b0a9)

---

## Компиляция и загрузка прошивки

### Требования
### Аппаратное обеспечение
* ESP32-C3
* LCD1602 I2C

### Программное обеспечение
* Arduino IDE 2.3.8 или выше
* WiFiManager (tzapu)

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
