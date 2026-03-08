#include <cstring>
/*
 *    Copyright 2025 UDFOwner
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

#include "commands.h"

#include <Arduino.h>

#include <esp_system.h>
#include <nvs_flash.h>

#include "string_utils.h"

#include "lcd_utils.h"

#define COMMAND_RESULT_SIZE 128

#define RELAY_PIN_PARAM "0"


// =======================
// Private Commands
// =======================

static void cmdReboot(char* result, size_t resultSize, const char* param, CommandFunctionCallback callback) {
  if (callback) {
    callback(COMMAND_REBOOT, param, "Device: rebooted!");
  }

  delay(300);

  ESP.restart();
}

static void cmdHardReset(char* result, size_t resultSize, const char* param, CommandFunctionCallback callback) {
  if (callback) {
    callback(COMMAND_HARDRESET, param, "Device: rebooted!");
  }

  delay(200);

  nvs_flash_erase();  // erase NVS (Wi-Fi)
  nvs_flash_init();

  delay(200);
  esp_restart();
}

// =======================
// Public Commands
// =======================
void commands_setReboot(const char* param, CommandFunctionCallback callback) {
  char result[COMMAND_RESULT_SIZE] = { 0 };
  cmdReboot(result, COMMAND_RESULT_SIZE, param, callback);
}

void commands_setHardReset(const char* param, CommandFunctionCallback callback) {
  char result[COMMAND_RESULT_SIZE] = { 0 };
  cmdHardReset(result, COMMAND_RESULT_SIZE, param, callback);
}

void commands_updateTime(const char* param, CommandFunctionCallback callback) {
  if (param == nullptr || strlen(param) < 10) {
    if (callback) callback(COMMAND_UPDATE_TIME, param, "Error: Invalid timestamp");
    return;
  }

  time_t timestamp = (time_t)atoll(param);

  struct timeval tv;
  tv.tv_sec = timestamp;
  tv.tv_usec = 0;

  if (settimeofday(&tv, nullptr) == 0) {
    tzset();
    log_i("System time updated to: %lld", (long long)timestamp);

    if (callback) callback(COMMAND_UPDATE_TIME, param, "The time has been updated!");
  } else {
    if (callback) callback(COMMAND_UPDATE_TIME, param, "Error: System failed to set time");
  }
}

void commands_showMessage(const char* param, CommandFunctionCallback callback) {

  const char* sep = strchr(param, '|');
  if (sep) {
    size_t len = sep - param;

    char tempMsg[128];
    if (len >= sizeof(tempMsg)) len = sizeof(tempMsg) - 1;

    memcpy(tempMsg, param, len);
    tempMsg[len] = '\0';

    uint32_t durationInSec = strtoul(sep + 1, nullptr, 10);

    notification.setMessage(tempMsg, durationInSec * 1000UL);

    if (callback) callback(COMMAND_SHOW_MESSAGE, param, "Message Showed!");
  } else {
    if (callback) callback(COMMAND_SHOW_MESSAGE, param, "Parsing error!");
  }
}

void commands_setBacklight(const char* param, CommandFunctionCallback callback) {
  if (param && strcmp(param, "1") == 0) {
    lcd.backlight();
  } else {
    lcd.noBacklight();
  }

  if (callback) callback(COMMAND_SET_BACKLIGHT, param, "Successful");
}
