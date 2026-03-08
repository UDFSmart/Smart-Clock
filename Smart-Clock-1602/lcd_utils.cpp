/*
 *    Copyright 2026 UDFOwner
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *
 *    More details: https://udfsoft.com/
 */

#include "lcd_utils.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

MessageNotification notification;

void lcd_init() {
  Wire.begin(4, 5);
  lcd.init();
  lcd.backlight();
}

void drawText(LiquidCrystal_I2C &lcd, const char *text, uint8_t col, uint8_t row) {
  lcd.setCursor(col, row);
  lcd.print(text);

  int len = strlen(text);
  for (int i = 0; i < (16 - len - col); i++) {
    lcd.print(" ");
  }
}

void drawText(LiquidCrystal_I2C &lcd, const String text, uint8_t col, uint8_t row) {
  lcd.setCursor(col, row);
  lcd.print(text);

  int len = text.length();
  for (int i = 0; i < (16 - len - col); i++) {
    lcd.print(" ");
  }
}

void drawText(LiquidCrystal_I2C &lcd, const char *text, uint8_t col, uint8_t row, unsigned long delayMsec) {
  drawText(lcd, text, col, row);
  delay(delayMsec);
}

void printPostCode(LiquidCrystal_I2C &lcd, int code, uint8_t col, uint8_t row, unsigned long delayMsec) {
  char buf[96];

  snprintf(buf, sizeof(buf), "CODE: %d", (int)code);
  drawText(lcd, buf, col, row, delayMsec);
}

void drawScrollText(LiquidCrystal_I2C &lcd, const char *text, uint8_t col, uint8_t row, uint16_t &pos) {
    const uint8_t width = 16;
    const uint16_t scrollInterval = 1000;
    const uint16_t pauseStart = 1500;
    const uint16_t pauseEnd = 1500;

    static unsigned long lastScroll = 0;
    static bool atStart = true;
    static bool atEnd = false;

    size_t len = strlen(text);
    char buf[17];

    unsigned long now = millis();

    if (len <= width) {
        snprintf(buf, sizeof(buf), "%-16s", text);
        lcd.setCursor(col, row);
        lcd.print(buf);
        return;
    }

    if (atStart) {
        snprintf(buf, sizeof(buf), "%-16s", text);
        lcd.setCursor(col, row);
        lcd.print(buf);

        if (now - lastScroll >= pauseStart) {
            atStart = false;
            lastScroll = now;
        }
        return;
    }

    if (atEnd) {
        for (uint8_t i = 0; i < width; i++) {
            buf[i] = text[(pos + i) % len];
        }
        buf[16] = '\0';
        lcd.setCursor(col, row);
        lcd.print(buf);

        if (now - lastScroll >= pauseEnd) {
            pos = 0;
            atStart = true;
            atEnd = false;
            lastScroll = now;
        }
        return;
    }

    if (now - lastScroll >= scrollInterval) {
        lastScroll = now;

        for (uint8_t i = 0; i < width; i++) {
            buf[i] = text[(pos + i) % len];
        }
        buf[16] = '\0';
        lcd.setCursor(col, row);
        lcd.print(buf);

        pos++;
        if (pos + width >= len) {
            atEnd = true;
        }
    }
}
