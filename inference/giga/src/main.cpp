#include "mbed.h"
#include "rtos.h"
#include <Wire.h>
#include <MPU6050_light.h>

#include <ArduTFLite.h>

using namespace mbed;
using namespace rtos;
using namespace std::chrono;


Timer timer;

Thread ThreadSensor(osPriorityHigh4);
Thread ThreadInference(osPriorityHigh2);

Semaphore inferenceSemaphore(0);


MPU6050 mpu(Wire1);


// Uncomment the following lines for 8 GESTURES MODELS
#include "cnn8g.h"   // Convolutional Model
// #include "dnn8g.h"   // Dense Model

const char* gestures[] = {
  "still",
  "wave",
  "swipe_left",
  "swipe_down",
  "swipe_right",
  "swipe_up",
  "stop",
  "roll"
};
const int numGestures = 8;


// Uncomment the following lines for 6 GESTURES MODELS
// #include "cnn6g.h"      // Convolutional Model
//#include "dnn6g.h"   // Dense Model
//
//const char* gestures[] = {
//  "still",
//  "wave",
//  "swipe_left",
//  "swipe_down",
//  "stop",
//  "roll"
//};
//const int numGestures = 6;

const int numFeatures = 6;
const int numSamples = 50;

const int inputLength = numFeatures * numSamples;

const int sampleRate = 20;

// Sensor Data array ------- {ax, ay, az, gx, gy, gz}
float rawData[numFeatures] = {0,  0,  0,  0,  0,  0};

float buffer[numSamples][numFeatures];
int head = 0;


// TFLite interpreter variables
constexpr int tensorArenaSize = 40 * 1024;
byte tensorArena[tensorArenaSize];


// Function Prototypes
void taskSensor(void);
void taskInference(void);

void normalizeData(float* data);


void setup(){
  Serial.begin(115200);
  
  Serial.println("{\"type\":\"info\", \"message\":\"Starting System in Arduino Giga R1 WiFi\"}");

  Wire1.begin();
  byte status = mpu.begin(1,1);
  Serial.print("{\"type\":\"info\", \"message\":\"MPU6050 status: "); Serial.print(status); Serial.println("\"}");

  // If sensor does not respond, the execution is blocked
  while(status!=0){ }

  Serial.println("{\"type\":\"info\", \"message\":\"Calculating MPU6050 offsets, please do not move the sensor...\"}");
  mpu.calcOffsets(true, true); 
  Serial.println("{\"type\":\"info\", \"message\":\"Calibration finished\"}");


  // Model Initialization. Execution is stopped if fails
  Serial.println("{\"type\":\"info\", \"message\":\"Initializing Neural Network Model...\"}");

  if (!modelInit(model, tensorArena, tensorArenaSize)){
    Serial.println("{\"type\":\"info\", \"message\":\"Model initialization failed. Please restart the system\"}");
    while(true);
  }
  Serial.println("{\"type\":\"info\", \"message\":\"Model Initialized\"}");

  // Initialize buffer to zero
  for(int i=0; i<numSamples; i++){
    for(int j=0; j<numFeatures; j++){
      buffer[i][j] = 0;
    }
  }

  head = 0;

  Serial.println("{\"type\":\"info\", \"message\":\"Starting scheduler...\"}");

  ThreadSensor.start(taskSensor);
  ThreadInference.start(taskInference);
  
}


void loop(){
    // Nothing to do here
}


