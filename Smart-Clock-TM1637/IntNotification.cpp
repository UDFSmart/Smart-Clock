#include <sys/_types.h>
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

#include "IntNotification.h"

IntNotification::IntNotification() : notification(0), notificationExpireTime(0) {
}

void IntNotification::setMessage(int notification, unsigned long delay) {
  this->notification = notification;
  notificationExpireTime = delay + millis();
}

bool IntNotification::hasNotification(unsigned long currentMillis) const {
  return (long)(notificationExpireTime - currentMillis) > 0;
}

int IntNotification::getMessage() const {
  return notification;
}
