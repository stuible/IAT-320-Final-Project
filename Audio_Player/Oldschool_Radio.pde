// Oldschool Radio Helper Functions

SoundFile oldschoolRadioSong;

void setupOldschoolRadio() {
  oldschoolRadioSong = new SoundFile(this, "ww2.mp3");
  println("ww2");
  
  objects.put("oldschoolRadio", 0);
}

void loadOldschoolRadioSong() {
  loadSound(oldschoolRadioSong);
}
