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

unsigned char left_value = 255;
unsigned char right_value = 255;
char left_delta = 0;
char right_delta = 0;

void check_buttons() {
  left.update();
  right.update();
  if (left.fell()) {
    left_delta = 1;
  } else if (left.rose()) {
    left_delta = -1;
  }
  if (right.fell()) {
    right_delta = 1;
  } else if (right.rose()) {
    right_delta = -1;
  }
}

void run_deltas() {
  left_value = constrain(left_value + left_delta, 0, 255);
  right_value = constrain(right_value + right_delta, 0, 255);
  for (int shelf = 0; shelf < NUM_SHELVES; shelf++) {
    for (int i = 0; i < NUM_LEDS / NUM_SHELVES / 2; i++) {
      char led_num_left = LED_SHELVES_LEFT[shelf][i];
      leds[led_num_left] = CHSV(0, 0, left_value);
      char led_num_right = LED_SHELVES_RIGHT[shelf][i];
      leds[led_num_right] = CHSV(0, 0, right_value);
    }
  }
}

void setup() {
  pinMode(PIN_LEFT, INPUT_PULLUP);
  pinMode(PIN_RIGHT, INPUT_PULLUP);
  left.attach(PIN_LEFT);
  right.attach(PIN_RIGHT);

  FastLED.addLeds<WS2801, PIN_DATA, PIN_CLOCK>(leds, NUM_LEDS);
}

void loop() {
  check_buttons();
  run_deltas();
  FastLED.show();
  delay(3);
}
