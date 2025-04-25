/*
 * Game_Play.c
 *
 *  Created on: Apr 25, 2025
 *      Author: Knnn
 */

#include "Game_Play.h"

void Game_Play_ROBOT_2(){
	if(Str_PS2.attackBtnBit.attack1 == 1){ //D3
		digitalWrite("PE07", 1);
	}else{
		digitalWrite("PE07", 0);
	}

	if(Str_PS2.attackBtnBit.attack3 == 1){ //D4
		digitalWrite("PB00", 1);
	}else{
		digitalWrite("PB00", 0);
	}

	if(Str_PS2.attackBtnBit.attack4 == 1){ //D5
		digitalWrite("PE13", 1);
	}else{
		digitalWrite("PE13", 0);
	}
}

void Game_Play_ROBOT_1(){
	//องศาที่ยิง
	if(Str_PS2.moveBtnBit.move4 == 1){
		digitalWrite("PE10", 1);
		digitalWrite("PE08", 0);
	}else{
		digitalWrite("PE10", 0);
		digitalWrite("PE08", 1);
	}

	if(Str_PS2.attackBtnBit.attack2 == 1){
		digitalWrite("PE07", 1);
		digitalWrite("PB00", 1);
		digitalWrite("PE15", 1);
	}else{
		digitalWrite("PE07", 0);
		digitalWrite("PB00", 0);
		digitalWrite("PE15", 0);
	}

	if((Str_PS2.attackBtnBit.attack3 == 1) && (Str_PS2.attackBtnBit.attack4 == 0)){
		Motor_DutyCycle_EXTRA1(-3924);
		Motor_DutyCycle_EXTRA2(3924);
	}else if((Str_PS2.attackBtnBit.attack3 == 0) && (Str_PS2.attackBtnBit.attack4 == 1)){
		Motor_DutyCycle_EXTRA1(-2000);
		Motor_DutyCycle_EXTRA2(2000);
	}else{
		Motor_DutyCycle_EXTRA1(0);
		Motor_DutyCycle_EXTRA2(0);
	}

	if (Str_PS2.moveBtnBit.set2 == 1) {
		Motor_DutyCycle_EXTRA1(-2000);
		Motor_DutyCycle_EXTRA2(2000);
	}


}
