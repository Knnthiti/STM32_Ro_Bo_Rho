/*
 * MPU6050.h
 *
 *  Created on: Nov 1, 2024
 *      Author: Knnn
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "stdint.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#include "MPU6050.h"

//-https://cdn.sparkfun.com/datasheets/Sensors/Accelerometers/RM-MPU-6000A.pdf
//-https://controllerstech.com/how-to-interface-mpu6050-gy-521-with-stm32/


#define MPU6050_ADDR 0x68<<1   // address I2C is MPU6050

#define power_management 0x6B
#define DATA_RATE 0x19

#define REG_DLPFCONF 0x1A

#define ACCEL_CONFIG_REG 0x1C
#define GYRO_CONFIG_REG 0x1B

#define GYRO_XOUT_H 0x43

#define Degree_to_Radian 0.017453f

#define ITG_TO_RAD    0.00121414f // (2000/28750 degree*s^-1/LSB) * 0.0174533 (rad/degree)

uint8_t Scan_I2C(I2C_HandleTypeDef *I2Cinstance);

void Setup_MPU6050(I2C_HandleTypeDef *I2Cinstance);

void MPU6050_calib();

typedef struct{
	int16_t gx;
	int16_t gy;
	int16_t gz;

	int16_t Ax;
	int16_t Ay;
	int16_t Az;
}MPU6050;

extern MPU6050 imu_data;

void ReadMPU6050();

int16_t get_gx();
int16_t get_gy();
int16_t get_gz();

extern float DegreeZ;
float getDegreeZ();

extern float RadianZ;
float getRadianZ();

#endif /* MPU6050_H_ */
