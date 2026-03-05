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

#include "Clock.h"

Clock::Clock() {
  memset(&_timeinfo, 0, sizeof(_timeinfo));
}

void Clock::setEpoch(time_t epoch) {
  struct timeval tv;
  tv.tv_sec = epoch;
  tv.tv_usec = 0;
  settimeofday(&tv, nullptr);
}

void Clock::update() {
  time_t now;
  time(&now);
  localtime_r(&now, &_timeinfo);
}

int Clock::hour() const {
  return _timeinfo.tm_hour;
}
int Clock::minute() const {
  return _timeinfo.tm_min;
}
int Clock::second() const {
  return _timeinfo.tm_sec;
}

int Clock::day() const {
  return _timeinfo.tm_mday;
}
int Clock::month() const {
  return _timeinfo.tm_mon + 1;
}
int Clock::year() const {
  return _timeinfo.tm_year + 1900;
}

String Clock::timeStr(const char* format) const {
  char buf[16];
  snprintf(buf, sizeof(buf), format, hour(), minute(), second());
  return String(buf);
}

String Clock::dateStr(const char* format) const {
  char buf[16];
  snprintf(buf, sizeof(buf), format, day(), month(), year());
  return String(buf);
}
