#include <Bounce2.h>
#include <FastLED.h>

const char PIN_DATA = 2;
const char PIN_CLOCK = 3;
const char PIN_LEFT = 6;
const char PIN_RIGHT = 7;

const int NUM_LEDS = 18;
const int NUM_SHELVES = 3;
const int LED_SHELVES_LEFT[3][3] = {{0, 1, 2}, {9, 10, 11}, {12, 13, 14}};
const int LED_SHELVES_RIGHT[3][3] = {{3, 4, 5}, {6, 7, 8}, {15, 16, 17}};

Bounce left = Bounce();
Bounce right = Bounce();
CRGB leds[NUM_LEDS];

void setLeds(bool isLeft, CRGB color) {
  for (int shelf = 0; shelf < NUM_SHELVES; shelf++) {
    for (int i = 0; i < NUM_LEDS / NUM_SHELVES / 2; i++) {
      if (isLeft) {
        leds[LED_SHELVES_LEFT[shelf][i]] = color;
      } else {
        leds[LED_SHELVES_RIGHT[shelf][i]] = color;
      }
    }
  }
}

void setLeft(CRGB color) {
  setLeds(true, color);
}

void setRight(CRGB color) {
  setLeds(false, color);
}

void setup() {
  pinMode(PIN_LEFT, INPUT_PULLUP);
  pinMode(PIN_RIGHT, INPUT_PULLUP);
  left.attach(PIN_LEFT);
  right.attach(PIN_RIGHT);

  FastLED.addLeds<WS2801, PIN_DATA, PIN_CLOCK>(leds, NUM_LEDS);
}

void loop() {
  left.update();
  right.update();
  if (left.fell()) {
    setLeft(CRGB::White);
  } else if (left.rose()) {
    setLeft(CRGB::Black);
  }
  if (!digitalRead(PIN_RIGHT)) {
    setRight(CRGB::White);
  } else {
    setRight(CRGB::Black);
  }
  FastLED.show();
}
