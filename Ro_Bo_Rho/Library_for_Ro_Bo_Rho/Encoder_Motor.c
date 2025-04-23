/*
 * Encoder.c
 *
 *  Created on: Nov 1, 2024
 *      Author: Knnn
 */
#include <Encoder_Motor.h>

//pin for Ro_Bo_Rho
TIM_HandleTypeDef *EN_LF; //_TIM_5
TIM_HandleTypeDef *EN_LB; //_TIM_1
TIM_HandleTypeDef *EN_RF; //_TIM_8
TIM_HandleTypeDef *EN_RB; //_TIM_4
TIM_HandleTypeDef *EN_X; //_TIM_2
TIM_HandleTypeDef *EN_Y; //_TIM_3


TIM_HandleTypeDef *LF_PWM; //_TIM_14_CH1
TIM_HandleTypeDef *LB_PWM; //_TIM_12_CH1
TIM_HandleTypeDef *RF_PWM; //_TIM_11_CH1
TIM_HandleTypeDef *RB_PWM; //_TIM_12_CH2
TIM_HandleTypeDef *EXTRA1_PWM; //_TIM_9_CH1
TIM_HandleTypeDef *EXTRA2_PWM; //_TIM_10_CH1


///////////////////////////////////////////////////////////Setup_MOTOR/////////////////////////////////////////////////////

int16_t DutyCycle_LF_MAX = 0;
int16_t DutyCycle_LB_MAX = 0;
int16_t DutyCycle_RF_MAX = 0;
int16_t DutyCycle_RB_MAX = 0;
int16_t DutyCycle_EXTRA1_MAX = 0;
int16_t DutyCycle_EXTRA2_MAX = 0;

char* IN_LF;
char* IN_LB;
char* IN_RF;
char* IN_RB;
char* IN_EXTRA1;
char* IN_EXTRA2;

void Motor_setup_LF(TIM_HandleTypeDef *_TIM_14_CH1 ,TIM_HandleTypeDef *_TIM_5  ,char* _IN_LF){
	//Motor_setup_LF(PWM_TIM ,Encoder_TIM   ,IN_LF);

	LF_PWM = _TIM_14_CH1;
	EN_LF      = _TIM_5;

	HAL_TIM_PWM_Start(LF_PWM, TIM_CHANNEL_1);       //PWM
	HAL_TIM_Encoder_Start(EN_LF , TIM_CHANNEL_ALL);     //Encoder

	IN_LF = _IN_LF;

	DutyCycle_LF_MAX = (LF_PWM->Init.Period);

}

void Motor_setup_LB(TIM_HandleTypeDef *_TIM_12_CH1 ,TIM_HandleTypeDef *_TIM_1  ,char* _IN_LB){
    //Motor_setup_LB(PWM_TIM ,Encoder_TIM  ,IN1_LB ,IN2_LB);

	LB_PWM = _TIM_12_CH1;
	EN_LB      = _TIM_1;

	HAL_TIM_PWM_Start(LB_PWM, TIM_CHANNEL_1);       //PWM
	HAL_TIM_Encoder_Start(EN_LB , TIM_CHANNEL_ALL);     //Encoder

	IN_LB = _IN_LB;

	DutyCycle_LB_MAX = (LB_PWM->Init.Period);

}

void Motor_setup_RF(TIM_HandleTypeDef *_TIM_11_CH1  ,TIM_HandleTypeDef *_TIM_8  ,char* _IN_RF){
    //Motor_setup_RF(PWM_TIM ,Encoder_TIM   ,IN1_RF ,IN2_RF);

	RF_PWM = _TIM_11_CH1;
	EN_RF  = _TIM_8;

	HAL_TIM_PWM_Start(RF_PWM, TIM_CHANNEL_1);           //PWM
	HAL_TIM_Encoder_Start(EN_RF , TIM_CHANNEL_ALL);     //Encoder

	IN_RF = _IN_RF;

	DutyCycle_RF_MAX = (RF_PWM->Init.Period);

}

