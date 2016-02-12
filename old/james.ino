#include "Adafruit_WS2801.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
#include <avr/power.h>
#endif

/*****************************************************************************
Example sketch for driving Adafruit WS2801 pixels!


  Designed specifically to work with the Adafruit RGB Pixels!
  12mm Bullet shape ----> https://www.adafruit.com/products/322
  12mm Flat shape   ----> https://www.adafruit.com/products/738
  36mm Square shape ----> https://www.adafruit.com/products/683

  These pixels use SPI to transmit the color data, and have built in
  high speed PWM drivers for 24 bit color per pixel
  2 pins are required to interface

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution

*****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
uint8_t dataPin  = 2;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 3;    // Green wire on Adafruit Pixels

const int rightDoor = 6;
const int leftDoor  = 7;

int leftDoorState = 0;
int rightDoorState = 0;
int previousLeftDoorState = 0;
int previousRightDoorState = 0;

int i = 0;
int closed = 0;
int opened = 1;

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin);

// Optional: leave off pin numbers to use hardware SPI
// (pinout is then specific to each board and can't be changed)
//Adafruit_WS2801 strip = Adafruit_WS2801(25);

// For 36mm LED pixels: these pixels internally represent color in a
// different format.  Either of the above constructors can accept an
// optional extra parameter: WS2801_RGB is 'conventional' RGB order
// WS2801_GRB is the GRB order required by the 36mm pixels.  Other
// than this parameter, your code does not need to do anything different;
// the library will handle the format change.  Examples:
//Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin, WS2801_GRB);
//Adafruit_WS2801 strip = Adafruit_WS2801(25, WS2801_GRB);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  pinMode(leftDoor, INPUT);
  pinMode(rightDoor, INPUT);

  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
}


void loop() {
  // Some example procedures showing how to display to the pixels

  rightDoorState = digitalRead(rightDoor);
  leftDoorState = digitalRead(leftDoor);

  if ((leftDoorState == LOW) & (rightDoorState == LOW) & (previousLeftDoorState == closed) & (previousRightDoorState == closed)) {
    for (i = 0; i < 41; i++)
    {
      setRightTop(Color(i*6, i*3, i), 5);
      setRightMiddle(Color(i*6, i*3, i), 5);
      setRightBottom(Color(i*6, i*3, i), 5);

      setLeftTop(Color(i*6, i*3, i), 5);
      setLeftMiddle(Color(i*6, i*3, i), 5);
      setLeftBottom(Color(i*6, i*3, i), 5);
    }
    previousLeftDoorState = opened;
    previousRightDoorState = opened;
  }
  else if ((leftDoorState == LOW) & (rightDoorState == LOW) & (previousLeftDoorState == opened) & (previousRightDoorState == closed)) {
    for (i = 0; i < 41; i++)
    {
      setRightTop(Color(i*6, i*3, i), 0);
      setRightMiddle(Color(i*6, i*3, i), 0);
      setRightBottom(Color(i*6, i*3, i), 0);
    }
    previousLeftDoorState = opened;
    previousRightDoorState = opened;
  }
  else if ((leftDoorState == LOW) & (rightDoorState == LOW) & (previousLeftDoorState == closed) & (previousRightDoorState == opened)) {
    for (i = 0; i < 41; i++)
    {
      setLeftTop(Color(i*6, i*3, i), 0);
      setLeftMiddle(Color(i*6, i*3, i), 0);
      setLeftBottom(Color(i*6, i*3, i), 0);
    }
    previousLeftDoorState = opened;
    previousRightDoorState = opened;
  }
  else if ((leftDoorState == HIGH) & (rightDoorState == HIGH)) {
    setRightTop(Color(0, 0, 0), 0);
    setLeftTop(Color(0, 0, 0), 0);
    setRightMiddle(Color(0, 0, 0), 0);
    setLeftMiddle(Color(0, 0, 0), 0);
    setRightBottom(Color(0, 0, 0), 0);
    setLeftBottom(Color(0, 0, 0), 0);

    previousLeftDoorState = closed;
    previousRightDoorState = closed;
  }
  else if ((leftDoorState == LOW) & (rightDoorState == HIGH) & (previousLeftDoorState == closed) & (previousRightDoorState == closed)) {
    for (i = 0; i < 41; i++)
    {
      setLeftTop(Color(i*6, i*3, i), 0);
      setLeftMiddle(Color(i*6, i*3, i), 0);
      setLeftBottom(Color(i*6, i*3, i), 0);
    }
    previousLeftDoorState = opened;
    previousRightDoorState = closed;
  }

  else if ((leftDoorState == HIGH) & (rightDoorState == LOW) & (previousRightDoorState == closed) & (previousLeftDoorState == closed)) {
    for (i = 0; i < 41; i++)
    {
      setRightTop(Color(i*6, i*3, i), 0);
      setRightMiddle(Color(i*6, i*3, i), 0);
      setRightBottom(Color(i*6, i*3, i), 0);

    }
    previousLeftDoorState = closed;
    previousRightDoorState = opened;
  }
  else if ((leftDoorState == LOW) & (rightDoorState == HIGH) & (previousLeftDoorState == closed) & (previousRightDoorState == opened)) {
    for (i = 0; i < 41; i++)
    {
      setLeftTop(Color(i*6, i*3, i), 0);
      setLeftMiddle(Color(i*6, i*3, i), 0);
      setLeftBottom(Color(i*6, i*3, i), 0);
    }
    setRightTop(Color(0, 0, 0), 0);
    delay(250);
    setRightMiddle(Color(0, 0, 0), 0);
    delay(250);
    setRightBottom(Color(0, 0, 0), 0);

    previousLeftDoorState = opened;
    previousRightDoorState = closed;
  }
  else if ((leftDoorState == HIGH) & (rightDoorState == LOW) & (previousLeftDoorState == opened) & (previousRightDoorState == closed)) {
    for (i = 0; i < 41; i++)
    {
      setRightTop(Color(i*6, i*3, i), 0);
      setRightMiddle(Color(i*6, i*3, i), 0);
      setRightBottom(Color(i*6, i*3, i), 0);

    }
    setLeftTop(Color(0, 0, 0), 0);
    delay(250);
    setLeftMiddle(Color(0, 0, 0), 0);
    delay(250);
    setLeftBottom(Color(0, 0, 0), 0);

    previousLeftDoorState = closed;
    previousRightDoorState = opened;
  }
  else if ((leftDoorState == HIGH) & (rightDoorState == LOW) & (previousRightDoorState == opened) & (previousLeftDoorState == opened)) {
    setLeftTop(Color(0, 0, 0), 0);
    delay(250);
    setLeftMiddle(Color(0, 0, 0), 0);
    delay(250);
    setLeftBottom(Color(0, 0, 0), 0);

    previousLeftDoorState = closed;
  }
  else if ((leftDoorState == LOW) & (rightDoorState == HIGH) & (previousRightDoorState == opened) & (previousLeftDoorState == opened)) {
    setRightTop(Color(0, 0, 0), 0);
    delay(250);
    setRightMiddle(Color(0, 0, 0), 0);
    delay(250);
    setRightBottom(Color(0, 0, 0), 0);

    previousRightDoorState = closed;
  }
}

void setRightTop(uint32_t c, uint8_t wait) {
  strip.setPixelColor(0, c);
  strip.setPixelColor(1, c);
  strip.setPixelColor(2, c);
  strip.show();
  delay(wait);
}
void setRightMiddle(uint32_t c, uint8_t wait) {
  strip.setPixelColor(9, c);
  strip.setPixelColor(10, c);
  strip.setPixelColor(11, c);
  strip.show();
  delay(wait);
}
void setRightBottom(uint32_t c, uint8_t wait) {
  strip.setPixelColor(12, c);
  strip.setPixelColor(13, c);
  strip.setPixelColor(14, c);
  strip.show();
  delay(wait);
}

void setLeftTop(uint32_t c, uint8_t wait) {
  strip.setPixelColor(3, c);
  strip.setPixelColor(4, c);
  strip.setPixelColor(5, c);
  strip.show();
  delay(wait);
}
void setLeftMiddle(uint32_t c, uint8_t wait) {
  strip.setPixelColor(6, c);
  strip.setPixelColor(7, c);
  strip.setPixelColor(8, c);
  strip.show();
  delay(wait);
}
void setLeftBottom(uint32_t c, uint8_t wait) {
  strip.setPixelColor(15, c);
  strip.setPixelColor(16, c);
  strip.setPixelColor(17, c);
  strip.show();
  delay(wait);
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}
