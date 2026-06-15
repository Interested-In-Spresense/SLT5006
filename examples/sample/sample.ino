/*
  * sample.ino - SLT5006 sensing sample
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

#include "SLT5006.h"

#define ENABLE_PIN 2

SLT5006 Sensor(Serial2, ENABLE_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  Serial.println("SLT5006 sample start");

  Sensor.begin();
  Sensor.enable();
  delay(1000);

  uint8_t major, minor, rev;
  if (Sensor.version(major, minor, rev)) {
    Serial.print("FW version: ");
    Serial.print(major); Serial.print(".");
    Serial.print(minor); Serial.print(".");
    Serial.println(rev);
  } else {
    Serial.println("version get failed");
  }

}

void loop() {
  if (!Sensor.send()) {
    Serial.println("send failed");
    delay(1000);
    return;
  }

  if (!Sensor.receive(5000)) {
    Serial.println("receive failed");
    delay(1000);
    return;
  }

  float t = Sensor.temp();
  float v = Sensor.vwc();
  float e = Sensor.ec_pore();

  Serial.print("Temp[degC]=");
  Serial.print(t, 4);
  Serial.print(", VWC[%]=");
  Serial.print(v, 1);
  Serial.print(", EC_PORE[dS/m]=");
  Serial.println(e, 3);

  delay(3000);
}
