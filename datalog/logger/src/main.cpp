#include <Arduino.h>
#include "Wire.h"
#include "Arduino_LED_Matrix.h"
#include <MPU6050_light.h>
#include <Arduino_FreeRTOS.h>

MPU6050 mpu(Wire);
ArduinoLEDMatrix matrix;

TaskHandle_t TaskSerialReadHandle;
TaskHandle_t TaskSensorReadHandle;

struct SensorData {
  float accX, accY, accZ;
  float gyroX, gyroY, gyroZ;
} sensorData;

uint8_t frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

void TaskSerialRead(void *pvParameters) {
  for(;;){
    if(Serial.available() > 0){
      char receivedChar = Serial.read();
      if(receivedChar == 'i'){
        digitalWrite(LED_BUILTIN, HIGH);
        for(uint8_t i=0; i<8; i++){
          for(uint8_t j=0; j<12; j++){
            frame[i][j] = 0;
          }
        }
        matrix.renderBitmap(frame, 8, 12);
        xTaskNotifyGive(TaskSensorReadHandle);
      }
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
    
  }
}

void TaskSensorRead(void *pvParameters) {
  const TickType_t xMaxExpectedBlockTime = pdMS_TO_TICKS(2000);
  unsigned int tini = 0;
  unsigned int tfin = 0;

  for(;;){
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);


    for(uint8_t i = 0; i<50; i++){
      TickType_t xLastWakeTime;
      const TickType_t xIncrement = 20/portTICK_PERIOD_MS;
      xLastWakeTime = xTaskGetTickCount();
      mpu.update();

      Serial.print(mpu.getAccX()); Serial.print(",");
      Serial.print(mpu.getAccY()); Serial.print(",");
      Serial.print(mpu.getAccZ()); Serial.print(",");
      Serial.print(mpu.getGyroX()); Serial.print(",");
      Serial.print(mpu.getGyroY()); Serial.print(",");
      Serial.print(mpu.getGyroZ()); Serial.print(",");
      Serial.println("");                              

      uint8_t row = i/12;
      uint8_t col = i%12;
      frame[row][col] = 1;
      matrix.renderBitmap(frame, 8, 12);
      vTaskDelayUntil( &xLastWakeTime, xIncrement );   
    }
    digitalWrite(LED_BUILTIN, LOW);
  

  }
}


void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);
  matrix.begin();

  // Initialize I2C communication and MPU6050 sensor
  Wire.begin();
  
  byte status = mpu.begin();

  pinMode(LED_BUILTIN, OUTPUT);

  // Verify sensor connection
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  //delay(1000);
  mpu.calcOffsets(true,true); // gyro and accelero
  Serial.println("Done!\n");


  // Create FreeRTOS tasks
  xTaskCreate(TaskSerialRead, "SerialRead", 128, NULL, 1, &TaskSerialReadHandle);
  xTaskCreate(TaskSensorRead, "SensorRead", 128, NULL, 2, &TaskSensorReadHandle);

  Serial.println("Starting scheduler ...");

  vTaskStartScheduler();
}


void loop() {
  // Nothing to do here as tasks are handled by FreeRTOS
}