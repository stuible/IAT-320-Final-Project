import processing.serial.*;

Serial serial;
String serialBuffer;

boolean ignoreSerial = false;

void setupSerial() {
  try {
    //Open USB Serial Port
    printArray(Serial.list()); 
    serial = new Serial(this, Serial.list()[6], 9600);
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

        //if (inBuffer.contains("/*") || inBuffer.contains("*/")) {
        //  int commentStart = inBuffer.indexOf("/*");
        //  int commentEnd = inBuffer.indexOf("*/");

        //  String inBufferFiltered = "";
        //  if (commentStart != -1) {
        //    inBufferFiltered += inBuffer.substring(0, commentStart);
        //    ignoreSerial = true;
        //  }
        //  if (commentEnd != -1) {
        //    inBufferFiltered += inBuffer.substring(commentEnd + 2, inBuffer.length());
        //    ignoreSerial = false;
        //  }
        //  serialBuffer += inBufferFiltered;

        //} else if (!ignoreSerial) {
        //  serialBuffer += inBuffer;
        //}
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

            if (json.hasKey("vol")) {
              Object volObj = json.get("vol");
              if (volObj instanceof Number) {
                setVolume(((Double) volObj).floatValue());
              }
              if (volObj instanceof String) {
                //setVolume((Float)volObj);
              }
            }

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
          //println("Buffer not ready:");
        }
      }
    }
  }
}
