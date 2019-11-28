/* 
 Inspired by https://processing.org/reference/libraries/sound/SoundFile.html
 */

import processing.sound.*;

SoundFile currentSound;

float volume = 50;

void setVolume(float _volume) {
  currentSound.amp(_volume / 100);
  volume = _volume;
  
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
  setVolume(volume);
  playSound();
}

void changeSound(SoundFile sound) {
  if (currentSound != null) currentSound.amp(0);
  currentSound = sound;
  setVolume(volume);
  if(!currentSound.isPlaying()) playSound();
}

void volumeUp(){
if(volume <= 80) setVolume(volume + 20);
}

void volumeDown(){
if(volume >= 20) setVolume(volume - 20);
}
