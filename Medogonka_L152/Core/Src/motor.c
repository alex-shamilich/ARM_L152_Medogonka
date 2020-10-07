/*
 * motor.c
 *
 *  Created on: Oct 1, 2020
 *      Author: EN-E-01
 */

#include "GPIO.h"
#include "Motor.h"
#include "cmsis_os.h"


//// Выход выбора направления движения мотора ВПЕРЕД
//#define MOTOR_FWD_Pin 				GPIO_PIN_6
//#define MOTOR_FWD_GPIO_Port 		GPIOE
//#define MOTOR_FWD_SET 				HAL_GPIO_WritePin(MOTOR_FWD_GPIO_Port,  MOTOR_FWD_Pin, GPIO_PIN_SET)
//#define MOTOR_FWD_RESET 			HAL_GPIO_WritePin(MOTOR_FWD_GPIO_Port,  MOTOR_FWD_Pin, GPIO_PIN_RESET)
//#define MOTOR_FWD_INV 				HAL_GPIO_TogglePin(MOTOR_FWD_GPIO_Port, MOTOR_FWD_Pin)
//
//// Выход выбора направления движения мотора НАЗАД
//#define MOTOR_BWD_Pin 				GPIO_PIN_7
//#define MOTOR_BWD_GPIO_Port 		GPIOE
//#define MOTOR_BWD_SET 				HAL_GPIO_WritePin(MOTOR_BWD_GPIO_Port,  MOTOR_BWD_Pin, GPIO_PIN_SET)
//#define MOTOR_BWD_RESET 			HAL_GPIO_WritePin(MOTOR_BWD_GPIO_Port,  MOTOR_BWD_Pin, GPIO_PIN_RESET)
//#define MOTOR_BWD_INV 				HAL_GPIO_TogglePin(MOTOR_BWD_GPIO_Port, MOTOR_BWD_Pin)


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
void  Motor_Scan_DirectionState(void)													// Просканировать состояние переключателя направления мотора
{
	GPIO_PinState FWD = HAL_GPIO_ReadPin(BTN_FWD_GPIO_Port,  BTN_FWD_Pin);
	GPIO_PinState BWD = HAL_GPIO_ReadPin(BTN_BWD_GPIO_Port,  BTN_BWD_Pin);

	if ( (FWD == GPIO_PIN_SET) &
		 (BWD == GPIO_PIN_SET) )
	{
		MotorDirection = MD_STOP;
	}
	if ( (FWD == GPIO_PIN_SET) &
		 (BWD == GPIO_PIN_RESET) )
	{
		MotorDirection = MD_FWD;
	}
	if ( (FWD == GPIO_PIN_RESET) &
		 (BWD == GPIO_PIN_SET) )
	{
		MotorDirection = MD_REV;
	}

}
//=======================================================================================
void  Motor_Set_DirectionState(TMotorDirection ADir)									// Установить направление мотора
{
	switch (ADir)
	{
		case MD_STOP:
			MOTOR_FWD_RESET;
			MOTOR_BWD_RESET;
			break;
		case MD_FWD:
			MOTOR_FWD_SET;
			MOTOR_BWD_RESET;
			break;
		case MD_REV:
			MOTOR_FWD_RESET;
			MOTOR_BWD_SET;
			break;
	}

}
//=======================================================================================
void  FAN_Init(void)																	// Инициализация управления мотором вентилятора охлажения
{
	MX_TIM11_Init();																	// Инициализация таймера для ШИМ

	FAN_Set_Start();																	// Включить мотор вентилятора охлажения
	FAN_Set_Speed(FAN_SPEED_DEFAULT);													// Установить скорость вентилятора по-умолчанию
}
//=======================================================================================
void  FAN_Set_Start(void)																// Включить мотор вентилятора охлажения
{
	HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1);
}
//=======================================================================================
void  FAN_Set_Stop(void)																// Выключить мотор вентилятора охлажения
{
	HAL_TIM_PWM_Stop(&htim11, TIM_CHANNEL_1);
}
//=======================================================================================
void  FAN_Set_Speed(uint8_t APercent)													// Установить скорость мотора вентилятора охлажения
{
	TIM11->CCR1 = APercent;																// Т.к. период ШИМ таймера задан в (htim11.Init.Period = 100;),
																						// скважность тут задаем от 0 до 100.
																						// Частота ШИМ определяется соотношением (htim11.Init.Prescaler = 32000;) с тактовой частотой
}
//=======================================================================================






