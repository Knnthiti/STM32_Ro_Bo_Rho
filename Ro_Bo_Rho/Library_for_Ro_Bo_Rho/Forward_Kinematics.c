/*
 * Forward_Kinematics.c
 *
 *  Created on: Nov 6, 2024
 *      Author: Knnn
 */
#include "Forward_Kinematics.h"

float _Lx;
float _Ly;
float _Radius_wheel;

void Setup_Forward_Kinematic(float Lx ,float Ly ,float Radius_wheel){
	_Lx = Lx;
	_Ly = Ly;
	_Radius_wheel = Radius_wheel;
}

float _Vx = 0;
float _Vy = 0;
float _Vz = 0;

void Odometry_Forward_Kinematic(float w_LF, float w_LB, float w_RF, float w_RB){
	//w_LF w_LB w_RF and w_RB represent the angular velocities.

	_Vx = (w_LF + w_RF + w_LB + w_RB) * (_Radius_wheel / 4.0f);
	_Vy = ((-w_LF + w_RF + w_LB - w_RB) * (_Radius_wheel / 4.0f));
	_Vz = (-w_LF + w_RF - w_LB + w_RB) * (_Radius_wheel / (4.0f * (_Lx + _Ly)));
}

float get_Vx(){
	return _Vx;
}

float get_Vy(){
	return _Vy;
}

float get_Vz(){
	return _Vz;
}

uint8_t __freq = 100;

float _Pos_X = 0.0f;
float _Pos_Y = 0.0f;
float _Pos_Z = 0.0f;

void Setup_frequency_Forward_Kinematic(uint8_t freq){
	__freq = freq;
}

void Setup_ZERO_Pos(){
	_Pos_X = 0.0f;
	_Pos_Y = 0.0f;
	_Pos_Z = 0.0f;
}

void Position_Robot(){
	//Heading_Robot is rad/s
	_Pos_Z += _Vz / __freq;
	_Pos_X += ((_Vx * cos(_Pos_Z)) - (_Vy * sin(_Pos_Z))) / __freq;
	_Pos_Y += ((_Vx * sin(_Pos_Z)) + (_Vy * cos(_Pos_Z))) / __freq;

}

float get_Sx(){
	return _Pos_X;
}

float get_Sy(){
	return _Pos_Y;
}

float get_Sz(){
	return _Pos_Z;
}
