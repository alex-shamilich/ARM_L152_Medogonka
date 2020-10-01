/*
 * keys.h
 *
 *  Created on: Oct 1, 2020
 *      Author: EN-E-01
 */

#ifndef INC_KEYS_H_
#define INC_KEYS_H_

#include "main.h"

// Кнопка СТАРТ
#define BTN_START_Pin			GPIO_PIN_8
#define BTN_START_GPIO_Port 	GPIOD

// Кнопка СТОП
#define BTN_STOP_Pin 			GPIO_PIN_9
#define BTN_STOP_GPIO_Port 		GPIOD

// Вход переключателя МОТОР ВПЕРЕД
#define BTN_FWD_Pin 			GPIO_PIN_10
#define BTN_FWD_GPIO_Port 		GPIOD

// Вход переключателя МОТОР НАЗАД
#define BTN_BWD_Pin 			GPIO_PIN_11
#define BTN_BWD_GPIO_Port 		GPIOD

// Кнопка МОТОР
#define BTN_MOTOR_Pin 			GPIO_PIN_12
#define BTN_MOTOR_GPIO_Port 	GPIOD


void  Keys_Init(void);																	// Настройка GPIO портов для кнопок

#endif /* INC_KEYS_H_ */
