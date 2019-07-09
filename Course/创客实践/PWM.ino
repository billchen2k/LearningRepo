// the setup function runs once when you press reset or power the board
int buttonStatus1;
int buttonStatus2;
int value = 100;

void buckAW(int mode, int offset) {
	if (mode == 1) {
		if (value + offset <= 255) {
			value += offset;
			for (int i = 9; i <= 11; i++) {
				analogWrite(i, value);
			}
		}
	}
    else{
		if (value - offset >= 0) {
			value -= offset;
			for (int i = 9; i <= 11; i++) {
				analogWrite(i, value);
			}
		}
    }
}

void setup() {
	// initialize digital pin 13 as an output.
	for (int i = 7; i <= 12; i++) {
		pinMode(i, OUTPUT);
	}
	pinMode(3, OUTPUT);
	digitalWrite(3, HIGH);
	pinMode(4, OUTPUT);
	digitalWrite(4, HIGH);
	pinMode(6, INPUT);
	buttonStatus1 = digitalRead(6);
	pinMode(5, INPUT);
	buttonStatus2 = digitalRead(5);
}


// the loop function runs over and over again forever
void loop() {
	if (digitalRead(6) == HIGH && buttonStatus1 == LOW) {
		buckAW(1, 10);
		
	}
	buttonStatus1 = digitalRead(6);
	if (digitalRead(5) == HIGH && buttonStatus2 == LOW) {
		buckAW(0, 10);
	}
	buttonStatus2 = digitalRead(5);
	delay(10);
}