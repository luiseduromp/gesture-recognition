import serial
import json
import time
from collections import defaultdict


SERIAL_PORT = 'COM3'
BAUD_RATE = 115200

SAMPLES_LIMIT = 100

raw_message_count = 0
processed_message_count = 0

max_time = float('-inf')
min_time = float('inf')

true_positives = defaultdict(int)
false_positives = defaultdict(int)
total_per_class = defaultdict(int)


def calculate_balanced_accuracy():
    per_class_accuracy = []
    for gesture in total_per_class:
        total = total_per_class[gesture]
        if total > 0:
            accuracy = true_positives[gesture] / total
        else:
            accuracy = 0.0
        per_class_accuracy.append(accuracy)

    balanced_accuracy = sum(per_class_accuracy) / len(per_class_accuracy)
    return balanced_accuracy, per_class_accuracy



if __name__ == '__main__':

    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f'Connected to {SERIAL_PORT}')

    except serial.SerialException as e:
        print(f'Error. Could not connect to {SERIAL_PORT}. {e}')
        exit(1)

    print("\n---------------- GESTURE RECOGNITION EVALUATION ----------------")
    print("Script for evaluating the gesture recognition system.")
    print("Please perform gestures and provide the feedback when prompted.")
    print("----------------------------------------------------------------\n")

    try:
        while processed_message_count < SAMPLES_LIMIT:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').strip()
                try:
                    data = json.loads(line)

                    if data['type'] == 'raw':
                        raw_message_count += 1
                        inference_time = float(data['time'])
                        max_time = max(max_time, inference_time)
                        min_time = min(min_time, inference_time)

                    elif data['type'] == 'proc':
                        processed_message_count += 1
                        detected_gesture = data['predicted']
                        total_per_class[detected_gesture] += 1

                        print(f'({processed_message_count}/{SAMPLES_LIMIT}) "{detected_gesture.upper()}" detected. Was this correct? (y/n): ', end='')
                        start_time = time.time()

                        while True:
                            if time.time() - start_time > 10:
                                print('\nTimeout. No response received. Discarding this sample.')
                                processed_message_count -= 1
                                break

                            response = input().strip().lower()

                            if response == 'y':
                                true_positives[detected_gesture] += 1
                                break
                            elif response == 'n':
                                false_positives[detected_gesture] += 1
                                break
                            else:
                                print('Invalid input. Please enter "y" or "n": ', end='')

                except json.JSONDecodeError as e:
                    print(f'Error. Not a valid data message. {e}')

                except KeyError as e:
                    print(f'Error. Not a valid data message. {e}')

        print(f"\n{SAMPLES_LIMIT} samples have been taken. Calculatig performance metrics...")
        balanced_accuracy, per_class_accuracy = calculate_balanced_accuracy()
        
        print("\n----- PERFORMANCE METRICS SUMMARY -----")
        
        print(f"Total inferences made: {raw_message_count}")
        print(f"Processed gestures received: {processed_message_count}")
        print(f"Max time (WCET): {max_time} ms")
        print(f"Min time: {min_time} ms")

        print("Accuracy per class:")
        for gesture, accuracy in zip(total_per_class.keys(), per_class_accuracy):
            print(f"- {gesture}: {accuracy:.2f}")

        print(f"Balanced accuracy: {balanced_accuracy:.2f}")
        print("---------------------------------------")
        

    except KeyboardInterrupt:
        print("\nInterrupted by user. Exiting program.")

    finally:
        ser.close()
        print("Serial port closed.")
            
