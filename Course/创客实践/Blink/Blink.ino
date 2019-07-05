// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
}

void lightOnly(int id) {
  int i = 0;
  for (i = 1; i <= 13; i++) {
    if (i != id) {
      digitalWrite(i, LOW);
    }
    else {
      digitalWrite(i, HIGH);
    }
  }
}
// the loop function runs over and over again forever
void loop() {
  int i;
  for (i = 7; i <= 13; i + 2) {
    lightOnly(i);
    delay(200);
  }
}
