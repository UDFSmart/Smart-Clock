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

#include "config.h"

#include "network_utils.h"
#include "string_utils.h"
#include "command_executor.h"

#include "Clock.h"

#define BASE_URL "https://smart.udfsoft.com/api/v1/devices/commands"
#define GET_COMMAND_URL BASE_URL

LiquidCrystal_I2C lcd(0x27, 16, 2);
Clock rtc;

void setup() {
  Serial.begin(115200);

  Wire.begin(4, 5);
  lcd.init();
  lcd.backlight();

  drawText(lcd, "Hello!", 0, 0, 2000);
  drawText(lcd, "This is your", 0, 0);
  drawText(lcd, "Smartclock", 0, 1, 3000);

  setupWifi(lcd);

  initHttpRequest();

  configTime(2 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  drawText(lcd, "Updating time", 0, 0);

  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) {
    delay(500);
  }

  lcd.clear();
}

void loop() {

  static unsigned long lastDisplayUpdateMs = 0;

  if (millis() - lastDisplayUpdateMs >= 1000) {
    lastDisplayUpdateMs = millis();

    rtc.update();  // calculate time

    drawText(lcd, rtc.dateStr("%02d.%02d.%04d"), 3, 0);  // date
    drawText(lcd, rtc.timeStr("%02d:%02d:%02d"), 4, 1);  // time
  }

  if (millis() - lastPoll >= pollInterval) {
    lastPoll = millis();
    pollServer();
  }
}

void pollServer() {
  if (WiFi.status() != WL_CONNECTED) {
    log_i("Reconnecting WiFi...");
    drawText(lcd, "Reconnecting...", 0, 0, 1000);
    WiFi.reconnect();
    return;
  }

  const char* collectHeaders[] = {
    X_CMD,
    X_CMD_PARAM,
    X_POLL_INTERVAL
  };

  processHttpRequest(GET_COMMAND_URL, "GET", nullptr, nullptr, 0, collectHeaders, 3, 15000, [](int code, const HttpHeader* headers, size_t count) {
    log_i("HTTPS Response code: %u", code);

    switch (code) {
      case HTTP_CODE_NO_CONTENT:
        command_executor_handleCommandRequest(headers, count, sendResult);
        break;
      case HTTP_CODE_NOT_FOUND:
        log_i("No command");
        break;
      case HTTP_CODE_FORBIDDEN:
        log_e("Access Forbidden! DEVICE_ID not found or API_KEY not valid");
        break;
      default:
        log_e("Unexpected code: %d", code);
    }
  });
}

void sendResult(const char* cmd, const char* param, const char* status) {
  if (WiFi.status() != WL_CONNECTED) {
    log_i("sendResult: WiFi.status() != WL_CONNECTED");
    return;
  }

  const int HEADERS_COUNT = 2;

  HttpHeader headers[HEADERS_COUNT];

  network_SetHeader(headers[0], X_CMD_STATUS, status);
  network_SetHeader(headers[1], X_CMD_PARAM, param);


  char postCommandUrl[256] = { 0 };

  snprintf(
    postCommandUrl,
    sizeof(postCommandUrl),
    "%s/%s",
    BASE_URL,
    cmd);

  sanitizePath(postCommandUrl);

  int code = processHttpRequest(postCommandUrl, "POST", nullptr, headers, HEADERS_COUNT);

  log_i("returned Code: %d", code);
}