void Motor_setup_RB(TIM_HandleTypeDef *_TIM_12_CH2   ,TIM_HandleTypeDef *_TIM_4 ,char* _IN_RB){
    //Motor_setup_RB(PWM_TIM ,Encoder_TIM   ,IN1_RB ,IN2_RB);

	RB_PWM = _TIM_12_CH2;
	EN_RB  = _TIM_4;

	HAL_TIM_PWM_Start(RB_PWM, TIM_CHANNEL_2);            //PWM
	HAL_TIM_Encoder_Start(EN_RB , TIM_CHANNEL_ALL);      //Encoder

	IN_RB = _IN_RB;

	DutyCycle_RB_MAX = (RB_PWM->Init.Period);

}

void Motor_setup_EXTRA1(TIM_HandleTypeDef *_TIM_9_CH1  ,TIM_HandleTypeDef *_TIM_3  ,char* _IN_EXTRA1){
    //Motor_setup_RB(PWM_TIM ,Encoder_TIM   ,IN1_RB ,IN2_RB);

	EXTRA1_PWM = _TIM_9_CH1;
	EN_X  = _TIM_3;

	HAL_TIM_PWM_Start(EXTRA1_PWM, TIM_CHANNEL_1);            //PWM
	HAL_TIM_Encoder_Start(EN_X , TIM_CHANNEL_ALL);      //Encoder

	IN_EXTRA1 = _IN_EXTRA1;

	DutyCycle_EXTRA1_MAX = (EXTRA1_PWM->Init.Period);

}

