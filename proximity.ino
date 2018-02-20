#include <Adafruit_NeoPixel.h>
#include <NewPing.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


/* tweakable values */
#define THRESHOLD                 150

#define MILISECONDS_TO_REACT      100
#define MILISECONDS_TO_INTERACT   500
#define MILISECONDS_TO_LEAVE      300
#define MILISECONDS_DELAY         50


/* config values */
#define NEOLED_PIN                6
#define TRIGGER_PIN               3
#define ECHO_PIN                  2
#define LED_COUNT                 33
#define MAX_DISTANCE              200


/* magical values */
#define STATE_EMPTY 1
#define STATE_PASSING 2
#define STATE_THERE 3



NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, NEOLED_PIN, NEO_GRB + NEO_KHZ800);

/* global counters and state holder */
int state = STATE_EMPTY;
bool inRangeState = false;
int inRangeDuration = 0;
int goneDuration = 0;
int stayDuration = 0;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
}

bool isInRange() {
  int distance = sonar.convert_cm(sonar.ping_median());
  if (distance > 0 && distance < THRESHOLD) {
    inRangeDuration += MILISECONDS_DELAY;

    if (inRangeDuration > MILISECONDS_TO_REACT) {
      inRangeState = true;
      goneDuration = 0;
    }
  }
  if (distance >= THRESHOLD || distance == 0) {
    goneDuration += MILISECONDS_DELAY;
    if(goneDuration > MILISECONDS_TO_LEAVE) {
      inRangeState = false;
      inRangeDuration = 0;
    }
  }
  return inRangeState;
}

void runLights() {
   int brightness;
   switch(state) {
    case STATE_EMPTY:
      // turn off all lights
      colorSet(strip.Color(0,0,0));
      break;


    case STATE_PASSING:
      // light up yellow relative to stayDuration
      brightness = 255 * ((1.0 * stayDuration) / MILISECONDS_TO_INTERACT);
      colorSet(strip.Color(brightness, brightness, 0));
      break;


    case STATE_THERE:
      // set lights green
      colorSet(strip.Color(0,255,0));
      break;
  }
}
void runStateMachine() {
  bool inRange = isInRange();
  switch(state) {
    case STATE_EMPTY:
      if(inRange) {
        state = STATE_PASSING;
        Serial.write(1);
      }
      break;

    case STATE_PASSING:
      if(!inRange) {
        state = STATE_EMPTY;
        Serial.write(0);
        stayDuration = 0;
      } else {
        stayDuration += MILISECONDS_DELAY;
        if(stayDuration > MILISECONDS_TO_INTERACT) {
          state = STATE_THERE;
          Serial.write(2);
        }
      }
      break;
    case STATE_THERE:
     if(!inRange) {
        state = STATE_EMPTY;
        Serial.write(0);
        stayDuration = 0;
      }
      break;
  }
}

void loop() {
  runStateMachine();
  runLights();

  delay(MILISECONDS_DELAY);
}

void colorSet(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}
