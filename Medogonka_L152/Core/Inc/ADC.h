#ifndef __adc_H
#define __adc_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "stm32l1xx_ll_adc.h"															// Для работы с внутренним термодатчиком и напряжением питания процессора
//======================================================================================
// Вход АЦП напряжения питания мотора (среднего)
#define ADC_V_MOTOR_Pin 			GPIO_PIN_0
#define ADC_V_MOTOR_GPIO_Port 		GPIOA
#define CHANNEL_ADC_V_MOTOR			ADC_CHANNEL_0										// Номер канала АЦП
#define DIVIDER_ADC_V_MOTOR			(double)(6.03)										// Делитель на входе АЦП чтобы вписаться в 0..3.3В

// Вход АЦП напряжения питания (входного)
#define ADC_V_IN_12V_Pin 			GPIO_PIN_1
#define ADC_V_IN_12V_GPIO_Port 		GPIOA
#define CHANNEL_ADC_V_IN_12V		ADC_CHANNEL_1										// Номер канала АЦП
#define DIVIDER_ADC_V_IN_12V		(double)(6.01)										// Делитель на входе АЦП чтобы вписаться в 0..3.3В

// Вход АЦП напряжения регулятора скорости мотора
#define ADC_SPEED_Pin 				GPIO_PIN_5
#define ADC_SPEED_GPIO_Port 		GPIOC
#define CHANNEL_ADC_SPEED			ADC_CHANNEL_15										// Номер канала АЦП
#define DIVIDER_ADC_SPEED			(double)(1.0)										// Делитель на входе АЦП чтобы вписаться в 0..3.3В

// Вход АЦП для измерения общего тока потребеления
#define ADC_I_IN_12V_Pin 			GPIO_PIN_8
#define ADC_I_IN_12V_GPIO_Port 		GPIOE
#define CHANNEL_ADC_I_IN_12V		ADC_CHANNEL_23										// Номер канала АЦП
#define DIVIDER_ADC_I_IN_12V		(double)(4.2)										// Делитель на входе АЦП чтобы вписаться в 0..3.3В

// Вход АЦП для измерения тока потребеления и перегрузки мотора
#define ADC_I_MOTOR_Pin 			GPIO_PIN_9
#define ADC_I_MOTOR_GPIO_Port 		GPIOE
#define CHANNEL_ADC_I_MOTOR			ADC_CHANNEL_24										// Номер канала АЦП
#define DIVIDER_ADC_I_MOTOR			(double)(3.2)										// Делитель на входе АЦП чтобы вписаться в 0..3.3В


//======================================================================================
#define ADC_REF_VOLTAGE_DEFAULT (double)(3.30)											// опорное напряжение АЦП (по умолчанию, если не измерять его)
//=======================================================================================
typedef struct
{
	uint8_t 	DataReady;																// структура заполнена

	uint32_t	ADC_RAW;																// сырые данные с АЦП

	double		ADC_Ref_Voltage;														// калибровка АЦП: реальное папряжение питания
	double		CPU_Temperature;														// Температура процессора (в кристалле) в градусах Цельсия
//	double		CPU_TemperatureRef;														// Температура процессора (в кристалле) в градусах Цельсия измеренная с учетом напряжения питания
	uint32_t	CPU_Temperature_raw;													// Температура процессора (в кристалле) в вольтах (сырые данные)

	double 		Speed_value_volts;														// Напряжение от регулятора скорости мотора в вольтах (с переменного резистора)
	uint8_t		Speed_value_percent;													// Напряжение от регулятора скорости мотора в процентаз 0..100 (с переменного резистора)

	double 		V_IN_12V_value_volts;													// Напряжение входного питания 12В в вольтах
	double 		V_IN_MOTOR_value_volts;													// Напряжение мотора в вольтах (среднее)
	double 		I_IN_12V_value_amperes;													// Ток общий по входу питания в Амперах
	double 		I_IN_MOTOR_value_amperes;												// Ток мотора в Амперах

}  ADC_State_TypeDef;
//=======================================================================================

ADC_State_TypeDef 						ADC_State;										// структура с сотоянием батареи

//=======================================================================================

extern ADC_HandleTypeDef hadc;

//======================================================================================
void MX_ADC_Init(void);
void ADC_ScanState(void);																// Замер из АЦП по всем каналам сразу
uint32_t ADC_GetRAWData(uint32_t Channel);												// Получить сырые данные для обрботки по указанному каналу


#ifdef __cplusplus
}
#endif

 #endif /*__ adc_H */
