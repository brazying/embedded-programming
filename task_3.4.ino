const int leds[] = {2, 3, 4, 5, 6, 7};
const int LED_COUNT = sizeof(leds) / sizeof(leds[0]);
const int button = 8;
int effect = 0;
int position = 0;
bool direction = true;
int lastReading = HIGH;
int buttonState = HIGH;
unsigned long debounceTimer = 0;
unsigned long effectTimer = 0;
void clearLeds() {
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(leds[i], LOW);
  }
}
void effectOne() {
  clearLeds();
  digitalWrite(leds[position], HIGH);
  position++;
  if (position >= LED_COUNT) {
    position = 0;
  }
}
void effectTwo() {
  clearLeds();
  digitalWrite(leds[position], HIGH);
  digitalWrite(leds[LED_COUNT - 1 - position], HIGH);
  position++;
  if (position >= (LED_COUNT + 1) / 2) {
    position = 0;
  }
}
void effectThree() {
  digitalWrite(leds[position], direction ? HIGH : LOW);
  position++;
  if (position >= LED_COUNT) {
    position = 0;
    direction = !direction;
  }
}
void setup() {
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(button, INPUT_PULLUP);
  clearLeds();
}
void loop() {
  int reading = digitalRead(button);

  if (reading != lastReading) {
    debounceTimer = millis();
  }
  if (millis() - debounceTimer > 50) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        effect++;
        if (effect > 2) {
          effect = 0;
        }
        position = 0;
        direction = true;
        clearLeds();
      }
    }
  }
  lastReading = reading;
  if (millis() - effectTimer >= 200) {
    effectTimer = millis();
    if (effect == 0) {
      effectOne();
    } else if (effect == 1) {
      effectTwo();
    } else {
      effectThree();
    }
  }
}
