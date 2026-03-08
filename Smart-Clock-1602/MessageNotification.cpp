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

#include "MessageNotification.h"
#include <string.h>

MessageNotification::MessageNotification()
  : notificationExpireTime(0) {
  _buffer[0] = '\0';
}

void MessageNotification::setMessage(const char* notification, unsigned long delay) {
  if (notification == nullptr) return;

  strncpy(_buffer, notification, sizeof(_buffer) - 1);
  _buffer[sizeof(_buffer) - 1] = '\0';

  notificationExpireTime = millis() + delay;
}

void MessageNotification::setPostCodeMessage(PostCode code, unsigned long delay) {
  snprintf(_buffer, sizeof(_buffer), "CODE: %d", (int)code);

  notificationExpireTime = millis() + delay;
}

void MessageNotification::setNumberMessage(int number, unsigned long delay) {
  snprintf(_buffer, sizeof(_buffer), "CODE: %d", number);

  notificationExpireTime = millis() + delay;
}

bool MessageNotification::hasNotification(unsigned long currentMillis) const {
  return (long)(notificationExpireTime - currentMillis) > 0;
}

const char* MessageNotification::getMessage() const {
  return _buffer;
}
