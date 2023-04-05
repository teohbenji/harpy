#NOTE: Ensure Serial Monitor is not running in IDE.
#Python code to detect string pull, and play the corresponding note.

import serial
import musicalbeeps

arduino = serial.Serial(port='COM3', baudrate=9600, timeout=.1) #Baud rate has to match Arduino
player = musicalbeeps.Player(volume = 1,
                            mute_output = False)

def readArduinoData():
    """Reads Serial monitor data from Arduino, and cleans into Python string.

    Returns:
        cleaned_str: Content of string matches Serial.print output in Arduino 
    """
    data = arduino.readline() #returns data as bytes
    cleaned_str = str(data.decode("utf-8")).strip()
    return cleaned_str

def playNote(note):
    player.play_note(note, 0.5)

def main():
    while True:
        value = readArduinoData()
        print(value, type(value), len(value))
        if (value in ["C", "D", "E", "F", "G", "A", "B"]):
            playNote(value)

main()