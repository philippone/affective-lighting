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


void ModeManager::getCurrentMode() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    
}


int ModeManager::getAccelX() {
  return ax;
}
