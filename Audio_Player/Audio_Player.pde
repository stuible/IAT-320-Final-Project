import java.util.Map;

// Defines index of currently active object
int activeObject = -1;

// Serial port that Arduino Base is connected to
int serialPort = 21;

// Hash map containing all 4 objects
HashMap<String, Integer> objects = new HashMap<String, Integer>();

void setup() {
  size(640, 360);
  background(255);

  // Run all object, serial and sound helper functions
  setupSerial();

  setupOldschoolRadio();
  setupPortableRadio();
  setupMP3Player();
  setupPhone();

  setupSound();
}      

void draw() {
  // Grab latest serial data from port
  updateSerial();
}

// Handles when active object changes
void changeObject(int index) {
  activeObject = index;

  if (activeObject == objects.get("oldschoolRadio")) {
    loadOldschoolRadioSong();
  } else if (activeObject == objects.get("portableRadio")) {
    loadPortableRadioSong();
  } else if (activeObject == objects.get("MP3Player")) {
    radioSongAM.stop();
    radioSongFM.stop();
    loadmp3PlayerSong();
  } else if (activeObject == objects.get("phone")) {
    loadPhoneSong();
  } else if (activeObject == -1) {
    //if (radioSongAM != null) radioSongAM.stop();
    //if (radioSongFM != null) radioSongFM.stop();
    //stopSound();

    setupOldschoolRadio();
    setupPortableRadio();
    setupMP3Player();
    setupPhone();

    setupSound();
  }
}
