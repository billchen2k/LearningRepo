// the setup function runs once when you press reset or power the board
int buttonStatus;

void setup()
{
	// initialize digital pin 13 as an output.
	pinMode(12, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(6, INPUT);
	digitalWrite(9, LOW);
	digitalWrite(12, HIGH);
	buttonStatus = digitalRead(6);
}

void switcher(int id)
{
	int status = digitalRead(id);
	if (status == HIGH)
	{
		digitalWrite(id, LOW);
	}
	else
	{
		digitalWrite(id, HIGH);
	}
}
// the loop function runs over and over again forever
void loop(){

	if (digitaRead(6) == LOW && buttonStatus == HIGH)
	{
		switcher(6);
	}
	buttonStatus = digitalRead(6);
}