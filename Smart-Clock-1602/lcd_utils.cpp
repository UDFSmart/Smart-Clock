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

void lcd_init() {
  Wire.begin(4, 5);
  lcd.init();
  lcd.backlight();
}

void drawText(LiquidCrystal_I2C &lcd, const char *text, uint8_t col, uint8_t row) {
  lcd.setCursor(col, row);
  lcd.print(text);  // Печатаем текст

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
