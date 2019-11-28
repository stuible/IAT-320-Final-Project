SoundFile radioSongAM;
SoundFile radioSongFM;

boolean portableRadioAM = true;

void setupPortableRadio() {
  objects.put("portableRadio", 1);
  
  radioSongAM = new SoundFile(this, "surfinusa.mp3");
  //radioSongAM = new SoundFile(this, "jfk.mp3");
  //println("loaded jfk");
  radioSongFM = new SoundFile(this, "surfinusa.mp3");
  println("loaded surfinusa");
}

void loadPortableRadioSong() {
  if(portableRadioAM) changeSound(radioSongAM);
  else changeSound(radioSongFM);
}

void setPortableRadioAM() {
  portableRadioAM = true;
  loadPortableRadioSong();
}
void setPortableRadioFM() {
  portableRadioAM = false;
  loadPortableRadioSong();
}
