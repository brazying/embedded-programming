const int carRed = 2;
const int carYellow = 3;
const int carGreen = 4;
const int pedRed = 5;
const int pedGreen = 6;
const int button = 7;
void setup() {
  pinMode(carRed, OUTPUT);
  pinMode(carYellow, OUTPUT);
  pinMode(carGreen, OUTPUT);
  pinMode(pedRed, OUTPUT);
  pinMode(pedGreen, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  digitalWrite(carGreen, HIGH);
  digitalWrite(pedRed, HIGH);
}
void loop() {
  if (digitalRead(button) == LOW) {
    delay(50);
    if (digitalRead(button) == LOW) {
      for (int i = 0; i < 3; i++) {
        digitalWrite(carGreen, LOW);
        delay(300);
        digitalWrite(carGreen, HIGH);
        delay(300);
      }
      digitalWrite(carGreen, LOW);
      digitalWrite(carYellow, HIGH);
      delay(2000);
      digitalWrite(carYellow, LOW);
      digitalWrite(carRed, HIGH);
      delay(500);
      digitalWrite(pedRed, LOW);
      digitalWrite(pedGreen, HIGH);
      delay(5000);
      for (int i = 0; i < 3; i++) {
        digitalWrite(pedGreen, LOW);
        delay(300);
        digitalWrite(pedGreen, HIGH);
        delay(300);
      }
      digitalWrite(pedGreen, LOW);
      digitalWrite(pedRed, HIGH);
      digitalWrite(carRed, LOW);
      digitalWrite(carGreen, HIGH);
      while (digitalRead(button) == LOW) {
        delay(10);
      }
    }
  }
}
