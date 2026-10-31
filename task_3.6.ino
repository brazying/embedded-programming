const int sensor = 2;
const int greenLed = 11;
const int redLed = 12;
int lastState = HIGH;
int stableState = HIGH;
int normalState = HIGH;
int switchCount = 0;
unsigned long changeTime = 0;
unsigned long windowTime = 0;
unsigned long vibrationTime = 0;
unsigned long blinkTime = 0;
bool vibration = false;
bool redState = false;
void setup() {
  pinMode(sensor, INPUT_PULLUP);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  Serial.begin(9600);
  lastState = digitalRead(sensor);
  stableState = lastState;
  normalState = lastState;
  changeTime = millis();
  windowTime = millis();
}
void loop() {
  unsigned long now = millis();
  int state = digitalRead(sensor);
  if (state != lastState) {
    lastState = state;
    changeTime = now;
    switchCount++;
  }
  if (now - windowTime >= 1000) {
    Serial.print("Switches: ");
    Serial.println(switchCount);
    if (switchCount > 5) {
      vibration = true;
      vibrationTime = now;
      blinkTime = now;
      redState = true;
      digitalWrite(redLed, HIGH);
      Serial.println("Vibration detected");
    }
    switchCount = 0;
    windowTime = now;
  }
  if (vibration) {
    if (now - vibrationTime >= 2000) {
      vibration = false;
      redState = false;
      digitalWrite(redLed, LOW);
    } else if (now - blinkTime >= 200) {
      redState = !redState;
      digitalWrite(redLed, redState);
      blinkTime = now;
    }
  }
  if (!vibration && state != stableState && now - changeTime >= 300) {
    stableState = state;
    if (stableState != normalState) {
      digitalWrite(greenLed, HIGH);
      Serial.println("Tilt detected");
    } else {
      digitalWrite(greenLed, LOW);
      Serial.println("Normal position");
    }
  }
}
