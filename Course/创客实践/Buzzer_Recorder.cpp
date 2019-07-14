#define BUZZER 9
#define BUTTON_RECORDER 6
#define LIGHT 13
#define BUTTON_C 1
#define BUTTON_D 2
#define BUTTON_E 3
#define NOTE_C 330
#define NOTE_D 350
#define NOTE_E 393
#define MAX_NOTES 100
#define RECORD_MODE 1
#define PLAYBACK_MODE 0
#define PRESSED 1
#define RELEASED 0
#define CLOCK_DELAY 30

long clocks = 0;

typedef struct Note {
	int button;
	int key;
	int len;
	Note() {
		button = 0;
		key = 0;
		len = 0;
	}
	Note(int _button, int _key, int _len) {
		button = _button;
		key = _key;
		len = _len;
	}
};

class Recorder {
      private:
	Note *notes;
	int mode;
	int storedCount;
	Note lastNote;

      public:
	Recorder() {
		defineMode();
		erase();
		lastNote = Note();
	}

	int Light(int pin, int status) {
		digitalWrite(pin, status);
	}

	int getButtonStatus(int pin) {
		if (digitalRead(pin) == HIGH)
			return RELEASED;
		else
			return PRESSED;
	}

	int defineMode() {
		mode = getButtonStatus(BUTTON_RECORDER) == PRESSED ? RECORD_MODE : PLAYBACK_MODE;
		return mode;
	}

	void addOneClock(Note note) {
		if (storedCount == MAX_NOTES)
			return;
		else {
			if (notes[storedCount].key == note.key) {
				notes[storedCount].len++;
				Buzzer(note);
			} else {
				storedCount++;
				notes[storedCount] = note;
				Buzzer(note);
			}
		}
	}

	void Buzzer(Note note) {
		Serial.println("Buzzer");
		if (note.key == 0) {
			noTone(lastNote.button);
			return;
		} else {
			if (lastNote.key != note.key) {
				noTone(lastNote.button);
				tone(BUZZER, note.key);
				lastNote = note;
			} else {
				lastNote = note;
			}
		}
	}

	void recordNext() {
		if (getButtonStatus(BUTTON_C) == PRESSED) {
			addOneClock(Note(BUTTON_C, NOTE_C, 0));
		} else if (getButtonStatus(BUTTON_D) == PRESSED) {
			addOneClock(Note(BUTTON_D, NOTE_D, 0));
		} else if (getButtonStatus(BUTTON_E) == PRESSED) {
			addOneClock(Note(BUTTON_E, NOTE_E, 0));
		} else {
			addOneClock(Note());
		}
	}

	void playNext() {
	}

	void erase() {
		delete notes;
		notes = new Note[MAX_NOTES];
		storedCount = 0;
	}

	void Operate() {
		Serial.println(mode);
		if (defineMode() == RECORD_MODE) {
			if (clocks % 50 < 25) {
				Light(LIGHT, 1);
			} else {
				Light(LIGHT, 0);
			}
			recordNext();
		} else if (defineMode() == PLAYBACK_MODE) {
			Light(LIGHT, 0);
		}
	}
};

void setup() {
	pinMode(BUTTON_C, INPUT_PULLUP);
	pinMode(BUTTON_D, INPUT_PULLUP);
	pinMode(BUTTON_E, INPUT_PULLUP);
	pinMode(BUTTON_RECORDER, INPUT_PULLUP);
	pinMode(BUZZER, OUTPUT);
	pinMode(BUTTON_RECORDER, OUTPUT);
	pinMode(LIGHT, OUTPUT);
	Serial.begin(115200);
}

Recorder recorder;

void loop() {
	clocks++;
	recorder.Operate();
	delay(CLOCK_DELAY);
}