void Motor_setup_EXTRA2(TIM_HandleTypeDef *_TIM_10_CH1  ,TIM_HandleTypeDef *_TIM_2 ,char* _IN_EXTRA2){
    //Motor_setup_RB(PWM_TIM ,Encoder_TIM   ,IN1_RB ,IN2_RB);

	EXTRA2_PWM = _TIM_10_CH1;
	EN_Y  = _TIM_2;

	HAL_TIM_PWM_Start(EXTRA2_PWM, TIM_CHANNEL_1);            //PWM
	HAL_TIM_Encoder_Start(EN_Y , TIM_CHANNEL_ALL);      //Encoder

	IN_EXTRA2 = _IN_EXTRA2;

	DutyCycle_EXTRA2_MAX = (EXTRA2_PWM->Init.Period);

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////PID///////////////////////////////////////////////////////////////

int16_t getCount(TIM_HandleTypeDef *TIM){
	int16_t count = ((int16_t)(TIM->Instance->CNT));

	return count;
}

int16_t Present_Count[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
int16_t Past_Count[6] = {0 ,0 ,0 ,0 ,0 ,0};    //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2

uint16_t _freq = 100;

float _RPM[6] = {0 ,0 ,0 ,0 ,0 ,0}; //Speed   //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2

uint16_t CPR = 68;

void Setup_CPR(uint16_t _CPR){
	CPR = _CPR;
}

uint16_t Gear_Ratio = 27;

void Setup_Gear_Ratio(uint16_t _Gear_Ratio){
	Gear_Ratio = _Gear_Ratio;
}

void Setup_frequency_Motor(uint16_t freq){
	_freq = freq;
}

float getRPM_to_Rad_s(float RPM){
	float Rad_s = RPM * 0.10472f;

	return Rad_s;
}

float getRad_s_to_RPM(float Rad_s){
	float RPM__ = Rad_s * 9.549297f;

	return RPM__;
}

float getRPM_TIM_Wheel(TIM_HandleTypeDef *TIM ,uint8_t _Wheel){
	Present_Count[_Wheel] = (int16_t)getCount(TIM);

	// V = count/t = count*freq
	_RPM[_Wheel] = (float)((int16_t)(Present_Count[_Wheel] - Past_Count[_Wheel]) * _freq);
	_RPM[_Wheel] = (float)(((_RPM[_Wheel]* 60.0f)/CPR )/Gear_Ratio);

	Past_Count[_Wheel] = Present_Count[_Wheel];

	return _RPM[_Wheel];
}


float Kp_Wheel[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
float Ki_Wheel[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
float Kd_Wheel[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2

float min_speed[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
float max_speed[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2


void Setup_PID_LF(float Kp_LF ,float Ki_LF ,float Kd_LF ,float min_speed_LF ,float max_speed_LF){
	Kp_Wheel[0] = Kp_LF;
	Ki_Wheel[0] = Ki_LF;
	Kd_Wheel[0] = Kd_LF;

	min_speed[0] = min_speed_LF;
	max_speed[0] = max_speed_LF;
}

void Setup_PID_LB(float Kp_LB ,float Ki_LB ,float Kd_LB ,float min_speed_LB ,float max_speed_LB){
	Kp_Wheel[1] = Kp_LB;
	Ki_Wheel[1] = Ki_LB;
	Kd_Wheel[1] = Kd_LB;

	min_speed[1] = min_speed_LB;
	max_speed[1] = max_speed_LB;
}

void Setup_PID_RF(float Kp_RF ,float Ki_RF ,float Kd_RF ,float min_speed_RF ,float max_speed_RF){
	Kp_Wheel[2] = Kp_RF;
	Ki_Wheel[2] = Ki_RF;
	Kd_Wheel[2] = Kd_RF;

	min_speed[2] = min_speed_RF;
	max_speed[2] = max_speed_RF;
}

void Setup_PID_RB(float Kp_RB ,float Ki_RB ,float Kd_RB ,float min_speed_RB ,float max_speed_RB){
	Kp_Wheel[3] = Kp_RB;
	Ki_Wheel[3] = Ki_RB;
	Kd_Wheel[3] = Kd_RB;

	min_speed[3] = min_speed_RB;
	max_speed[3] = max_speed_RB;
}

void Setup_PID_EXTRA1(float Kp_EXTRA1 ,float Ki_EXTRA1 ,float Kd_EXTRA1 ,float min_speed_EXTRA1 ,float max_speed_EXTRA1){
	Kp_Wheel[4] = Kp_EXTRA1;
	Ki_Wheel[4] = Ki_EXTRA1;
	Kd_Wheel[4] = Kd_EXTRA1;

	min_speed[4] = min_speed_EXTRA1;
	max_speed[4] = max_speed_EXTRA1;
}

void Setup_PID_EXTRA2(float Kp_EXTRA2 ,float Ki_EXTRA2 ,float Kd_EXTRA2 ,float min_speed_EXTRA2 ,float max_speed_EXTRA2){
	Kp_Wheel[5] = Kp_EXTRA2;
	Ki_Wheel[5] = Ki_EXTRA2;
	Kd_Wheel[5] = Kd_EXTRA2;

	min_speed[5] = min_speed_EXTRA2;
	max_speed[5] = max_speed_EXTRA2;
}



float Error_Speed[6]  = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2

float Proportional[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
float Integnator[6]   = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
float Derivative[6]   = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2

float Past_Error[6]   = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2

float Output_PID[6]    = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2

float PID_Speed(float _Setpoint ,int16_t RPM ,uint8_t _Wheel){
//	switch (_Wheel) {
//	  case 0 : getRPM_TIM_Wheel(EN_LF ,LF ); break;
//	  case 1 : getRPM_TIM_Wheel(EN_LB ,LB ); break;
//	  case 2 : getRPM_TIM_Wheel(EN_RF ,RF ); break;
//	  case 3 : getRPM_TIM_Wheel(EN_RB ,RB ); break;
//	  case 4 : getRPM_TIM_Wheel(EN_X ,EXTRA1 ); break;
//	  case 5 : getRPM_TIM_Wheel(EN_Y ,EXTRA2 ); break;
//	}

//	Error_Speed[_Wheel] = _Setpoint-_RPM[_Wheel];
	Error_Speed[_Wheel] = _Setpoint-RPM;

	Proportional[_Wheel] = Error_Speed[_Wheel];
	Integnator[_Wheel]   += Error_Speed[_Wheel];
	Derivative[_Wheel]   = Error_Speed[_Wheel] - Past_Error[_Wheel];

	Past_Error[_Wheel] = Error_Speed[_Wheel];

	Output_PID[_Wheel]  = (float)((Proportional[_Wheel]*Kp_Wheel[_Wheel]) + (Integnator[_Wheel]*Ki_Wheel[_Wheel]) + (Derivative[_Wheel]*Kd_Wheel[_Wheel]));


	return Output_PID[_Wheel];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////Motor////////////////////////////////////////////////////////////////////
void Motor_DutyCycle_LF(int16_t DutyCycle_LF){
	if (DutyCycle_LF > DutyCycle_LF_MAX) {
	    DutyCycle_LF = DutyCycle_LF_MAX;
	} else if (DutyCycle_LF < -DutyCycle_LF_MAX) {
		DutyCycle_LF = -DutyCycle_LF_MAX;
	}

	LF_PWM->Instance->CCR1 = (DutyCycle_LF > 0) ? (int16_t)DutyCycle_LF : (DutyCycle_LF_MAX + (int16_t)DutyCycle_LF);

	digitalWrite(IN_LF , (DutyCycle_LF < 0) ? 1 : 0);

	if(DutyCycle_LF == 0){
	   LF_PWM->Instance->CCR1 = 0;
	   digitalWrite(IN_LF ,0);
	}
}

void Motor_DutyCycle_LB(int16_t DutyCycle_LB){
	DutyCycle_LB = -DutyCycle_LB;
	if (DutyCycle_LB > DutyCycle_LB_MAX) {
		DutyCycle_LB = DutyCycle_LB_MAX;
	} else if (DutyCycle_LB < -DutyCycle_LB_MAX) {
		DutyCycle_LB = -DutyCycle_LB_MAX;
	}

	LB_PWM->Instance->CCR1 = (DutyCycle_LB > 0) ? (int16_t)DutyCycle_LB : (DutyCycle_LB_MAX + (int16_t)DutyCycle_LB);

	digitalWrite(IN_LB , (DutyCycle_LB < 0) ? 1 : 0);

	if(DutyCycle_LB == 0){
	   LB_PWM->Instance->CCR1 = 0;
	   digitalWrite(IN_LB ,0);
	}
}

void Motor_DutyCycle_RF(int16_t DutyCycle_RF){
	DutyCycle_RF = -DutyCycle_RF;
	if (DutyCycle_RF > DutyCycle_RF_MAX) {
		DutyCycle_RF = DutyCycle_RF_MAX;
	} else if (DutyCycle_RF < -DutyCycle_RF_MAX) {
		DutyCycle_RF = -DutyCycle_RF_MAX;
	}

	RF_PWM->Instance->CCR1 = (DutyCycle_RF > 0) ? (int16_t)DutyCycle_RF : (DutyCycle_RF_MAX + (int16_t)DutyCycle_RF);

	digitalWrite(IN_RF , (DutyCycle_RF < 0) ? 1 : 0);

	if(DutyCycle_RF == 0){
	   RF_PWM->Instance->CCR1 = 0;
	   digitalWrite(IN_RF ,0);
	}
}

void Motor_DutyCycle_RB(int16_t DutyCycle_RB){
	if (DutyCycle_RB > DutyCycle_RB_MAX) {
		DutyCycle_RB = DutyCycle_RB_MAX;
	} else if (DutyCycle_RB < -DutyCycle_RB_MAX) {
	    DutyCycle_RB = -DutyCycle_RB_MAX;
	}

	RB_PWM->Instance->CCR2 = (DutyCycle_RB > 0) ? (int16_t)DutyCycle_RB : (DutyCycle_RB_MAX + (int16_t)DutyCycle_RB);

	digitalWrite(IN_RB , (DutyCycle_RB < 0) ? 1 : 0);

	if(DutyCycle_RB == 0){
	    RB_PWM->Instance->CCR2 = 0;
		digitalWrite(IN_RB ,0);
	}
}

void Motor_DutyCycle_EXTRA1(int16_t DutyCycle_EXTRA1){
	if (DutyCycle_EXTRA1 > DutyCycle_EXTRA1_MAX) {
		DutyCycle_EXTRA1 = DutyCycle_EXTRA1_MAX;
	} else if (DutyCycle_EXTRA1 < -DutyCycle_EXTRA1_MAX) {
		DutyCycle_EXTRA1 = -DutyCycle_EXTRA1_MAX;
	}

	EXTRA1_PWM->Instance->CCR1 = (DutyCycle_EXTRA1 > 0) ? (int16_t)DutyCycle_EXTRA1 : (DutyCycle_EXTRA1_MAX + (int16_t)DutyCycle_EXTRA1);

	digitalWrite(IN_EXTRA1 , (DutyCycle_EXTRA1 < 0) ? 1 : 0);

	if(DutyCycle_EXTRA1 == 0){
		EXTRA1_PWM->Instance->CCR1 = 0;
	    digitalWrite(IN_EXTRA1 ,0);
	}
}

void Motor_DutyCycle_EXTRA2(int16_t DutyCycle_EXTRA2){
	if (DutyCycle_EXTRA2 > DutyCycle_EXTRA2_MAX) {
		DutyCycle_EXTRA2 = DutyCycle_EXTRA2_MAX;
	} else if (DutyCycle_EXTRA2 < -DutyCycle_EXTRA2_MAX) {
		DutyCycle_EXTRA2 = -DutyCycle_EXTRA2_MAX;
	}

	EXTRA2_PWM->Instance->CCR1 = (DutyCycle_EXTRA2 > 0) ? (int16_t)DutyCycle_EXTRA2 : (DutyCycle_EXTRA2_MAX + (int16_t)DutyCycle_EXTRA2);

	digitalWrite(IN_EXTRA2 , (DutyCycle_EXTRA2 < 0) ? 1 : 0);

	if(DutyCycle_EXTRA2 == 0){
	     EXTRA2_PWM->Instance->CCR1 = 0;
		 digitalWrite(IN_EXTRA2 ,0);
	}
}

int16_t Duty_Cycle[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2

float Motor_Speed_LF(int16_t RPM_INPUT ,float RPM_LF){
	if (RPM_LF > max_speed[0]) {
	   RPM_LF = max_speed[0];
	} else if (RPM_LF < -max_speed[0]) {
	   RPM_LF = -max_speed[0];
	}

	PID_Speed(RPM_INPUT ,RPM_LF , 0);

	Duty_Cycle[0] = (int16_t)((Output_PID[0] / ((float)(max_speed[0] - min_speed[0]))) * DutyCycle_LF_MAX);

	Motor_DutyCycle_LF(Duty_Cycle[0]);

//	return _RPM[0];
	return Output_PID[0];
}

float Motor_Speed_LB(int16_t RPM_INPUT ,float RPM_LB){
	if (RPM_LB > max_speed[1]) {
	   RPM_LB = max_speed[1];
	} else if (RPM_LB < -max_speed[1]) {
	   RPM_LB = -max_speed[1];
	}

	PID_Speed(RPM_INPUT ,RPM_LB ,1);

	Duty_Cycle[1] = (int16_t)((Output_PID[1]/((float)(max_speed[1] - min_speed[1]))) * DutyCycle_LB_MAX);

	Motor_DutyCycle_LB(Duty_Cycle[1]);

//	return _RPM[1];
	return Output_PID[1];
}

float Motor_Speed_RF(int16_t RPM_INPUT ,float RPM_RF){
	if (RPM_RF > max_speed[2]) {
	   RPM_RF = max_speed[2];
	} else if (RPM_RF < -max_speed[2]) {
	   RPM_RF = -max_speed[2];
	}

	PID_Speed(RPM_INPUT ,RPM_RF ,2);

	Duty_Cycle[2] = (int16_t)((Output_PID[2]/((float)(max_speed[2] - min_speed[2]))) * DutyCycle_RF_MAX);

	Motor_DutyCycle_RF(Duty_Cycle[2]);

//	return _RPM[2];
	return Output_PID[2];
}

float Motor_Speed_RB(int16_t RPM_INPUT ,float RPM_RB){
	if (RPM_RB > max_speed[3]) {
		RPM_RB = max_speed[3];
	} else if (RPM_RB < -max_speed[3]) {
		RPM_RB = -max_speed[3];
	}

	PID_Speed(RPM_INPUT ,RPM_RB ,3);

	Duty_Cycle[3] = (int16_t)((Output_PID[3]/((float)(max_speed[3] - min_speed[3]))) * DutyCycle_RB_MAX);

	Motor_DutyCycle_RB(Duty_Cycle[3]);

//	return _RPM[3];
	return Output_PID[3];
}

float Motor_Speed_EXTRA1(int16_t RPM_INPUT ,float RPM_EXTRA1){
	if (RPM_EXTRA1 > max_speed[4]) {
		RPM_EXTRA1 = max_speed[4];
	} else if (RPM_EXTRA1 < -max_speed[4]) {
		RPM_EXTRA1 = -max_speed[4];
	}

	PID_Speed(RPM_INPUT ,RPM_EXTRA1 ,4);

	Duty_Cycle[4] = (int16_t)((Output_PID[4]/((float)(max_speed[4] - min_speed[4]))) * DutyCycle_EXTRA1_MAX);

	Motor_DutyCycle_EXTRA1(Duty_Cycle[4]);

//	return _RPM[4];
	return Output_PID[4];
}

float Motor_Speed_EXTRA2(int16_t RPM_INPUT ,float RPM_EXTRA2){
	if (RPM_EXTRA2 > max_speed[5]) {
		RPM_EXTRA2 = max_speed[5];
	} else if (RPM_EXTRA2 < -max_speed[5]) {
		RPM_EXTRA2 = -max_speed[5];
	}

	PID_Speed(RPM_INPUT ,RPM_EXTRA2 ,5);

	Duty_Cycle[5] = (int16_t)((Output_PID[5]/((float)(max_speed[5] - min_speed[5]))) * DutyCycle_EXTRA2_MAX);

	Motor_DutyCycle_EXTRA2(Duty_Cycle[5]);

//	return _RPM[5];
	return Output_PID[5];
}

void digitalWrite(char* _PIN , uint8_t vlue){
	uint8_t PIN = (_PIN[2] - '0') * 10 + (_PIN[3] - '0');

	if (_PIN[1] == 'A') {
	        switch (PIN) {
	            case 0: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, vlue); break;
	            case 1: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, vlue); break;
	            case 2: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, vlue); break;
	            case 3: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, vlue); break;
	            case 4: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, vlue); break;
	            case 5: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, vlue); break;
	            case 6: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, vlue); break;
	            case 7: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, vlue); break;
	            case 8: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, vlue); break;
	            case 9: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, vlue); break;
	            case 10: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, vlue); break;
	            case 11: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, vlue); break;
	            case 12: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, vlue); break;
	            case 13: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, vlue); break;
	            case 14: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, vlue); break;
	            case 15: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, vlue); break;
	        }
	    } else if (_PIN[1] == 'B') {
	        switch (PIN) {
	            case 0: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, vlue); break;
	            case 1: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, vlue); break;
	            case 2: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, vlue); break;
	            case 3: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, vlue); break;
	            case 4: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, vlue); break;
	            case 5: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, vlue); break;
	            case 6: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, vlue); break;
	            case 7: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, vlue); break;
	            case 8: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, vlue); break;
	            case 9: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, vlue); break;
	            case 10: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, vlue); break;
	            case 11: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, vlue); break;
	            case 12: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, vlue); break;
	            case 13: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, vlue); break;
	            case 14: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, vlue); break;
	            case 15: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, vlue); break;
	        }
	    } else if (_PIN[1] == 'C') {
	        switch (PIN) {
	            case 0: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, vlue); break;
	            case 1: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, vlue); break;
	            case 2: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, vlue); break;
	            case 3: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, vlue); break;
	            case 4: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, vlue); break;
	            case 5: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, vlue); break;
	            case 6: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, vlue); break;
	            case 7: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, vlue); break;
	            case 8: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, vlue); break;
	            case 9: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, vlue); break;
	            case 10: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, vlue); break;
	            case 11: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, vlue); break;
	            case 12: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, vlue); break;
	            case 13: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, vlue); break;
	            case 14: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, vlue); break;
	            case 15: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, vlue); break;
	        }
	    } else if (_PIN[1] == 'D') {
	        switch (PIN) {
	            case 0: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, vlue); break;
	            case 1: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, vlue); break;
	            case 2: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, vlue); break;
	            case 3: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, vlue); break;
	            case 4: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, vlue); break;
	            case 5: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, vlue); break;
	            case 6: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, vlue); break;
	            case 7: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, vlue); break;
	            case 8: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, vlue); break;
	            case 9: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, vlue); break;
	            case 10: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, vlue); break;
	            case 11: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, vlue); break;
	            case 12: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, vlue); break;
	            case 13: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, vlue); break;
	            case 14: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, vlue); break;
	            case 15: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, vlue); break;
	        }
	    } else if (_PIN[1] == 'E') {
	        switch (PIN) {
	            case 0: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, vlue); break;
	            case 1: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, vlue); break;
	            case 2: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, vlue); break;
	            case 3: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, vlue); break;
	            case 4: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, vlue); break;
	            case 5: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, vlue); break;
	            case 6: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, vlue); break;
	            case 7: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, vlue); break;
	            case 8: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, vlue); break;
	            case 9: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, vlue); break;
	            case 10: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, vlue); break;
	            case 11: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, vlue); break;
	            case 12: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, vlue); break;
	            case 13: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, vlue); break;
	            case 14: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, vlue); break;
	            case 15: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, vlue); break;
	        }
	    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

