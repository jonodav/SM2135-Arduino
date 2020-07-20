#include <SM2135.h>

SM2135 sm2135(12, 14); //Pin 12 as data, pin 14 as clock

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  sm2135.setRGB(255, 0, 0); //Sets red color
}
