#NOTE: Ensure Serial Monitor is not running in IDE.
#Python code to detect string pull, and play the corresponding note.

import serial
import time

arduino = serial.Serial(port='COM3', baudrate=115200, timeout=.1) #Baud rate has to match Arduino

def readArduinoData():
    """Reads Serial monitor data from Arduino, and cleans into Python string.

    Returns:
        cleaned_str: Content of string matches Serial.print output in Arduino 
    """
    data = arduino.readline() #returns data as bytes
    cleaned_str = str(data.decode("utf-8"))
    return cleaned_str

# def checkIfStringPulled():
#     value = readArduinoData()
#     if(value == "C1"):
#         print("Plays music!!!!!!!")

while True:
    value = readArduinoData()
    print(value, type(value))
    time.sleep(0.2)