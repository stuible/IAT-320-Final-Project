/* 
 Inspired by https://processing.org/reference/libraries/sound/SoundFile.html
 */

import processing.sound.*;

SoundFile currentSound;

void setVolume(float volume) {
  currentSound.amp(volume / 100);
}

void setupSound() {

  // Load a soundfile from the /data folder of the sketch and play it back
  //currentSound = new SoundFile(this, "imissyou.mp3");
  //currentSound.play();
}

void playSound() {
  if (currentSound != null)   currentSound.play();
}

void stopSound() {
  if (currentSound != null) currentSound.stop();
}

void loadSound(SoundFile sound) {
  stopSound();
  currentSound = sound;
  playSound();
}
