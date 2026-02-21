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

#include "network_utils.h"
#include "HardwareSerial.h"

WiFiClientSecure client;
HTTPClient http;

void copyHeaders(HttpHeader* resHeaders, int count, HTTPClient& http);

void initHttpRequest() {
  client.setInsecure();
}

int processHttpRequest(
  const char* url,
  const char* method,
  String* body,
  HttpHeader* extraHeaders,
  size_t headersCount,
  const char* collectHeaders[],
  int collectHeadersCount,
  int timeout,
  HttpResponseCallback callback) {

  http.begin(client, url);
  http.setTimeout(timeout);
  http.setReuse(true);

  setBaseHeaders(http);
  for (size_t i = 0; i < headersCount; i++) {
    http.addHeader(extraHeaders[i].name, extraHeaders[i].value);
  }

  if (collectHeadersCount > 0)
    http.collectHeaders(collectHeaders, collectHeadersCount);

  int code = -1;

  log_d("===== Start Request ====");
  log_d("%s %s", method, url);

  if (strcmp(method, "POST") == 0) {
    code = http.POST(body ? *body : "");
  } else {
    code = http.GET();
  }
  log_d("===== End Request ====");
  log_d("");

  int responseHeadersCount = http.headers();

  HttpHeader responseHeaders[responseHeadersCount > 0 ? responseHeadersCount : 1];

  if (responseHeadersCount > 0)
    copyHeaders(responseHeaders, responseHeadersCount, http);

  http.end();

  if (callback) {
    callback(code, responseHeaders, responseHeadersCount);
  }

  return code;
}

void copyHeaders(HttpHeader* resHeaders, int count, HTTPClient& http) {
  for (int i = 0; i < count; i++) {
    String name = http.headerName(i);
    String value = http.header(i);

    strlcpy(resHeaders[i].name, name.c_str(), HEADER_NAME_LEN);
    strlcpy(resHeaders[i].value, value.c_str(), HEADER_VALUE_LEN);
  }
}

void setBaseHeaders(HTTPClient& http) {
  http.addHeader("Prefer", "return=minimal");

  http.addHeader("X-Api-Key", API_KEY);

  http.addHeader("X-DEVICE-ID", DEVICE_ID);
  http.addHeader("X-DEVICE-TYPE", DEVICE_TYPE);

  http.addHeader("X-DEVICE-CONTROLLER-TYPE", DEVICE_CONTROLLER_TYPE);

  uint64_t chipid = ESP.getEfuseMac();
  char chipIdStr[17];
  snprintf(chipIdStr, sizeof(chipIdStr), "%08X", (uint32_t)(chipid >> 32));
  http.addHeader("X-CHIP-ID", chipIdStr);


  http.addHeader("X-MAC", WiFi.macAddress());
  http.addHeader("X-APP-VERSION", APP_VERSION);

  char buf[64];

  // WIFI
  http.addHeader("X-WIFI-SSID", WiFi.SSID());

  snprintf(buf, sizeof(buf), "%d", WiFi.RSSI());
  http.addHeader("X-WIFI-RSSI", buf);
  // END WIFI

  snprintf(buf, sizeof(buf), "%lu", millis() / 1000);
  http.addHeader("X-UPTIME", buf);

  snprintf(buf, sizeof(buf), "%u", ESP.getFreeHeap());
  http.addHeader("X-FREE-HEAP", buf);

  snprintf(buf, sizeof(buf), "%u", ESP.getFreeSketchSpace());
  http.addHeader("X-FREE-SKETCH", buf);

  snprintf(buf, sizeof(buf), "%u", ESP.getFlashChipSize());
  http.addHeader("X-FLASH-SIZE", buf);

  time_t now = time(nullptr);
  snprintf(buf, sizeof(buf), "%ld", (long)now);
  http.addHeader("X-DEVICE-TIME", buf);
}

void printResponseHeaders(HTTPClient& http) {
  int count = http.headers();

  log_d("Headers count: %d", count);

  for (int i = 0; i < count; i++) {
    log_d("%s: %s", http.headerName(i).c_str(), http.header(i).c_str());
  }
}

void network_SetHeader(HttpHeader& header, const char* name, const char* value) {
  if (name == NULL) return;

  strlcpy(header.name, name, sizeof(header.name));
  strlcpy(header.value, value == NULL ? "" : value, sizeof(header.value));
}

void setupWifi(LiquidCrystal_I2C& lcd) {
  WiFiManager wm;

  if (WiFi.macAddress() == "00:00:00:00:00:00") {
    esp_wifi_set_mac(WIFI_IF_STA, customMAC);  // SETUP IN Config.h Sample: static const uint8_t customMAC[] = { 0xAC, 0x00, 0x00, 0x00, 0x00, 0x00 };
    delay(200);
  }

  drawText(lcd, "WiFi Connecting", 0, 0);

  wm.setConnectTimeout(120);  // 2 mins
  wm.setConfigPortalTimeout(300);

  // If the connection fails, the configurator will start
  if (!wm.autoConnect("SMART_CLOCK_AP", "12345678")) {

    log_i("Failed to connect, rebooting...");
    drawText(lcd, "Failed to connect", 0, 0);
    drawText(lcd, "rebooting...", 0, 0, 2000);

    ESP.restart();
  }

  drawText(lcd, "WiFi Connected!", 0, 0);
  drawText(lcd, WiFi.localIP().toString().c_str(), 0, 1, 2000);

  log_i("Connected to WiFi!/nIP: %s", WiFi.localIP().toString().c_str());
}
