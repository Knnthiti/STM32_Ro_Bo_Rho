/*
 * Ramp_Robot.h
 *
 *  Created on: Nov 8, 2024
 *      Author: Knnn
 */

#ifndef RAMP_ROBOT_H_
#define RAMP_ROBOT_H_

#include "stdint.h"
#include "stdlib.h"

#include "math.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

////////////////////////////////////////////////////////////////////////
extern float _r;
extern float _Rad_s;

void Cartesian_to_Polar(float Px, float Py);

float get_Polar_r();
float get_Polar_Rad_s();

////////////////////////////////////////////////////////////////////////
extern float _V_r;
extern float _V_Rad_s;

void Setup_Ramp_Polar_r(float Kp_r ,float Ki_r ,float Kd_r ,float max_Vr);

void Ramp_Polar_r(float Diff_r);
void Polar_Rad_s(float Rad_s ,float head_ing);

float get_V_r();
float get_V_Rad_s();

////////////////////////////////////////////////////////////////////////
extern float __Vx;
extern float __Vy;

void Polar_to_Cartesian(float V_r ,float V_Rad_s);

float get_Cartesian_Vx();
float get_Cartesian_Vy();

extern float __Vz;
void Setup_Ramp_Vz(float Kp_Vz ,float Ki_Vz ,float Kd_Vz,float max_Vz);
float Ramp_Vz(float Set_point_Rad ,float head_ing);

#endif /* RAMP_ROBOT_H_ */
