import java.util.Map;

int activeObject = -1;

int serialPort = 21;

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
    println("SHOULD EBE STOPPING ALL AUDIO");
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
