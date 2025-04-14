/*
 * app_ros_comm.h
 *
 *  Created on: Feb 17, 2025
 *      Author: Knnn
 */

#ifndef APP_ROS_COMM_H_
#define APP_ROS_COMM_H_

#include "stdint.h"
#include "stdlib.h"

#include "Encoder_Motor.h"
#include "MPU6050.h"
#include <usbd_cdc_if.h>

#define ROS_COMM_RX_SIZE    13
#define ROS_COMM_TX_SIZE    32

#define COMM_TIMEOUT_MS (40-1) // 40ms communication timeout

typedef struct __attribute__((packed)) {
  // Send by PC
  uint8_t rbcHeader[2];

  union {
    uint8_t reg;
    struct {
      uint8_t address : 5;
      uint8_t type : 2;
      uint8_t rw : 1;
    } regBit;
  };

  uint8_t CTK;

  struct {
    int16_t motor1_ctrl;
    int16_t motor2_ctrl;
    int16_t motor3_ctrl;
    int16_t motor4_ctrl;
  } motorControl;

  uint8_t cmdDataPC;

  // Receive from MCU
  uint8_t ajbHeader[2];
  uint8_t cmdDataMCU;

  struct {
    int16_t motor1_fb;
    int16_t motor2_fb;
    int16_t motor3_fb;
    int16_t motor4_fb;
  } motorFeedBack;

  struct {
    int8_t mouse_x_vel;
    int8_t mouse_y_vel;
  } mouseVel;

  int16_t gyro_x_raw;
  int16_t gyro_y_raw;
  int16_t gyro_z_raw;

  int16_t mag_x_raw;
  int16_t mag_y_raw;
  int16_t mag_z_raw;

  int16_t acc_x_raw;
  int16_t acc_y_raw;
  int16_t acc_z_raw;

  uint8_t cks;
} ros_rbc_ioPacket_t;


extern ros_rbc_ioPacket_t  rbc_Packet_t;

// state machine enum
enum ROS_COMM_FSM{
  COMMSTATE_WAITFORREPLY    = 0, // Wait for Header match, then process the message
  COMMSTATE_REPLYDATA       = 1, // Transmit the feedback message
};

typedef struct{
	float v1;
	float v2;
	float v3;
	float v4;
}v_motor;

extern v_motor motor_cmdvel_ptr_t;

void app_ros_comm_runner();
void app_ros_comm_processRX();
void app_ros_comm_comandProcessor();
void app_ros_comm_txPoll();

#endif /* APP_ROS_COMM_H_ */
