# SM2135-Arduino
Arduino library for interfacing with SM2135 LED drivers, based upon code by Theo Arends for the tasmota firmware


## Usage
### Include the library
```c++
#include <SM2135.h>
```

### Initialisation 
Declare an instance of the library:

```c++
SM2135 sm2135(uint8_t dat, uint8_t clk);
```
Example: 
```c++
SM2135 sm2135(12, 14);
```
### Functions
Set the RGB values:
```c++
setRGB(uint8_t red, uint8_t green, uint8_t blue);
```
Example: 
```c++
setRGB(22, 255, 123); //Cyan
```

Set the white valuse:
```c++
setWhite(uint8_t warm, uint8_t cold);
```

Example: 
```c++
setWhite(255, 0); // 100% warm white)
```

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
  sm2135.setWhite(220, 20);
}
```
**Note that the driver will only turn on the RGB leds OR white LEDs at a time, so if you call setRGB and then setWhite, it will only turn the white LEDs on. **
