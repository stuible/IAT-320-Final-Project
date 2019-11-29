IAT320
# Final Project
Prototype code for Platform, Objects and Audio player

## Code:
- __`Base`__ Arduino code that handles main platform / base which the 4 audio players will rest on.  communicates with all 4 objects and with computer

- __`4 Objects`__ Arduino code for all four objects:
    - Oldschool Radio
    - Portable Radio
    - MP3 Player
    - Phone

- __`Audio_Player`__ Processing code that listens for command via serial from Platform and starts and stops the song

## Libraries
I have included the Arduino libraries used.  They can be copied into ~/Documents/Arduino/libraries.  Most can be downloaded through "Manage Libraries" but I customized the code for RF24G library so you must use my version of that library.