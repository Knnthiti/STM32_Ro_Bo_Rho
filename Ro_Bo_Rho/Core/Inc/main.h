/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct __attribute__((packed)){
  uint8_t Header[2];

  union {
    uint8_t moveBtnByte;
    struct {
      uint8_t move1 : 1;
      uint8_t move2 : 1;
      uint8_t move3 : 1;
      uint8_t move4 : 1;
      uint8_t res1 : 2;
      uint8_t set1 : 1;
      uint8_t set2 : 1;
    } moveBtnBit;
  };

  union {
    uint8_t attackBtnByte;
    struct {
      uint8_t attack1 : 1;
      uint8_t attack2 : 1;
      uint8_t attack3 : 1;
      uint8_t attack4 : 1;
      uint8_t res1 : 4;
    } attackBtnBit;
  };

  int8_t stickValue[4];  //joyL_X,joyL_Y ,joyR_X,joyR_Y

} ControllerData;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CE_1_Pin GPIO_PIN_2
#define CE_1_GPIO_Port GPIOE
#define CE_2_Pin GPIO_PIN_3
#define CE_2_GPIO_Port GPIOE
#define EXTRA1_PWM_L_Pin GPIO_PIN_5
#define EXTRA1_PWM_L_GPIO_Port GPIOE
#define SERVO_1_Pin GPIO_PIN_6
#define SERVO_1_GPIO_Port GPIOE
#define EXTRA1_DIGI_R_Pin GPIO_PIN_13
#define EXTRA1_DIGI_R_GPIO_Port GPIOC
#define SERVO_2_Pin GPIO_PIN_6
#define SERVO_2_GPIO_Port GPIOA
#define LF_PWM_L_Pin GPIO_PIN_7
#define LF_PWM_L_GPIO_Port GPIOA
#define LF_DIGI_R_Pin GPIO_PIN_5
#define LF_DIGI_R_GPIO_Port GPIOC
#define LB_DIGI_R_Pin GPIO_PIN_12
#define LB_DIGI_R_GPIO_Port GPIOE
#define LB_PWM_L_Pin GPIO_PIN_14
#define LB_PWM_L_GPIO_Port GPIOB
#define RB_PWM_L_Pin GPIO_PIN_15
#define RB_PWM_L_GPIO_Port GPIOB
#define RB_DIGI_R_Pin GPIO_PIN_9
#define RB_DIGI_R_GPIO_Port GPIOD
#define EN_X_A_Pin GPIO_PIN_15
#define EN_X_A_GPIO_Port GPIOA
#define EN_X_B_Pin GPIO_PIN_3
#define EN_X_B_GPIO_Port GPIOB
#define EN_Y_A_Pin GPIO_PIN_4
#define EN_Y_A_GPIO_Port GPIOB
#define EN_Y_B_Pin GPIO_PIN_5
#define EN_Y_B_GPIO_Port GPIOB
#define EXTRA2_PWM_L_Pin GPIO_PIN_8
#define EXTRA2_PWM_L_GPIO_Port GPIOB
#define RF_PWM_L_Pin GPIO_PIN_9
#define RF_PWM_L_GPIO_Port GPIOB
#define EXTRA2_DIGI_R_Pin GPIO_PIN_0
#define EXTRA2_DIGI_R_GPIO_Port GPIOE
#define RF_DIGI_R_Pin GPIO_PIN_1
#define RF_DIGI_R_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
