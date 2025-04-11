# Created by Cameron Oehler
# April 11, 2025
# Reads serial data stream and allows that data to be requested over HTTP

from flask import Flask
import threading
import serial

COM_PORT = 'COM7'
HOST = "0.0.0.0"
PORT = 8080

app = Flask(__name__)

collect_data_t_alive = True # Should collect_data thread continue
data = None # Current data

@app.route("/")
def main():
    global data
    # print("CURRENT_DATA", data)
    return data # Respond with current data

def collect_data():
    global data

    # Start connection with STM32
    ser = serial.Serial(COM_PORT, 115200, timeout=10)

    # Send command "stream"
    ser.write(b's')
    ser.read(1)
    ser.write(b't')
    ser.read(1)
    ser.write(b'r')
    ser.read(1)
    ser.write(b'e')
    ser.read(1)
    ser.write(b'a')
    ser.read(1)
    ser.write(b'm')
    ser.read(1)
    ser.write(b'\n')

    # Collect and store data stream
    while(collect_data_t_alive):
        data = ser.readline()
        # print(data)

if __name__ == "__main__":
    threading.Thread(target=collect_data).start() # Run as seperate thread
    app.run(host=HOST, port=PORT, debug=True, use_reloader=False) # Blocks until Ctrl+C
    collect_data_t_alive = False # Kill other thread
