#include "ModeManager.h"
    
ModeManager::ModeManager() {
  
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    
}

void ModeManager::initGyro() {
  accelgyro.initialize();
}

boolean ModeManager::isGyroConnected() {
  return accelgyro.testConnection();
}


int ModeManager::getCurrentMode() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    int aax = abs(ax);
    int aay = abs(ay);
    int aaz = abs(az);
    
    if (aax >= aay && aax >= aaz){
      if(ax > 0){
        return 5;
      }
      else{
        return 0;
      }
    }else if(aay >= aax && aay >= aaz){
      if(ay > 0){
        return 2;
      }
      else{
        return 4;
      }
    }else if(aaz >= aax && aaz >= aay){
      if(az > 0){
        return 3;
      }
      else{
        return 1;
      }
    }
}


int ModeManager::getAccelX() {
  return ax;
}
int ModeManager::getAccelY() {
  return ay;
}
int ModeManager::getAccelZ() {
  return az;
}