void taskSensor(void){

  int lastWakeTime = 0;
  int sampleCount = 0;

  while(1){

    mpu.update();
 
    rawData[0] = mpu.getAccX();
    rawData[1] = mpu.getAccY();
    rawData[2] = mpu.getAccZ();
    rawData[3] = mpu.getGyroX();
    rawData[4] = mpu.getGyroY();
    rawData[5] = mpu.getGyroZ();

    normalizeData(rawData);

    // Print the Data 
    // Serial.print("{");
    // Serial.print("\"type\":\"data\", ");
    // Serial.print("\"data\":[");
    // for(uint8_t i=0; i<numFeatures; i++){
    //     Serial.print("\""); Serial.print(rawData[i]); Serial.print("\"");
    //     if(i < numFeatures - 1){
    //         Serial.print(", ");
    //     }
    // }
    // Serial.print("]");
    // Serial.println("}");

    sampleCount++;
    if(sampleCount >= 5){
      inferenceSemaphore.release();
      sampleCount = 0;
    }
    // inferenceSemaphore.release();

    lastWakeTime = sampleRate - Kernel::get_ms_count() % sampleRate;
    ThisThread::sleep_for(lastWakeTime);
  }
}


void taskInference(void){
  int headInput;
  bool inferenceSuccess;
  long tInference = 0;

  float maxVal, output;
  float lastVal = 0;
  int maxIndex;
  int lastIndex = 0;

  int detectedGesture = -1;
  int currentGesture = -1;
  int candidateGesture = -1;
  int consecutiveCount = 0;
  const int requiredConsecutive = 3;

  int outputSamples = 0;
  float outputNN[numGestures];

  while(1){
    inferenceSemaphore.acquire();

    timer.start();

    headInput = head;

    // Feed input data to Neural Network input Layer
    for(int i=0; i<numSamples; i++){
      for(int j=0; j<numFeatures; j++){
        modelSetInput(buffer[headInput][j], numFeatures*i + j);
      }
      headInput = (headInput + 1) % numSamples;
    }

    inferenceSuccess = modelRunInference();

    timer.stop();
  
    tInference = timer.elapsed_time().count();

    timer.reset();

    if(!inferenceSuccess){
      Serial.println("{\"type\":\"info\", \"message\":\"Inference failed\"}");

    } else {
      maxVal = -1000;
      maxIndex = -1;

      for (int i = 0; i < numGestures; i++) {
        output = modelGetOutput(i);
        if(output > maxVal){
          maxVal = output;
          maxIndex = i;
        }
        outputNN[i] = output;
      }

      // Print the Real-Time inference result
      Serial.print("{");
      Serial.print("\"type\":\"raw\", ");
      Serial.print("\"predicted\":\""); Serial.print(gestures[maxIndex]); Serial.print("\", ");
      Serial.print("\"prob\":\""); Serial.print(maxVal); Serial.print("\", ");
      Serial.print("\"time\":\""); Serial.print(float(tInference)/1000.0); Serial.print("\", ");
      Serial.print("\"output\":{");
      for(uint8_t i=0; i<numGestures; i++){
        Serial.print("\""); Serial.print(gestures[i]); Serial.print("\":\""); Serial.print(outputNN[i]); Serial.print("\"");
        if(i < numGestures - 1){
          Serial.print(", ");
        }
      }
      Serial.print("}");
      Serial.println("}");

      // Process gesture data to deliver a single gesture
      detectedGesture = maxIndex;
      if(detectedGesture == candidateGesture){
        consecutiveCount++;
        if(consecutiveCount >= requiredConsecutive && candidateGesture != currentGesture){
          currentGesture = candidateGesture;
          if(currentGesture != 0){
            Serial.print("{");
            Serial.print("\"type\":\"proc\", ");
            Serial.print("\"predicted\":\""); Serial.print(gestures[currentGesture]); Serial.print("\"");
            Serial.println("}");
          }
        }
      } else {
        candidateGesture = detectedGesture;
        consecutiveCount = 1;
      }

    }
  }
}



void normalizeData(float* data){
  const float mean[] =  {0.11057, -0.33894, 0.87751, -11.37737,   6.73449,   7.65292};
  const float stdev[] = {0.91116,  0.82320, 0.92559,  77.19974, 171.23090, 104.44059};

  for(int i = 0; i < numFeatures; i++){
    buffer[head][i] = (data[i] - mean[i]) / stdev[i];
  }
  head = (head + 1) % numSamples;

}

