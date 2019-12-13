
# OBSOLETE - An Interactive Satire
### IAT320 Final Project

## About

Code for Platform, Objects and Audio player


## Code:
- __`Base`__ Arduino code that handles main platform / base which the 4 audio players will rest on.  communicates with all 4 objects and with computer

- __`4 Objects`__ Arduino code for all four objects:
    - Oldschool Radio
    - Portable Radio
    - MP3 Player
    - Phone

- __`Audio_Player`__ Processing code that listens for command via serial from Platform and starts and stops the song

## Libraries
I have included the Arduino libraries used.  They can be copied into ~/Documents/Arduino/libraries.  Most can be downloaded through "Manage Libraries" but I customized the code for RF24G library so you must use my version of that library.  This had to be done because the original library would consatntly and verbosely print to serial during every function call.  This made the JSON which the Audio Player recieves over serial (USB) invalid a lot of the time.  To fix this a removed all serial print aactivity from the RF24G library.