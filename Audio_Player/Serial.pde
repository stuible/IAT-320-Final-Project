// Serial Helper Functions

import processing.serial.*;

Serial serial;
String serialBuffer;

boolean ignoreSerial = false;

void setupSerial() {
  try {
    //Open USB Serial Port
    printArray(Serial.list()); 
    serial = new Serial(this, Serial.list()[serialPort], 9600);
    println("OPENING PORT");
  }
  catch(Exception e) {
    println("PORT NOT AVAILABLE");
  }

  // Instantiate serial buffer string
  serialBuffer = "";
}

void updateSerial() {

  // Pulls serial JSON data into buffer if available.
  if (serial != null) {
    while (serial.available() > 0) {
      String inBuffer = serial.readString();   
      if (inBuffer != null) {

        serialBuffer += inBuffer;

        //Recived completed json object and can now process it
        if (serialBuffer.endsWith("\n")) {

          // Confirm we started listening in time to recieve the beginning of the JSON object
          JSONObject json = serialBuffer.startsWith("{") ? parseJSONObject(serialBuffer) : null;
          if (json == null) {
            println("JSONObject could not be parsed:");
            println(serialBuffer);
          } else {
            println(serialBuffer);

            // If JSON has "vol" key, proccess the volume
            if (json.hasKey("vol")) {
              Object volObj = json.get("vol");
              // If volume is number, set volume to that number
              if (volObj instanceof Number) {

                try {
                  setVolume(((Number)volObj).floatValue());
                }
                catch(Exception e) {
                  //  Block of code to handle errors
                  println(e);
                }
              }
              // If volume is a string increase or decrease volume accordingly
              if (volObj instanceof String) {
                String volCommand = (String) volObj;

                if (volCommand.equals("up")) {
                  println("vol up");
                  volumeUp();
                }
                if (volCommand.equals("down")) {
                  println("vol down");
                  volumeDown();
                }
              }
            }

            // If JSON has "track" key, process a song change
            if (json.hasKey("track")) {

              // If track is a number, set the song the the index recieved from the phone object
              Object trackObj = json.get("track");
              if (trackObj instanceof Number) {
                int newSongIndex = (int) trackObj;
                if (activeObject == objects.get("phone")) {
                  setPhoneSong(newSongIndex);
                }
              }

              // If track is a string, set the song the next or previous mp3 player track accordingly
              // (or handle play / pause)
              if (trackObj instanceof String) {

                String trackCommand = (String) trackObj;

                if (trackCommand.equals("next")) {
                  println("next");
                  nextmp3PlayerSong();
                }
                if (trackCommand.equals("prev")) {
                  println("prev");
                  prevmp3PlayerSong();
                }
                if (trackCommand.equals("pause")) {
                  println("pause / play");
                  playPausemp3Song();
                }
              }
            }

            // If JSON has "AM" key then process the portable radios AM / FM status
            if (json.hasKey("AM")) {
              boolean AM = json.getBoolean("AM");
              if (AM) setPortableRadioAM();
              else setPortableRadioFM();
            }

            //If JSON has "activeObject" key, switch the active object to recieved index
            if (json.hasKey("activeObject")) {
              changeObject(json.getInt("activeObject"));
              println("Active Object Changed to: " + activeObject);
            }


            // Process Active state if it exists in json object
            if (json.hasKey("active")) {
              boolean active = json.getBoolean("active");

              // If object is active, play song
              if (active) {
                //if(!file.isPlaying()) file.play();
              }
              // If not, stop the song
              else currentSound.stop();
            }
          }

          //Reset buffer
          serialBuffer = "";
        } else {
          // Buffer not ready
        }
      }
    }
  }
}
