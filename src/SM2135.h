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

#ifndef SM2135_h
#define SM2135_h

#define SM2135_ADDR_MC      0xC0  // Max current register
#define SM2135_ADDR_CH      0xC1  // RGB or CW channel select register
#define SM2135_ADDR_R       0xC2  // Red color
#define SM2135_ADDR_G       0xC3  // Green color
#define SM2135_ADDR_B       0xC4  // Blue color
#define SM2135_ADDR_C       0xC5  // Cold
#define SM2135_ADDR_W       0xC6  // Warm

#define SM2135_RGB          0x00  // RGB channel
#define SM2135_CW           0x80  // CW channel (Chip default)

#define SM2135_10MA         0x00
#define SM2135_15MA         0x01
#define SM2135_20MA         0x02  // RGB max current (Chip default)
#define SM2135_25MA         0x03
#define SM2135_30MA         0x04  // CW max current (Chip default)
#define SM2135_35MA         0x05
#define SM2135_40MA         0x06
#define SM2135_45MA         0x07  // Max value for RGB
#define SM2135_50MA         0x08
#define SM2135_55MA         0x09
#define SM2135_60MA         0x0A

const uint8_t SM2135_CURRENT = (SM2135_20MA << 4) | SM2135_15MA;  // See https://github.com/arendst/Tasmota/issues/6495#issuecomment-549121683

class SM2135 {
    public: 
        SM2135(uint8_t dat, uint8_t clk);
        void setWhite(uint8_t warm, uint8_t cold);
        void setRGB(uint8_t red, uint8_t green, uint8_t blue);
    private:
        uint8_t SM2135Write(uint8_t data);
        void SM2135Send(uint8_t *buffer, uint8_t size);
        uint8_t _dat;
        uint8_t _clk; 
};

#endif