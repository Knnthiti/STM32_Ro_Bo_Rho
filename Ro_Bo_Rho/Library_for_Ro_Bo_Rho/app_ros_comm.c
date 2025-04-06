/*
 * app_ros_comm.c
 *
 *  Created on: Feb 17, 2025
 *      Author: Knnn
 */
#include "app_ros_comm.h"

v_motor motor_cmdvel_ptr_t;
ros_rbc_ioPacket_t  rbc_Packet_t;

unsigned long commTimeout_millis = 0;

// Private variable
uint8_t comm_fsm        = 0;
uint8_t rx_timeOutFlag = 0;


void app_ros_comm_runner(){

  if((uwTick - commTimeout_millis) > COMM_TIMEOUT_MS){
    commTimeout_millis = uwTick;
    comm_fsm = COMMSTATE_WAITFORREPLY;
    rx_timeOutFlag = 1;

    motor_cmdvel_ptr_t.v1 = 0.0f;
    motor_cmdvel_ptr_t.v2 = 0.0f;
    motor_cmdvel_ptr_t.v3 = 0.0f;
    motor_cmdvel_ptr_t.v4 = 0.0f;
  }

  switch(comm_fsm){
    case COMMSTATE_WAITFORREPLY:
    {
      commTimeout_millis = uwTick;
      rx_timeOutFlag = 0;

      // Process RX data here
      app_ros_comm_processRX();
    }
    break;

    case COMMSTATE_REPLYDATA:
    {
    	app_ros_comm_txPoll();
        comm_fsm = COMMSTATE_WAITFORREPLY;
    }
    break;
  }

}

void app_ros_comm_processRX(){
  if(
  (rbc_Packet_t.rbcHeader[0] != 'R')  ||
  (rbc_Packet_t.rbcHeader[1] != 'B')
  )
    return;

  // Apply header
  rbc_Packet_t.ajbHeader[0] = 'J';
  rbc_Packet_t.ajbHeader[1] = 'B';

  // Apply motor RPM command
  motor_cmdvel_ptr_t.v1  =
    (float)rbc_Packet_t.motorControl.motor1_ctrl;// LF
  motor_cmdvel_ptr_t.v2  =
    (float)rbc_Packet_t.motorControl.motor2_ctrl;// LB
  motor_cmdvel_ptr_t.v3  =
    (float)rbc_Packet_t.motorControl.motor3_ctrl;// RB
  motor_cmdvel_ptr_t.v4  =
    (float)rbc_Packet_t.motorControl.motor4_ctrl;// RF

  // Reply command
  rbc_Packet_t.cmdDataMCU = 0x00;

  // Process PC command
  app_ros_comm_comandProcessor();

  comm_fsm = COMMSTATE_REPLYDATA;
}

void app_ros_comm_comandProcessor(){
//  switch(rbc_Packet_t.reg & 0x7F){
//    case 0x00:// Null command
//      {
//        // Reply command
//        rbc_Packet_t.cmdDataMCU = 0x00;
//      }
//      break;
//
//    case 0xAA:// Emergency stop
//      {
//        // Reply command
//        rbc_Packet_t.cmdDataMCU = 0x55;
//        motor_cmdvel_ptr_t->v1  = 0.0f;
//        motor_cmdvel_ptr_t->v2  = 0.0f;
//        motor_cmdvel_ptr_t->v3  = 0.0f;
//        motor_cmdvel_ptr_t->v4  = 0.0f;
//      }
//      break;
//
//    default:
//        // Reply command
//        rbc_Packet_t.cmdDataMCU = 0x00;
//      break;
//  }
//
}

void app_ros_comm_txPoll(){
	// Send encoder RPM count
	  rbc_Packet_t.motorFeedBack.motor1_fb  = _RPM[0];                       // LF
	  rbc_Packet_t.motorFeedBack.motor2_fb  = _RPM[1];                       // LB
	  rbc_Packet_t.motorFeedBack.motor3_fb  = _RPM[2];                       // RB
	  rbc_Packet_t.motorFeedBack.motor4_fb  = _RPM[3];                       // RF

	// Send gyro data
	  rbc_Packet_t.gyro_x_raw = imu_data.gx;
	  rbc_Packet_t.gyro_y_raw = imu_data.gy;
	  rbc_Packet_t.gyro_z_raw = imu_data.gz;

		// Send mag data
//	  rbc_Packet_t.mag_x_raw = imu_acmag_data_ptr_t->mag_x;
//	  rbc_Packet_t.mag_y_raw = imu_acmag_data_ptr_t->mag_y;
//	  rbc_Packet_t.mag_z_raw = imu_acmag_data_ptr_t->mag_z;

	  rbc_Packet_t.mag_x_raw = 0;
	  rbc_Packet_t.mag_y_raw = 0;
	  rbc_Packet_t.mag_z_raw = 0;

		// Send accel data
	  rbc_Packet_t.acc_x_raw = imu_data.Ax;
	  rbc_Packet_t.acc_y_raw = imu_data.Ay;
	  rbc_Packet_t.acc_z_raw = imu_data.Az;


	  CDC_Transmit_FS((uint8_t *)(&rbc_Packet_t.ajbHeader), ROS_COMM_TX_SIZE);

}

