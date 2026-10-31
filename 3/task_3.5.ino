const int rows[4] = {9, 8, 7, 6};
const int cols[4] = {5, 4, 3, 2};
const int yellowLed = 10;
const int greenLed = 11;
const int redLed = 12;
char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
String password = "1234";
String enteredPassword = "";
int attempts = 0;
bool locked = false;
unsigned long lockTime = 0;
char readKey() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(rows[i], LOW);
    for (int j = 0; j < 4; j++) {
      if (digitalRead(cols[j]) == LOW) {
        delay(50);
        if (digitalRead(cols[j]) == LOW) {
          char key = keys[i][j];

          while (digitalRead(cols[j]) == LOW) {
          }
          digitalWrite(rows[i], HIGH);
          return key;
        }
      }
    }
    digitalWrite(rows[i], HIGH);
  }
  return 0;
}
void checkPassword() {
  if (enteredPassword == password) {
    digitalWrite(greenLed, HIGH);
    delay(3000);
    digitalWrite(greenLed, LOW);
    attempts = 0;
  } else {
    attempts++;
    for (int i = 0; i < 3; i++) {
      digitalWrite(redLed, HIGH);
      delay(300);
      digitalWrite(redLed, LOW);
      delay(300);
    }
    if (attempts >= 3) {
      locked = true;
      lockTime = millis();
    }
  }
  enteredPassword = "";
}
void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], HIGH);
    pinMode(cols[i], INPUT_PULLUP);
  }
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
}
void loop() {
  if (locked) {
    if (millis() - lockTime >= 10000) {
      locked = false;
      attempts = 0;
    } else {
      return;
    }
  }
  char key = readKey();
  if (key != 0) {
    if (key == '*') {
      enteredPassword = "";
    } else if (key == '#') {
      if (enteredPassword.length() > 0) {
        checkPassword();
      }
    } else if (key >= '0' && key <= '9') {
      if (enteredPassword.length() < 4) {
        enteredPassword += key;
        digitalWrite(yellowLed, HIGH);
        delay(100);
        digitalWrite(yellowLed, LOW);
      }
      if (enteredPassword.length() == 4) {
        checkPassword();
      }
    }
  }
}
