#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <Wire.h>
#include <MPU6050_light.h>

#define _1_OPTIMIZE 0B11000000 // PROGMEM + Highly-Recommended Optimization For RAM
#define _2_OPTIMIZE 0B00100100 // MULTIPLE_BIASES_PER_LAYER + int8_t quantization 

#define ACTIVATION__PER_LAYER
        #define ReLU
        #define Softmax

#include "NeuralNetwork.h"


#define NumberOf(arg) ((unsigned int) (sizeof(arg) / sizeof (arg[0]))) // alculates the number of layers 


// Uncomment the following lines for 8 GESTURES MODELS
// #include "dnn8g.h"

// const char* gestures[] = {
//     "still",
//     "wave",
//     "swipe_left",
//     "swipe_down",
//     "swipe_right",
//     "swipe_up",
//     "stop",
//     "roll"
// };
// const int numGestures = 8;

// const unsigned int layers[] = {300, 16, 16, 8, 8}; 
// byte activFunctions[] = {  0, 0, 0, 1};      // 0: ReLU, 1: Softmax


// Uncomment the following lines for 6 GESTURES MODELS
#include "dnn6g.h"

const char* gestures[] = {
    "still",
    "wave",
    "swipe_left",
    "swipe_down",
    "stop",
    "roll"
};
const int numGestures = 6;

const unsigned int layers[] = {300, 16, 8, 8, 6}; 
byte activFunctions[] = {  0, 0, 0, 1};         // 0: ReLU, 1: Softmax


// Uncomment the following lines for 4 GESTURES MODELS
// #include "dnn4g.h"

// const char* gestures[] = {
//     "still",
//     "wave",
//     "swipe_left",
//     "stop"
// };
// const int numGestures = 4;

// const unsigned int layers[] = {300, 8, 8, 4}; 
// byte activFunctions[] = {  0, 0, 1};      // 0: ReLU, 1: Softmax


const int TSensor = 20;


// Task handlers
TaskHandle_t TaskSensorHandle = NULL;
TaskHandle_t TaskInferenceHandle = NULL;


MPU6050 mpu(Wire);



float *outputNN;

unsigned long t0, t1, timeElapsed, tCurrent, tLast, tPeriod;

unsigned long tInference;


const int numFeatures = 6;
const int numSamples = 50;

const int inputLength = numFeatures * numSamples;

float buffer[inputLength];
float inputNN[inputLength];
float normalizedData[numFeatures];

int head = 0;


NeuralNetwork NN(layers, weights, biases, NumberOf(layers), activFunctions);


// Function prototypes
void TaskSensor(void *pvParameters);
void TaskInference(void *pvParameters);

void normalizeData(float *data);


/**
 * Setup Function
 * 
 */
void setup() {
    Serial.begin(115200);

    Serial.println("{\"type\":\"info\", \"message\":\"Starting System\"}");

    // Initialize MPU6050
    Wire.begin();
    byte status = mpu.begin(1, 1);
    Serial.print("{\"type\":\"info\", \"message\":\"MPU6050 status: "); Serial.print(status); Serial.println("\"}");

    // If there is no response from MPU6050, block the initialization
    while(status!=0){ }

    Serial.println("{\"type\":\"info\", \"message\":\"Calculating MPU6050 offsets, please do not move the sensor...\"}");
    mpu.calcOffsets(true, true); 
    Serial.println("{\"type\":\"info\", \"message\":\"Calibration finished\"}");


    // Initialize buffer and inputNN 
    for(int b=0; b<inputLength; b++){
        buffer[b] = 0;
        inputNN[b] = 0;
    }

    head = 0;

    Serial.println("{\"type\":\"info\", \"message\":\"Starting scheduler...\"}");

    xTaskCreate(
        TaskSensor,       
        "TaskSensor",         
        configMINIMAL_STACK_SIZE,   
        NULL, 
        2, 
        &TaskSensorHandle
    );

    xTaskCreate(
        TaskInference, 
        "TaskInference",   
        2048,
        NULL, 
        1, 
        &TaskInferenceHandle
    );

}


void loop() {
  // Nothing to do here
}

/**
 * Task for reading sensor data
 */
void TaskSensor(void *pvParameters){
    TickType_t xLastWakeTime;
    xLastWakeTime = 0;

    uint8_t samples = 0;
    float rawData[numFeatures];

    for(;;){

        xLastWakeTime = xTaskGetTickCount();

        mpu.update();
        
        rawData[0] = mpu.getAccX();
        rawData[1] = mpu.getAccY();
        rawData[2] = mpu.getAccZ();
        rawData[3] = mpu.getGyroX();
        rawData[4] = mpu.getGyroY();
        rawData[5] = mpu.getGyroZ();

        normalizeData(rawData);

        samples++;

        if(samples >= 10){
            samples = 0;
            xTaskNotifyGive(TaskInferenceHandle);
        }

        xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(TSensor));

    }
}

/**
 * Task for making inferences
 */
void TaskInference(void *pvParameters){

    int headInput;

    TickType_t tStart, tEnd, tInference;

    int detectedGesture = -1;
    int currentGesture = -1;
    int candidateGesture = -1;
    int consecutiveCount = 0;
    const int requiredConsecutive = 2;

    for(;;){
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        tStart = xTaskGetTickCount();

        headInput = head;

        // Only for Circular buffer
        for(int i=0; i<inputLength; i++){
            inputNN[i] = buffer[headInput];
            headInput = (headInput + 1) % inputLength;
        }
        
        outputNN = NN.FeedForward(inputNN);

        float maxVal = -1000;
        int8_t maxIndex = -1;

        for(uint8_t i=0; i<numGestures; i++){
            if(outputNN[i] > maxVal){
                maxVal = outputNN[i];
                maxIndex = i;
            }
        }

        tEnd = xTaskGetTickCount();
        tInference = (tEnd - tStart) * portTICK_PERIOD_MS;

        // Print the Real-Time inference result
        Serial.print("{");
        Serial.print("\"type\":\"raw\", ");
        Serial.print("\"predicted\":\""); Serial.print(gestures[maxIndex]); Serial.print("\", ");
        Serial.print("\"prob\":\""); Serial.print(maxVal); Serial.print("\", ");
        Serial.print("\"time\":\""); Serial.print(tInference); Serial.print("\", ");
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


/**
 * Normalizes the data and inserts it to the circular buffer
 */
void normalizeData(float *data){
    // Mean and Std. Dev. values for accel and gyro. Calculated at training
    const float mean[] =  {0.11057, -0.33894, 0.87751, -11.37737,   6.73449,   7.65292};
    const float stdev[] = {0.91116,  0.82320, 0.92559,  77.19974, 171.23090, 104.44059};

    for(int i=0; i<numFeatures; i++){
        buffer[head + i] = (data[i] - mean[i]) / stdev[i];
    }
    head = (head + 6) % inputLength;
}

