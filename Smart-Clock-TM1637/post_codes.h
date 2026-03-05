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

#pragma once

enum PostCode {
  POST_TM1637_INITIALIZED = 8000,

  POST_EMPTY_MAC_ADDRESS = 8100,
  POST_WIFI_CONNECTING,
  POST_WIFI_CONNECTION_FAILED,
  POST_WIFI_CONNECTED,
  POST_WIFI_CONNECTION_LOST,

  POST_RESPONSE_DEVICE_ID_OR_API_KEY_NOT_FOUND = 8201,
  POST_RESPONSE_UNEXPECTED_CODE = 9000,
  
  POST_OK = 8888,
};