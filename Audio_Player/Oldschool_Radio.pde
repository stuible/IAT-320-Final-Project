SoundFile oldschoolRadioSong;

void setupOldschoolRadio() {
  oldschoolRadioSong = new SoundFile(this, "ww2.mp3");
  
  objects.put("oldschoolRadio", 0);
}

void loadOldschoolRadioSong() {
  loadSound(oldschoolRadioSong);
}
