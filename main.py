#NOTE: Ensure Serial Monitor is not running in IDE.
#Python code to detect string pull, and play the corresponding note.
#For freeplay and synthesia modes

import serial
import musicalbeeps
from threading import Thread

arduino = serial.Serial(port='COM3', baudrate=9600, timeout=.1) 

def readArduinoData():
    """Reads Serial monitor data from Arduino, and cleans into Python string.

    Returns:
        cleaned_str: Content of string matches Serial.print output in Arduino 
    """
    data = arduino.readline()
    cleaned_str = str(data.decode("utf-8")).strip()
    return cleaned_str

def play_note(note):
    player = musicalbeeps.Player(volume = 1,
                            mute_output = False)
    player.play_note(note, 0.5)

if __name__ == '__main__':
    while True:
        value = readArduinoData()
        print(value, type(value), len(value))
        
        isValueNote = value in ["C3", "D3", "E3", "F3", "G3", "A3", "B3", "C4", "D4", "E4", "F4", "G4", "A4", "B4"]
        if isValueNote:
            Thread(target=play_note, args=(value,)).start()