/*
 * encoder.h
 *
 *  Created on: Oct 1, 2020
 *      Author: EN-E-01
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "main.h"


// GPIO для энкодера
#define ENC_A_Pin 			GPIO_PIN_3
#define ENC_A_GPIO_Port 	GPIOE

#define ENC_B_Pin 			GPIO_PIN_4
#define ENC_B_GPIO_Port 	GPIOE

#define ENC_BTN_Pin 		GPIO_PIN_13
#define ENC_BTN_GPIO_Port 	GPIOD

void  Encoder_Init(void);																	// Настройка GPIO портов для энкодера


#endif /* INC_УNCODER_H_ */
