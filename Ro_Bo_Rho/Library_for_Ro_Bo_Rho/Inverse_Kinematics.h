/*
 * Inverse_Kinematics.h
 *
 *  Created on: Nov 6, 2024
 *      Author: Knnn
 */

#ifndef INVERSE_KINEMATICS_H_
#define INVERSE_KINEMATICS_H_

#include "stdint.h"
#include "stdlib.h"

#include "math.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

//https://ecam-eurobot.github.io/Tutorials/mechanical/mecanum.html
//inverse kinematic equations mecanum wheel

extern float Lx_;
extern float Ly_;
extern float Radius_wheel_;

void Setup_Inverse_Kinematic(float Lx ,float Ly ,float Radius_wheel);

extern float w_LF;
extern float w_LB;
extern float w_RF;
extern float w_RB;

void Inverse_Kinematic(float Vx ,float Vy ,float wz);

float get_w_LF();
float get_w_LB();
float get_w_RF();
float get_w_RB();

float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);

#endif /* INVERSE_KINEMATICS_H_ */
