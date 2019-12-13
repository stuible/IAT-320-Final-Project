// MP3 Player Helper Functions

// Songs, Current Song and songcount variables (cannot get array size of object arrays in Java)
SoundFile[] mp3PlayerSongs;
int currentmp3PlayerSong;
int songCount = 3;

void setupMP3Player() {
  currentmp3PlayerSong = 1;
  objects.put("MP3Player", 2);

  mp3PlayerSongs = new SoundFile[songCount];
  mp3PlayerSongs[0] = new SoundFile(this, "imissyou.mp3");
  mp3PlayerSongs[1] = new SoundFile(this, "souljaboy.mp3");
  mp3PlayerSongs[2] = new SoundFile(this, "complicated.mp3");
  //mp3PlayerSongs[3] = new SoundFile(this, "wonderwall.mp3");
  //mp3PlayerSongs[4] = new SoundFile(this, "imagine.mp3");
  //mp3PlayerSongs[5] = new SoundFile(this, "wonderwall.mp3");
}

void loadmp3PlayerSong() {
  loadSound(mp3PlayerSongs[currentmp3PlayerSong]);
}

void nextmp3PlayerSong() {
  if (currentmp3PlayerSong < songCount - 1) currentmp3PlayerSong++;
  else currentmp3PlayerSong = 0;
  loadmp3PlayerSong();
}

void prevmp3PlayerSong() {
  if (currentmp3PlayerSong > 0) currentmp3PlayerSong--;
  else currentmp3PlayerSong = songCount - 1;
  loadmp3PlayerSong();
}

void playPausemp3Song() {
  if (currentSound != null) {
    if(currentSound.isPlaying()) currentSound.pause();
    else currentSound.play();
  }
}
