/*
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Arduino.h"
#include "SM2135.h"

SM2135::SM2135(uint8_t dat, uint8_t clk) {
    pinMode(dat, OUTPUT);
    digitalWrite(dat, HIGH);
    pinMode(clk, OUTPUT);
    digitalWrite(clk, HIGH);
    _dat = dat;
    _clk = clk;
}

uint8_t SM2135::SM2135Write(uint8_t data) {
  for (uint32_t i = 0; i < 8; i++) {
    digitalWrite(_clk, LOW);
    digitalWrite(_dat, (data & 0x80));
    digitalWrite(_clk, HIGH);
    data = data << 1;
  }
  digitalWrite(_clk, LOW);
  digitalWrite(_dat, HIGH);
  pinMode(_dat, INPUT);
  digitalWrite(_clk, HIGH);
  uint8_t ack = digitalRead(_dat);
  pinMode(_dat, OUTPUT);
  return ack;
}


void SM2135::SM2135Send(uint8_t *buffer, uint8_t size) {
  digitalWrite(_dat, LOW);
  for (uint32_t i = 0; i < size; i++) {
    SM2135Write(buffer[i]);
  }
  digitalWrite(_clk, LOW);
  digitalWrite(_clk, HIGH);
  digitalWrite(_dat, HIGH);
}

void SM2135::setRGB(uint8_t red, uint8_t green, uint8_t blue) {
  if(red != _lastRed || green != _lastGreen || blue != _lastBlue || !lastSetRGB) { //Only run if data has changed or driver was last set to white
    _lastRed = red;
    _lastGreen = green;
    _lastBlue = blue;
    lastSetRGB = true;
    uint8_t data[6];
    // Color
    /*
        if ((cur_col[0] + cur_col[1] + cur_col[2]) >= (3 * 256)) {
          // Scale down to 765 total to fix max power usage of 9W
          // Currently not needed with setting 3 x 15mA = 45mA = 11W = 765
        }
    */
    data[0] = SM2135_ADDR_MC;
    data[1] = SM2135_CURRENT;
    data[2] = SM2135_RGB;
    data[3] = blue;  // Green
    data[4] = green;  // Red
    data[5] = red;  // Blue
    SM2135Send(data, 6);
  }
}

void SM2135::setWhite(uint8_t warm, uint8_t cold) {
  if(warm != _lastWarm || cold != _lastCold || lastSetRGB) { //Only run if data has changed or driver was last set to RGB
    _lastWarm = warm;
    _lastCold = cold;
    lastSetRGB = false;
    uint8_t data[6];
    data[0] = SM2135_ADDR_MC;
    data[1] = SM2135_CURRENT;
    data[2] = SM2135_CW;
    SM2135Send(data, 3);
    delay(1);
    data[0] = SM2135_ADDR_C;
    data[1] = cold;  // Cold
    data[2] = warm;  // Warm
    SM2135Send(data, 3);
  }
}