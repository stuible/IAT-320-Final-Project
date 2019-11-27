import java.util.Map;

int activeObject = 0;

HashMap<String, Integer> objects = new HashMap<String, Integer>();

void setup() {
  size(640, 360);
  background(255);

  setupSerial();

  setupOldschoolRadio();
  setupPortableRadio();
  setupMP3Player();
  setupPhone();

  setupSound();
}      

void draw() {
  updateSerial();
}

void changeObject(int index) {
  activeObject = index;

  if (activeObject == objects.get("oldschoolRadio")) {
  }
  else if (activeObject == objects.get("portableRadio")) {
  }
  else if (activeObject == objects.get("MP3Player")) {
  }
  else if (activeObject == objects.get("phone")) {
    loadPhoneSong();
  }
}
