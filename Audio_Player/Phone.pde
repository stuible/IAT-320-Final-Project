SoundFile[] phoneSongs;
int currentPhoneSong = 0;

void setupPhone() {
  objects.put("phone", 3);

  phoneSongs = new SoundFile[3];
  phoneSongs[0] = new SoundFile(this, "guccigang.mp3");
  phoneSongs[1] = new SoundFile(this, "imissyou.mp3");
  phoneSongs[2] = new SoundFile(this, "wonderwall.mp3");
}

void loadPhoneSong() {
  loadSound(phoneSongs[currentPhoneSong]);
}

void setPhoneSong(int index) {
  currentPhoneSong = index;
  loadPhoneSong();
}
