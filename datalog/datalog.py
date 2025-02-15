import serial
import csv
import time
import os
from typing import Union
from pathlib import Path

SERIAL_PORT = 'COM6'
BAUD_RATE = 115200
OUTPUT_FILE = 'gesture_samples.csv'

DATASET_PATH = './dataset'

NUM_SAMPLES = 50
NUM_FEATURES = 6

ser = serial.Serial(port=SERIAL_PORT, baudrate=BAUD_RATE, timeout=1)

datafile = OUTPUT_FILE

EXIT_OPTION = 'q'

options = {
    '0':'still',
    '1':'wave',
    '2':'swipe_left',
    '3':'swipe_down',
    '4':'swipe_right',
    '5':'swipe_up',
    '6':'stop',
    '7':'roll',
    'q':'Exit Program'
}


def display_menu() -> None:
    """Displays the menu in the terminal according to the existing options."""
    print('\nGesture recorder from MPU6050')
    print('Gesture options:')
    for key, value in options.items():
        print(f"{key}. {value}")


def collect_data(option:str) -> None:
    output_dir = os.path.join(DATASET_PATH, options[option])
    os.makedirs(output_dir, exist_ok=True)
    existing_files = os.listdir(output_dir)
    file_index = len(existing_files) + 1
    csv_file = os.path.join(output_dir, f'{options[option]}_{file_index}.csv')

    samples = []
    while len(samples) < NUM_SAMPLES:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()

            try:
                values = list(map(float, line.split(",")))

                if len(values) == NUM_FEATURES:
                    samples.append(values)
                
            except ValueError:
                print(f'Invalid data received: {line}')

    print(f"Samples collected: {len(samples)}")
 
    with open(file=csv_file, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['accX', 'accY', 'accZ', 'gyroX', 'gyroY', 'gyroZ'])
        writer.writerows(samples)

    print(f'Samples saved to {csv_file}')


def samples_count(path: str) -> dict:
    no_samples = {}
    for root, dirs, files in os.walk(path):
        for directory in dirs:
            dir_path = os.path.join(root, directory)
            file_count = len([f for f in os.listdir(dir_path) if os.path.isfile(os.path.join(dir_path, f))])
            no_samples[directory] = file_count

    return no_samples



if __name__ == '__main__':

    try:
        while True:
            display_menu()
            print('-'*20)
            print('No. Samples:', samples_count(path=DATASET_PATH))
            print('-'*20)
            option = input('Enter your choice: ')

            print(f'Option: {option}')

            if option in options.keys():
                if option == EXIT_OPTION:
                    print('Exit Program')
                    break
                else:
                    print(f'Taking samples for {options[option]}')
                    ser.write("i".encode('utf-8'))
                    collect_data(option=option)

            else:
                print('Option not valid')

    except KeyboardInterrupt:
        print('Program Cancelled\n')

    finally:
        ser.close()       
        print('Serial Port Closed\n')
