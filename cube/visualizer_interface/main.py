from flask import Flask
import threading
import serial

COM_PORT = 'COM7'
HOST = "0.0.0.0"
PORT = 8080

app = Flask(__name__)

collect_data_t_alive = True
data = None

@app.route("/")
def main():
    global data
    # print("CURRENT_DATA", data)
    return data

def collect_data():
    global data
    ser = serial.Serial(COM_PORT, 115200, timeout=10)
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

    while(collect_data_t_alive):
        data = ser.readline()
        # print(data)

if __name__ == "__main__":
    threading.Thread(target=collect_data).start()
    app.run(host=HOST, port=PORT, debug=True, use_reloader=False)
    collect_data_t_alive = False
