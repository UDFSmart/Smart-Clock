
#include "string_utils.h"

#include <cstring>

void sanitizePath(char* s) {
  for (; *s; s++) {
    if (*s == ' ') *s = '_';
  }
}

bool parseMessageСommandParam(const char* param, char* message, size_t messageSize, uint32_t* durationMs) {
  const char* sep = strchr(param, '|');
  if (!sep) return false;

  // копируем Message
  size_t len = sep - param;
  if (len >= messageSize) len = messageSize - 1;

  memcpy(message, param, len);
  message[len] = '\0';

  // парсим 3000
  *durationMs = strtoul(sep + 1, nullptr, 10);

  return true;
}