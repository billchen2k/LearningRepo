#define BUZZER 11
#define BUTTON_RECORDER 9
#define NOTE_C 330
#define NOTE_D 350
#define NODE_E 393
#define RECORD_MODE 1
#define PLAYBACK_MODE 0
#define PRESSED 1
#define RELEASED 0
#define CLOCK 30

typedef struct Note {
  int key;
  int len;
};



class Recorder {
  Note* notes;
  int mode = RECORD_MODE;
  Recorder() { 
	  notes = new Note[100]; 
  }

  int getButtonStatus(int pin) {
  if (digitalRead(pin) == HIGH)
    return RELEASED;
  else
    return PRESSED;
} 
  void defineMode(){
	mode = getButtonStatus(BUTTON_RECORDER) == PRESSED ? RECORD_MODE : PLAYBACK_MODE;
  }

  void Record(){

  }
};

void setup() {
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON_RECORDER, OUTPUT);
}

void loop() {}
