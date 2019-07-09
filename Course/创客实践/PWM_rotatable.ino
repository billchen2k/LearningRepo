// the setup function runs once when you press reset or power the board

void setup() {
	// initialize digital pin 13 as an output.
	pinMode(9, OUTPUT);
	analogWrite(9, 100);
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);

	pinMode(6, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
    if(digitalRead(6) == HIGH){
	    int val = analogRead(A3);
	    val = map(val, 0, 1023, 0, 255);
	    analogWrite(9, val);
    }
    else{
	    analogWrite(9, 1024);
    }
}