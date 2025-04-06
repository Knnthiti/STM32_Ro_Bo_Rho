/*
 * Inverse_Kinematics.c
 *
 *  Created on: Nov 6, 2024
 *      Author: Knnn
 */
#include "Inverse_Kinematics.h"

float Lx_;
float Ly_;
float Radius_wheel_;

void Setup_Inverse_Kinematic(float Lx ,float Ly ,float Radius_wheel){
	Lx_ = Lx;
	Ly_ = Ly;
	Radius_wheel_ = Radius_wheel;
}

float w_LF = 0.0f;
float w_LB = 0.0f;
float w_RF = 0.0f;
float w_RB = 0.0f;

void Inverse_Kinematic(float Vx ,float Vy ,float wz){
	w_LF = (Vx - Vy - (Lx_ +Ly_)*wz)/Radius_wheel_;
	w_RF = -(Vx + Vy + (Lx_ +Ly_)*wz)/Radius_wheel_;
	w_LB = (Vx + Vy - (Lx_ +Ly_)*wz)/Radius_wheel_;
	w_RB = -(Vx - Vy + (Lx_ +Ly_)*wz)/Radius_wheel_;
}

float get_w_LF(){
	return w_LF;
}

float get_w_LB(){
	return w_LB;
}

float get_w_RF(){
	return w_RF;
}

float get_w_RB(){
	return w_RB;
}

float map(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
    return toLow + (toHigh - toLow) * ((value - fromLow) / (fromHigh - fromLow));
}
