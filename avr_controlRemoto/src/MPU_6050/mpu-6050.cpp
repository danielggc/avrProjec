#include "mpu-6050.hpp"



MPU6050::MPU6050(){
    twi_init();
}

void MPU6050::setClockSource(uint8_t source){

}

void  MPU6050::begin(){
    writeMPU6050(MPU6050_SMPLRT_DIV, 0x07);
    writeMPU6050(MPU6050_CONFIG, 0x00);
    writeMPU6050(MPU6050_GYRO_CONFIG, 0x18);
    writeMPU6050(MPU6050_ACCEL_CONFIG, 0x00);
    writeMPU6050(MPU6050_PWR_MGMT_1, 0x01);
    writeMPU6050(0x38,0x01);
    this->update();
    angleGyroX = 0;
    angleGyroY = 0;
    angleX = this->getAccAngleX();
    angleY = this->getAccAngleY();

}
void MPU6050::writeMPU6050(uint8_t  reg, uint8_t  data){
    twi_write(MPU6050_ADDR,&reg,2,NULL);
    twi_write(MPU6050_ADDR,&data,2,NULL);
}

void MPU6050::update(){
    writeMPU6050(0x3B,0xD1);
    uint8_t reg=0x3B;
    twi_write(MPU6050_ADDR,&reg,1,NULL);
	twi_read(MPU6050_ADDR,14,NULL);
    uint8_t *direccionTrasmicion=twi_wait();
    rawAccX = *direccionTrasmicion<< 8 | *direccionTrasmicion++;
    rawAccY = *direccionTrasmicion++ << 8 | *direccionTrasmicion++;
    rawAccZ = *direccionTrasmicion++ << 8 | *direccionTrasmicion++;
    rawTemp = *direccionTrasmicion++ << 8 | *direccionTrasmicion++;
    rawGyroX = *direccionTrasmicion++ << 8 | *direccionTrasmicion++;
    rawGyroY = *direccionTrasmicion++ << 8 | *direccionTrasmicion++;
    rawGyroZ = *direccionTrasmicion++ << 8 | *direccionTrasmicion++;

  temp = (rawTemp + 12412.0) / 340.0;

  accX = ((float)rawAccX) / 16384.0;
  accY = ((float)rawAccY) / 16384.0;
  accZ = ((float)rawAccZ) / 16384.0;

  angleAccX = atan2(accY, sqrt(accZ * accZ + accX * accX)) * 360 / 2.0 / PI;
  angleAccY = atan2(accX, sqrt(accZ * accZ + accY * accY)) * 360 / -2.0 / PI;

  gyroX = ((float)rawGyroX) / 65.5;
  gyroY = ((float)rawGyroY) / 65.5;
  gyroZ = ((float)rawGyroZ) / 65.5;

  gyroX -= gyroXoffset;
  gyroY -= gyroYoffset;
  gyroZ -= gyroZoffset;

  interval = 1;//(millis() - preInterval) * 0.001;

  angleGyroX += gyroX * interval;
  angleGyroY += gyroY * interval;
  angleGyroZ += gyroZ * interval;

  angleX = (gyroCoef * (angleX + gyroX * interval)) + (accCoef * angleAccX);
  angleY = (gyroCoef * (angleY + gyroY * interval)) + (accCoef * angleAccY);
  angleZ = angleGyroZ;

  preInterval = 0;//millis();

}