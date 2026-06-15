/*
*  SLT5006.h - Murata Soil Sensor (SLT5006) driver for Spresense.
 *  Author Interested-In-Spresense
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#pragma once

#include <Arduino.h>

class SLT5006
{
public:
  explicit SLT5006(HardwareSerial &serial = Serial2, uint8_t enablePin = 2);
  void begin();
  void end();

  bool enable();
  bool disable();

  bool state();
  bool version(uint8_t &major, uint8_t &minor, uint8_t &rev);
  bool send();
  bool receive(uint32_t timeoutMs);

  float temp();
  float vwc();
  float ec_pore();

private:

  typedef struct SensorPacket_s {
    uint8_t addr;
    uint8_t size;
    uint32_t data;

    float temp() const;
    float vwc() const;
    float ec_pore() const;
  } SensorPacket;

  void write(SensorPacket);
  void read(SensorPacket);
  bool receive(SensorPacket *);

  uint16_t calc(uint16_t, uint8_t);

  static const uint32_t kSensorFixedBaud = 9600;
  static const uint32_t kDefaultTimeoutMs = 5000;

  HardwareSerial *_serial;
  uint8_t _enablePin;
  uint32_t _timeoutMs = kDefaultTimeoutMs;

  void clear();
  size_t get(uint8_t *buf, size_t bufSize, uint32_t timeoutMs);

};
