#include "commands.h"
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

#include <Arduino.h>
#include <cstddef>
#include "command_executor.h"

static Command commands[] = {
  { COMMAND_PIN_ON, commands_setPinOn },
  { COMMAND_PIN_OFF, commands_setPinOff },
  { COMMAND_RELAY_ON, commands_setRelayOn },
  { COMMAND_RELAY_OFF, commands_setRelayOff },
  { COMMAND_PIN_WATCH, commands_setStatus },
  { COMMAND_REBOOT, commands_setReboot },
  { COMMAND_HARDRESET, commands_setHardReset },
  { COMMAND_UPDATE_TIME, commands_updateTime },
  { COMMAND_SHOW_MESSAGE, commands_showMessage }
};

unsigned long lastPoll = 0;

unsigned long pollInterval = DEFAULT_POLL_INTERVAL;

static OnResultCommandFunction globalOnResult = nullptr;

static void handleCommandResult(const char* cmd, const char* param, const char* status);

void command_executor_execute(const char* cmd, const char* param, CommandFunctionCallback function) {
  if (!cmd || strlen(cmd) == 0) {
    log_i("No command received");
    return;
  }

  size_t commandsCount = sizeof(commands) / sizeof(commands[0]);

  for (size_t i = 0; i < commandsCount; ++i) {
    if (strcmp(commands[i].name, cmd) == 0) {
      commands[i].function(param, function);

      return;
    }
  }

  if (function) function(cmd, param, "Unknown command");
}

void command_executor_handleCommandRequest(const HttpHeader* headers, size_t headersCount, OnResultCommandFunction onResultFunc) {
  char cmd[32] = { 0 };
  char param[32] = { 0 };

  for (size_t i = 0; i < headersCount; i++) {
    const char* name = headers[i].name;

    if (strcmp(name, X_CMD) == 0) {  // if name == X_CMD
      const char* value = headers[i].value;
      strlcpy(cmd, value, sizeof(cmd));
    } else if (strcmp(name, X_CMD_PARAM) == 0) {  // if name == X_CMD_PARAM
      strlcpy(param, headers[i].value, sizeof(param));
    } else if (strcmp(name, X_POLL_INTERVAL) == 0) {  // if name == X_POLL_INTERVAL
      pollInterval = atoi(headers[i].value);
      if (pollInterval <= 1000) pollInterval = DEFAULT_POLL_INTERVAL;
    }
  }

  log_i("command: %s; Param: %s", cmd, param);
  log_i("pollInterval: %lu", pollInterval);

  globalOnResult = onResultFunc;

  command_executor_execute(cmd, param, handleCommandResult);
}

static void handleCommandResult(const char* cmd, const char* param, const char* status) {
  if (strcmp(cmd, COMMAND_HARDRESET) == 0) {
    log_i("Smart device: RESET!");
    Serial.flush();
  } else {
    log_i("command: %s; Param: %s; Status: %s\n", cmd, param, status);
  }

  delay(50);

  if (globalOnResult)
    globalOnResult(cmd, param, status);  // sendResult(cmd, param, status);
}
