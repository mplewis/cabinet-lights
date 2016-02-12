#include <Bounce2.h>
#include <FastLED.h>

const char PIN_DATA = 2;
const char PIN_CLOCK = 3;
const char PIN_LEFT = 6;
const char PIN_RIGHT = 7;

const int NUM_LEDS = 18;
const int LEDS_LEFT[] = {0, 1, 2, 9, 10, 11, 12, 13, 14};
const int LEDS_RIGHT[] = {3, 4, 5, 6, 7, 8, 15, 16, 17};

Bounce left = Bounce();
Bounce right = Bounce();
CRGB leds[NUM_LEDS];

void setLeds(bool isLeft, CRGB color) {
  const int *toSet;
  if (isLeft) {
    toSet = LEDS_LEFT;
  } else {
    toSet = LEDS_RIGHT;
  }
  for (int i = 0; i < NUM_LEDS / 2; i++) {
    leds[toSet[i]] = color;
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
  FastLED.addLeds<WS2801, PIN_DATA, PIN_CLOCK>(leds, NUM_LEDS);
  setLeft(CRGB::Red);
  setRight(CRGB::Red);
  FastLED.show();
  delay(2000);
}

void loop() {
  left.update();
  right.update();
  if (!digitalRead(PIN_LEFT)) {
    setLeft(CRGB::White);
  } else {
    setLeft(CRGB::Black);
  }
  if (!digitalRead(PIN_RIGHT)) {
    setRight(CRGB::White);
  } else {
    setRight(CRGB::Black);
  }
  FastLED.show();
}
