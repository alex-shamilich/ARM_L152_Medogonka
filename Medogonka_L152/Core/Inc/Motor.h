/*
 * motor.h
 *
 *  Created on: Oct 1, 2020
 *      Author: EN-E-01
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

//#include "main.h"

#define FAN_SPEED_DEFAULT 	100															// Начальная скорость вентилятора охлаждения при включении (0..100)


uint8_t		Speed_value_percent;														// Напряжение от регулятора скорости мотора в процентаз 0..100 (с переменного резистора)

typedef enum TMotorDirection {															// Направление движения мотора
    MD_STOP,																			// Остановлен
	MD_FWD,																				// Вперед
	MD_REV																				// Назад
} TMotorDirection;

TMotorDirection MotorDirection;															// Направление движения мотра


void  Motor_Set_Dir_Forward(void);														// Установить направление мотора - ВПЕРЕД
void  Motor_Set_Dir_Backward(void);														// Установить направление мотора - НАЗАД

void  Motor_Set_DirectionState(TMotorDirection ADir);									// Установить направление мотора
void  Motor_Scan_DirectionState(void);													// Просканировать состояние переключателя направления мотора

void  FAN_Init(void);																	// Инициализация управления мотором вентилятора охлажения
void  FAN_Set_Start(void);																// Включить мотор вентилятора охлажения
void  FAN_Set_Stop(void);																// Выключить мотор вентилятора охлажения
void  FAN_Set_Speed(uint8_t APercent);													// Установить скорость мотора вентилятора охлажения


#endif /* INC_MOTOR_H_ */
