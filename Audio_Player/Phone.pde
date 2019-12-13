// Phone Helper Functions

SoundFile[] phoneSongs;
int currentPhoneSong;

// Add object
void setupPhone() {
  currentPhoneSong = 0;
  objects.put("phone", 3);

  phoneSongs = new SoundFile[4];
  phoneSongs[0] = new SoundFile(this, "walk.mp3");
  println("loaded walk");
  phoneSongs[1] = new SoundFile(this, "luciddreams.mp3");
  println("loaded luciddreams");
  phoneSongs[2] = new SoundFile(this, "ad.mp3");
  println("loaded ad");
  phoneSongs[2] = new SoundFile(this, "panda.mp3");
  println("loaded panda");
}

void loadPhoneSong() {
  loadSound(phoneSongs[currentPhoneSong]);
}

void setPhoneSong(int index) {
  currentPhoneSong = index;
  loadPhoneSong();
}
