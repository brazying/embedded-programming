const int button = 7;
const int led1 = 12;
const int led2 = 11;
int ledState = LOW;
int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long pressTime = 0;
unsigned long timer = 0;
unsigned long led2Time = 0;
bool longPress = false;
bool led2Active = false;
void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}
void loop() {
  int reading = digitalRead(button);
  if (reading != lastButtonState) {
    timer = millis();
  }
  if (millis() - timer > 50) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        pressTime = millis();
        longPress = false;
      }
      if (buttonState == HIGH) {
        if (!longPress && millis() - pressTime < 500) {
          ledState = !ledState;
          digitalWrite(led1, ledState);
        }
      }
    }
  }
  if (buttonState == LOW && !longPress) {
    if (millis() - pressTime >= 1000) {
      longPress = true;
      led2Active = true;
      led2Time = millis();
      digitalWrite(led2, HIGH);
    }
  }
  if (led2Active && millis() - led2Time >= 3000) {
    led2Active = false;
    digitalWrite(led2, LOW);
  }
  lastButtonState = reading;
}
