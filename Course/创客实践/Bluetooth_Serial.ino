char inChar = 0; // for incoming serial data

void setup() { // opens serial port,
	// sets baud rate to 9600 bps
	Serial.begin(9600);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	digitalWrite(8, LOW);
	digitalWrite(9, LOW);
}

void loop() {
	// reply only when you receive data:
	if (Serial.available() > 0) {
		// read the incoming byte:
		inChar = Serial.read();
		if (inChar == 'R' || inChar == 'r') {
			digitalWrite(9, HIGH);
			digitalWrite(8, LOW);
		} else if (inChar == 'B' || inChar == 'b') {
			digitalWrite(8, HIGH);
			digitalWrite(9, LOW);
		}
	} else {
		digitalWrite(8, LOW);
		digitalWrite(9, LOW);
	}
}
