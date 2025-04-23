/*
 * Encoder.h
 *
 *  Created on: Nov 1, 2024
 *      Author: Knnn
 */

#ifndef ENCODER_MOTOR_H_
#define ENCODER_MOTOR_H_

#include "stdint.h"
#include "stdlib.h"

#include "math.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#define LF 0
#define LB 1
#define RF 2
#define RB 3
#define EXTRA1 4
#define EXTRA2 5

extern float _RPM[6]; //Speed   //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2

void Motor_setup_LF(TIM_HandleTypeDef *_TIM_14_CH1 ,TIM_HandleTypeDef *_TIM_5  ,char* _IN_LF);
void Motor_setup_LB(TIM_HandleTypeDef *_TIM_15_CH1 ,TIM_HandleTypeDef *_TIM_1  ,char* _IN_LB);
void Motor_setup_RF(TIM_HandleTypeDef *_TIM_11_CH1 ,TIM_HandleTypeDef *_TIM_8  ,char* _IN_RF);
void Motor_setup_RB(TIM_HandleTypeDef *_TIM_12_CH2 ,TIM_HandleTypeDef *_TIM_4  ,char* _IN_RB);
void Motor_setup_EXTRA1(TIM_HandleTypeDef *_TIM_9_CH1     ,TIM_HandleTypeDef *_TIM_2  ,char* _IN_EXTRA1);
void Motor_setup_EXTRA2(TIM_HandleTypeDef *_TIM_10_CH1    ,TIM_HandleTypeDef *_TIM_3  ,char* _IN_EXTRA2);

void Setup_CPR(uint16_t CPR);

extern uint16_t Gear_Ratio;
void Setup_Gear_Ratio(uint16_t _Gear_Ratio);

void Motor_DutyCycle_LF(int16_t DutyCycle_LF);
void Motor_DutyCycle_LB(int16_t DutyCycle_LB);
void Motor_DutyCycle_RF(int16_t DutyCycle_RF);
void Motor_DutyCycle_RB(int16_t DutyCycle_RB);
void Motor_DutyCycle_EXTRA1(int16_t DutyCycle_EXTRA1);
void Motor_DutyCycle_EXTRA2(int16_t DutyCycle_EXTRA2);

void Setup_frequency_Motor(uint16_t freq);

int16_t getCount(TIM_HandleTypeDef *TIM);
float getRPM_TIM_Wheel(TIM_HandleTypeDef *TIM ,uint8_t _Wheel);


float getRPM_to_Rad_s(float RPM);
float getRad_s_to_RPM(float Rad_s);

void Setup_PID_LF(float Kp_LF ,float Ki_LF ,float Kd_LF ,float min_speed_LF ,float max_speed_LF);
void Setup_PID_LB(float Kp_LB ,float Ki_LB ,float Kd_LB ,float min_speed_LB ,float max_speed_LB);
void Setup_PID_RF(float Kp_RF ,float Ki_RF ,float Kd_RF ,float min_speed_RF ,float max_speed_RF);
void Setup_PID_RB(float Kp_RB ,float Ki_RB ,float Kd_RB ,float min_speed_RB ,float max_speed_RB);
void Setup_PID_EXTRA1(float Kp_EXTRA1 ,float Ki_EXTRA1 ,float Kd_EXTRA1 ,float min_speed_EXTRA1 ,float max_speed_EXTRA1);
void Setup_PID_EXTRA2(float Kp_EXTRA2 ,float Ki_EXTRA2 ,float Kd_EXTRA2 ,float min_speed_EXTRA2 ,float max_speed_EXTRA2);

float PID_Speed(float Setpoint, int16_t RPM_INPUT ,uint8_t Wheel);

float Motor_Speed_LF(int16_t RPM_INPUT ,float _RPM_LF);
float Motor_Speed_LB(int16_t RPM_INPUT ,float _RPM_LB);
float Motor_Speed_RF(int16_t RPM_INPUT ,float _RPM_RF);
float Motor_Speed_RB(int16_t RPM_INPUT ,float _RPM_RB);
float Motor_Speed_EXTRA1(int16_t RPM_INPUT ,float RPM_EXTRA1);
float Motor_Speed_EXTRA2(int16_t RPM_INPUT ,float RPM_EXTRA2);

void digitalWrite(char* _PIN, uint8_t vlue);
#endif /* ENCODER_MOTOR_H_ */
