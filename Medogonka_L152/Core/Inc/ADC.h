#ifndef __adc_H
#define __adc_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

// Вход АЦП напряжения питания мотора (среднего)
#define ADC_V_MOTOR_Pin 			GPIO_PIN_0
#define ADC_V_MOTOR_GPIO_Port 		GPIOA

// Вход АЦП напряжения питания (входного)
#define ADC_V_IN_12V_Pin 			GPIO_PIN_1
#define ADC_V_IN_12V_GPIO_Port 		GPIOA

// Вход АЦП напряжения регулятора скорости мотора
#define ADC_SPEED_Pin 				GPIO_PIN_5
#define ADC_SPEED_GPIO_Port 		GPIOC

// Вход АЦП для измерения общего тока потребеления
#define ADC_I_IN_12V_Pin 			GPIO_PIN_8
#define ADC_I_IN_12V_GPIO_Port 		GPIOE

// Вход АЦП для измерения тока потребеления и перегрузки мотора
#define ADC_I_MOTOR_Pin 			GPIO_PIN_9
#define ADC_I_MOTOR_GPIO_Port 		GPIOE



extern ADC_HandleTypeDef hadc;

void MX_ADC_Init(void);

#ifdef __cplusplus
}
#endif

 #endif /*__ adc_H */
