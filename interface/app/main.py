import json

from fastapi import FastAPI, WebSocket
import serial
from serial.tools import list_ports

app = FastAPI()

stop_port = False

def detect_serial_ports():
    ports = list(list_ports.comports())

    if not ports:
        raise Exception("No serial ports detected. Please connect the device and try again.")
    
    print("Available serial ports:")
    for port in ports:
        print(port.device, port.description)

    return ports[0].device


def read_serial_data():

    try:
        port = detect_serial_ports()
        with serial.Serial(port, 115200, timeout=1) as ser:
            while not stop_port:
                line = ser.readline().decode('utf-8').strip()
                # print(line)
                try:
                    if line:
                        yield json.loads(line)
                except json.JSONDecodeError:
                    print("Invalid JSON data")

    except KeyboardInterrupt:
        print("Keyboard interrupt")
                
    except serial.SerialException as e:
        print("Serial port error: ", e)

    finally:
        print("Closing serial port")
        ser.close()

    


@app.get(path="/")
async def home():
    return {"init":"Gesture Recognition Interface"}


@app.websocket(path="/ws/data")
async def data_stream(websocket: WebSocket):
    await websocket.accept()
    for data in read_serial_data():
        print(data)
        await websocket.send_json(data)