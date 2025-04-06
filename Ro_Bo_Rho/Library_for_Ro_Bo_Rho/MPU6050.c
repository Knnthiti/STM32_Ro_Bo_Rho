/*
 * MPU6050.c
 *
 *  Created on: Nov 1, 2024
 *      Author: Knnn
 */
#include"MPU6050.h"

uint8_t _addr = 0;

uint8_t Scan_I2C(I2C_HandleTypeDef *I2Cinstance){
	HAL_StatusTypeDef result;
	for (uint8_t i = 1; i < 128; i++)
	{
	    result = HAL_I2C_IsDeviceReady(I2Cinstance, (uint16_t)(i<<1), 2, 100);
	    if (result == HAL_OK){
	        _addr = i;
	    }
	}

	return _addr;
}

I2C_HandleTypeDef* I2C_MPU6050;

void Setup_MPU6050(I2C_HandleTypeDef *I2Cinstance){
		I2C_MPU6050 = I2Cinstance;

		// power management register 0X6B we should write all 0's to wake the sensor up
		uint8_t Data = 0;
		HAL_I2C_Mem_Write(I2C_MPU6050, MPU6050_ADDR, power_management, 1, &Data, 1, 2000);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		Data = 0x07;
		HAL_I2C_Mem_Write(I2C_MPU6050, MPU6050_ADDR, DATA_RATE, 1, &Data, 1, 2000);

		Data = 0x03;
		HAL_I2C_Mem_Write(I2C_MPU6050, MPU6050_ADDR, REG_DLPFCONF, 1, &Data, 1, 2000);

		// Set accelerometer configuration in ACCEL_CONFIG Register
		Data = 18;  // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> ± 2g
		HAL_I2C_Mem_Write(I2C_MPU6050, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, 2000);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		Data = 18;  // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> ± 250 ̐/s
		HAL_I2C_Mem_Write(I2C_MPU6050, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, 2000);


		MPU6050_calib();
}

MPU6050 imu_data;

float gyro_offset = 0;

void ReadMPU6050(){
	uint8_t Rec_Data[6];
	// Read 6 BYTES of data starting from ACCEL_XOUT_H (0x3B) register
	HAL_I2C_Mem_Read (I2C_MPU6050, MPU6050_ADDR, 0x3B, 1, Rec_Data, 6, 1000);

	imu_data.Ax = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	imu_data.Ay = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	imu_data.Az = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

	uint8_t data[6];

	// Read 6 BYTES of data starting from GYRO_XOUT_H register
	HAL_I2C_Mem_Read (I2C_MPU6050, MPU6050_ADDR, GYRO_XOUT_H, 1, data, 6, 1000);

	// Step 3: Combine the high and low bytes into 16-bit values
	imu_data.gx = (int16_t)(data[0] << 8 | data[1]);  // X-axis gyroscope data
	imu_data.gy = (int16_t)(data[2] << 8 | data[3]);  // Y-axis gyroscope data
	imu_data.gz = (int16_t)(data[4] << 8 | data[5]);  // Z-axis gyroscope data

	imu_data.gz = imu_data.gz - gyro_offset;
}

//int16_t get_gx(){
//	return imu_data.gx;
//}
//
//int16_t get_gy(){
//	return imu_data.gy;
//}
//
//int16_t get_gz(){
//	return imu_data.gz;
//}


float gyro_raw = 0;

void MPU6050_calib(){
	for(uint16_t i=0; i < 2000; i++){
		ReadMPU6050();
		gyro_raw += imu_data.gz;
		HAL_Delay(1);
	}
	gyro_offset = ((float)gyro_raw)/2000.0f;
}

//long currentTime = 0;
//float dt_yak = 0.0f;
//long lastTime = 0;
#define freq_MPU6050 100

float angularZ = 0.0f;

float DegreeZ = 0.0f;

float getDegreeZ(){
	ReadMPU6050();
//	currentTime = uwTick;
//	dt_yak = (float)((currentTime - lastTime) / 1000.0f);
//	lastTime = currentTime;

//	angularZ = ((float)(imu_data.gz - gyro_offset)) / 131.0f * dt_yak;
	angularZ = ((float)(imu_data.gz) / (131.0f * freq_MPU6050));

	DegreeZ += angularZ;  //returns the absolute value of the z-axis rotazion integral

	return DegreeZ;
}

float RadianZ = 0.0f;

float getRadianZ(){
	getDegreeZ();
	RadianZ = DegreeZ * Degree_to_Radian;

	return RadianZ;
}
