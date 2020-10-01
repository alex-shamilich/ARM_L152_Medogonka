/*
 * motor.c
 *
 *  Created on: Oct 1, 2020
 *      Author: EN-E-01
 */

#include "motor.h"
#include "cmsis_os.h"


// Выход выбора направления движения мотора ВПЕРЕД
#define MOTOR_FWD_Pin 				GPIO_PIN_6
#define MOTOR_FWD_GPIO_Port 		GPIOE
#define MOTOR_FWD_SET 				HAL_GPIO_WritePin(MOTOR_FWD_GPIO_Port,  MOTOR_FWD_Pin, GPIO_PIN_SET)
#define MOTOR_FWD_RESET 			HAL_GPIO_WritePin(MOTOR_FWD_GPIO_Port,  MOTOR_FWD_Pin, GPIO_PIN_RESET)
#define MOTOR_FWD_INV 				HAL_GPIO_TogglePin(MOTOR_FWD_GPIO_Port, MOTOR_FWD_Pin)

// Выход выбора направления движения мотора НАЗАД
#define MOTOR_BWD_Pin 				GPIO_PIN_7
#define MOTOR_BWD_GPIO_Port 		GPIOE
#define MOTOR_BWD_SET 				HAL_GPIO_WritePin(MOTOR_BWD_GPIO_Port,  MOTOR_BWD_Pin, GPIO_PIN_SET)
#define MOTOR_BWD_RESET 			HAL_GPIO_WritePin(MOTOR_BWD_GPIO_Port,  MOTOR_BWD_Pin, GPIO_PIN_RESET)
#define MOTOR_BWD_INV 				HAL_GPIO_TogglePin(MOTOR_BWD_GPIO_Port, MOTOR_BWD_Pin)


//=======================================================================================
void  Motor_Set_Dir_Forward(void)														// Установить направление мотора - ВПЕРЕД
{
	// Сначала сбросить оба направления
	MOTOR_FWD_RESET;
	MOTOR_BWD_RESET;

	osDelay(100);
	MOTOR_FWD_SET;
}
//=======================================================================================
void  Motor_Set_Dir_Backward(void)														// Установить направление мотора - НАЗАД
{
	// Сначала сбросить оба направления
	MOTOR_FWD_RESET;
	MOTOR_BWD_RESET;

	osDelay(100);
	MOTOR_BWD_SET;
}
//=======================================================================================


