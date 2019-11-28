SoundFile radioSongAM;
SoundFile radioSongFM;

boolean portableRadioAM = true;

void setupPortableRadio() {
  objects.put("portableRadio", 1);
  
  radioSongAM = new SoundFile(this, "jfk.mp3");
  radioSongFM = new SoundFile(this, "surfinusa.mp3");
}

void loadPortableRadioSong() {
  if(portableRadioAM) loadSound(radioSongAM);
  else loadSound(radioSongFM);
}

void setPortableRadioAM() {
  portableRadioAM = true;
  loadPhoneSong();
}
void setPortableRadioFM() {
  portableRadioAM = false;
  loadPhoneSong();
}
