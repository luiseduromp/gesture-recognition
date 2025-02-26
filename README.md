# Gesture Recognition
This repository includes all the modules necessary to implement an IMU based gesture recognition system. 

This project was developed as part of a master´s final project, which objective was to test different neural network sizes and architectures in embedded systems running in real time.

The IMU used is the MPU6050, which has a 3 axes accelerometer and a 3 axes gyroscope, and the embedded devices tested were an Arduino Mega 2560 and an Arduino Giga R1.

### Datalog
The first module is the datalog, that has the logger script for an Arduino, and a python script, which takes the data sent by the arduino and saves it as a CSV file. 

The gesture options showed in the python script where originally used in the project, however any custom gesture can be logged just by changing the name in the options. After logging the gesture, the file is saved inside a directory with the gesture name.

**The original dataset is not included in this repository**

### Training
The neural networks training was done using Google Colab. The notebooks included were run in Colab. This module includes two notebooks:
- Normalization. Performs normalization of the dataset.
- Training. Contains the actual training of the neural networks that were implemented in both devices.

### Inference
The inference module includes the individual implementations on each Arduino. Both implementations have been developed to be almost the same, however, since part of the requirement of the project was to test different real time operating systems, there are some slight changes between each other.
- Arduino Mega 2560 works with FreeRTOS, and was implemented using Giorgos Xou's [NeuralNetworks](https://github.com/GiorgosXou/NeuralNetworks) library. The library is very well documented, is easy to use and has lots of examples.
- Arduino Giga R1 runns with MbedOS, and the inference engine is [ArduTFLite](https://github.com/spaziochirale/ArduTFLite) by Spazio Chirale. This library has a very easy to use API.

### Evaluation
The evaluation module has a python script that was developed to evaluate the real deployment of the gesture recognition system on each platform. The script reads the output from the serial port of the Arduino and after receiving a detected gesture, a prompt is shown in the terminal asking if the detected gesture was correct. After a number of samples taken, the individual precision of each gesture is calculated.

### Interface
The interface module was designed as a web application. The backend is a FastAPI app, which has been setup to work with websockets to enable direct updates of gesture detections to the client. And the frontend is the actual interface built using React. The interface was developed to take the real-time gesture data and the processed gestures, and it shows both in the browser.



> [!NOTE]
> The master's final project of which this repository is part, was financed and supported by the "Siemens Energy AI Chair: Energy Sustainability for a Decarbonized Society 5.0"; (TSI-100930-2023-5), funded by the Secretary of State for Digitalization and Artificial Intelligence through the ENIA 2022 Chairs call, and co-funded by the European Union-Next Generation EU.