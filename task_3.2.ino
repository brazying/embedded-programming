const int led = 12;
const int button = 7;
int ledState = LOW;
int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long timer = 0;
int counter = 0;
void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
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
        ledState = !ledState;
        digitalWrite(led, ledState);
        counter++;
        Serial.println(counter);
      }
    }
  }
  lastButtonState = reading;
}
