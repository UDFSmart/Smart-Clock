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

#include "config.h"

#include "network_utils.h"
#include "string_utils.h"
#include "command_executor.h"

#include "Clock.h"

#include "tm1637_display_utils.h"

#define BASE_URL "https://smart.udfsoft.com/api/v1/devices/commands"
#define GET_COMMAND_URL BASE_URL

Clock rtc;

void setup() {
  Serial.begin(115200);
  delay(500);

  tm1637_init();

  display.showNumberDec(8001);

  setupWifi(display);

  display.showNumberDec(8002);

  initHttpRequest();

  display.showNumberDec(8003);
  display.clear();
}

void loop() {

  static unsigned long lastDisplayUpdateMs = 0;
  static bool colonState = false;

  unsigned long currentMillis = millis();

  if (currentMillis - lastDisplayUpdateMs >= 1000) {
    lastDisplayUpdateMs = currentMillis;
    colonState = !colonState;

    rtc.update();  // calculate time

    int hours = rtc.hour();
    int minutes = rtc.minute();

    int timeValue = hours * 100 + minutes;

    if (colonState) {
      display.showNumberDecEx(timeValue, 0b01000000, true);
    } else {
      display.showNumberDecEx(timeValue, 0, true);
    }
  }

  if (currentMillis - lastPoll >= pollInterval) {
    lastPoll = currentMillis;
    pollServer();
  }
}

void pollServer() {
  if (WiFi.status() != WL_CONNECTED) {
    log_i("Reconnecting WiFi...");
    display.showNumberDec(8801);
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

    // display.showNumberDec(code);

    switch (code) {
      case HTTP_CODE_NO_CONTENT:
        command_executor_handleCommandRequest(headers, count, sendCommandResult);
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

void sendCommandResult(const char* cmd, const char* param, const char* status) {
  if (WiFi.status() != WL_CONNECTED) {
    log_i("sendResult: WiFi.status() != WL_CONNECTED");
    display.showNumberDec(8802);
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
