#include "globalVars.h"

float velX, velY, velZ;
float avgX, avgY, avgZ;
float curX, curY, curZ;

void displaySensorDetails(int x)
{
  sensor_t sensor;
  if (x == 0){
    accel.getSensor(&sensor);
  }
  else if (x == 1){
    gyro.getSensor(&sensor);
  }
  else if (x == 2){
    mag.getSensor(&sensor);
  }
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void gyroSetup(){
  Serial.println("Gyroscope Test"); Serial.println("");
  /* Enable auto-ranging */
  gyro.enableAutoRange(true);
  if(!gyro.begin())
  {
    Serial.println("Ooops, no L3GD20 detected ... Check your wiring!");
    while(1);
  }
  displaySensorDetails(1);
}
void accelSetup(){
   Serial.println("Accelerometer Test"); Serial.println("");
  accel.enableAutoRange(true);
  if(!accel.begin())
  {
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  displaySensorDetails(0);
}
void magSetup(){
  Serial.println("Magnetometer Test"); Serial.println("");
  /* Enable auto-gain */
  mag.enableAutoRange(true);
  if(!mag.begin())
  {
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  displaySensorDetails(2);
}

void updateCurAccel(){
  sensors_event_t event;
  accel.getEvent(&event);
  curX = event.acceleration.x;
  curY = event.acceleration.y;
  curZ = event.acceleration.z;
}

void updateAverageAccel(){
  updateCurAccel();
}

//void updateVelocityVector(int*x, int*y, int*z, )