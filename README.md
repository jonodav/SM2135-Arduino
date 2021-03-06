# SM2135 Arduino
Arduino library for interfacing with SM2135 LED drivers, based on code by Theo Arends for the tasmota firmware.

Only tested on a tuya based light bulb with a SM2135 driver, using a tuya tywe3 module (ESP8266). Please let me know if you have success on other platforms.


## Usage
### Include the library
```c++
#include <SM2135.h>
```

### Initialisation 
Declare an instance of the library:

```c++
SM2135 sm2135(uint8_t data, uint8_t clock);
```
Example: 
```c++
SM2135 sm2135(12, 14); // Pin 12 as data, pin 14 as clock
```
### Functions
Set the RGB values:
```c++
setRGB(uint8_t red, uint8_t green, uint8_t blue);
```
Example: 
```c++
setRGB(22, 255, 123); // Cyan
```

Set the white values:
```c++
setWhite(uint8_t warm, uint8_t cold);
```

Example: 
```c++
setWhite(255, 0); // 100% warm white
```
I'm not sure that the cool and warm white channels are the right way around in the library as my test device only has one white channel, so please file an issue if this is the case.

__Note that the driver will only turn on the RGB LEDs OR white LEDs at a time, so if you call setRGB and then setWhite, it will only turn the white LEDs on.__

### Full Example

```c++
#include <SM2135.h>

SM2135 sm2135(12, 14);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  sm2135.setRGB(220, 22, 120);
  delay(2000);
  sm2135.setWhite(220, 20);
  delay(2000);
}
```
