void setup() {
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	Serial.begin(115200);
	digitalWrite(13, LOW);
}
int clock = 0;
void loop() {
	clock = (clock > 10000) ? -0 : clock + 1;

	int valCube = (clock % 10 < 5) ? 255 : 0;
	int valSin = (1 + sin((double)clock / 3.0)) * 255;
	analogWrite(12, valCube);
	//delay(1);

	Serial.println(clock);
}
