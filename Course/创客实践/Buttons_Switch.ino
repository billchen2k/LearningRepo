// the setup function runs once when you press reset or power the board
int buttonStatus;
int mode = 0;
int currentpos = 0;

void setup() {
  // initialize digital pin 13 as an output.
  for(int i = 7; i<= 12; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  pinMode(6, INPUT);
  buttonStatus = digitalRead(6);
}

void lightOnly(int id) {
  int i = 0;
  for (i = 7; i <= 13; i++) {
    if (i != id) {
      digitalWrite(i, LOW);
    } else {
      digitalWrite(i, HIGH);
    }
  }
}

void switcher(){
  if(mode == 0)
    mode = 1;
  else if(mode == 1)
    mode = 0;
}

// the loop function runs over and over again forever
void loop(){
  lightOnly(currentpos + 7);
  currentpos = (mode == 1) ? (currentpos - 1) : (currentpos + 1);
  if(currentpos == -1){
    currentpos = 4;
  }
  if(currentpos == 5){
    currentpos =0;
  }
  if (digitalRead(6) == HIGH && buttonStatus == LOW){
    switcher();
  }
  delay(300);
}