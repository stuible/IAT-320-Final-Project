SoundFile[] mp3PlayerSongs;
int currentmp3PlayerSong = 0;

void setupMP3Player() {
  objects.put("MP3Player", 2);
  
  mp3PlayerSongs = new SoundFile[6];
  mp3PlayerSongs[0] = new SoundFile(this, "imissyou.mp3");
  mp3PlayerSongs[1] = new SoundFile(this, "souljaboy.mp3");
  mp3PlayerSongs[2] = new SoundFile(this, "wonderwall.mp3");
  mp3PlayerSongs[3] = new SoundFile(this, "imagine.mp3");
  mp3PlayerSongs[4] = new SoundFile(this, "complicated.mp3");
  mp3PlayerSongs[5] = new SoundFile(this, "wonderwall.mp3");
}

void loadmp3PlayerSong() {
  loadSound(mp3PlayerSongs[currentmp3PlayerSong]);
}

void setmp3PlayerSong(int index) {
  currentmp3PlayerSong = index;
  loadmp3PlayerSong();
}
