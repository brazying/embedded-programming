unsigned long startTime;
unsigned long endTime;
unsigned long digitalTime;
unsigned long registerTime;
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  startTime = micros();
  for (int i = 0; i < 100000; i++) {
    digitalWrite(13, HIGH);
    digitalWrite(13, LOW);
  }
  endTime = micros();
  digitalTime = endTime - startTime;
  startTime = micros();
  for (int i = 0; i < 100000; i++) {
    PORTB |= (1 << PB5);
    PORTB &= ~(1 << PB5);
  }
  endTime = micros();
  registerTime = endTime - startTime;
  Serial.print("digitalWrite time: ");
  Serial.println(digitalTime);
  Serial.print("PORTB time: ");
  Serial.println(registerTime);
  Serial.print("Speed difference: ");
  Serial.println((float)digitalTime / registerTime);
  Serial.print("digitalWrite frequency: ");
  Serial.println(100000.0 / (digitalTime / 1000000.0));
  Serial.print("PORTB frequency: ");
  Serial.println(100000.0 / (registerTime / 1000000.0));
}
void loop() {
}
