void setup() {
  Serial.begin(115200);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  analogWrite(9, 100);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

}

void loop() {
    int val = analogRead(A3);
    
    int valR, valG, valB;
    valG = map(val, 600, 100, 100, 0);
    valR = map(val, 600, 100, 0, 110);
    Serial.println(valR);
    analogWrite(10, valG);
    analogWrite(9, valR);
    delay(10);
}
