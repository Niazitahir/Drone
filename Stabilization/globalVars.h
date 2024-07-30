#ifndef GLOBALVARS_H
#define GLOBALVARS_H

extern Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);
extern Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
extern Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
extern float velX, velY, velZ;
extern float avgX, avgY, avgZ;
extern float curX, curY, curZ;
#endif