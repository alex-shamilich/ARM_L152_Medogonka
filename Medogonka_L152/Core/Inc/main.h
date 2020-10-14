//======================================================================================
// File Name          : main.h
// Description        : Main program header
//======================================================================================
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal.h"
#include "stdio.h"

#include "State.h"

#include "adc.h"
#include "dac.h"
#include "gpio.h"
#include "keys.h"
#include "Encoder.h"
#include "Buzzer_TIM.h"
#include "Motor.h"
#include "Display.h"
#include "DS18B20.h"


// LCD LIL9488:
#include "LCD_ili9488.h"
#include "LCD_ili9488_test.h"
//======================================================================================

void Delay_for_errror(uint32_t ms); 													// должна работать вне зависимости от прерываний. Когда все рухнуло и нужно диодом показать код ошибки
void Error_Handler(uint8_t err_num);													// Обработчик ошибок

//======================================================================================

uint16_t MotorSpeed_Period;																// Период импульсов от датчика скорости мотора
uint16_t MotorSpeed;																	// Скорость мотора от датчика скорости мотора

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
//======================================================================================
