#ifndef __adc_H
#define __adc_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

//======================================================================================
// Вход АЦП напряжения питания мотора (среднего)
#define ADC_V_MOTOR_Pin 			GPIO_PIN_0
#define ADC_V_MOTOR_GPIO_Port 		GPIOA
#define CHANNEL_ADC_V_MOTOR			ADC_CHANNEL_0

// Вход АЦП напряжения питания (входного)
#define ADC_V_IN_12V_Pin 			GPIO_PIN_1
#define ADC_V_IN_12V_GPIO_Port 		GPIOA
#define CHANNEL_ADC_V_IN_12V		ADC_CHANNEL_1

// Вход АЦП напряжения регулятора скорости мотора
#define ADC_SPEED_Pin 				GPIO_PIN_5
#define ADC_SPEED_GPIO_Port 		GPIOC
#define CHANNEL_ADC_SPEED			ADC_CHANNEL_15

// Вход АЦП для измерения общего тока потребеления
#define ADC_I_IN_12V_Pin 			GPIO_PIN_8
#define ADC_I_IN_12V_GPIO_Port 		GPIOE
#define CHANNEL_ADC_I_IN_12V		ADC_CHANNEL_23

// Вход АЦП для измерения тока потребеления и перегрузки мотора
#define ADC_I_MOTOR_Pin 			GPIO_PIN_9
#define ADC_I_MOTOR_GPIO_Port 		GPIOE
#define CHANNEL_ADC_I_MOTOR			ADC_CHANNEL_24

//======================================================================================
#define ADC_DIVIDER_RATIO		(double)(3.439) // (200K+82K)/82K						// Коэффициент делителя на резисторах от АКБ до входа АЦП (опорное от источника 1.8V)
#define BATTERY_LOW_THRESHOLD	(double)(2.55)											// пороговое напряжение отключения при низком заряде батареи
//=======================================================================================
typedef struct
{
	uint8_t 	DataReady;																// структура заполнена

	uint32_t	ADC_RAW;																// сырые данные с АЦП
	double		battery_raw_volts;														// напряженеие на АЦП в чистом виде в вольтах
	double		battery_cell_volts;														// напряженеие на 1 ячейке батареи (4 ячейки сейчас, соотв общее / 4)

	uint8_t		battery_level;															// уровень батареи для графического отображения

	double		ADC_Ref_Voltage;														// калибровка батереи: опорное напряжение АЦП

	uint8_t		CHG_ON_BATT;															// От какого источника питаемся 0 = от внешнего входа (USB кабель), 1 = от внутренней АКБ
	uint8_t		CHG_CHARGE;																// Процесс заряда (0=зарядка АКБ не идет, 1=зарядка АКБ идет)
	uint8_t		CHG_DONE;																// Статус окончания заряда (0=заряд АКБ не окончен, 1=заряд АКБ окончен)

	uint8_t		LOW_BATT;																// Статус зизкого заряда АКБ перед выключением (1=напряжение ниже порога работы, 0=норма)

	uint8_t		LRF_DENY;																// Статус запрета на использование дальномера во время заряда (1=запрещено, 0=разрешено)

}  ADC_State_TypeDef;
//=======================================================================================
typedef struct
{
	uint8_t 	DataReady;																// структура заполнена

	uint16_t	ADC_RAW;																// сырые данные с АЦП
	double		InternalTemperature_raw;												// напряженеие на АЦП в чистом виде
	 int32_t    Temperature_DegreeCelsius;												// Температура в градусах цельсия

}  ADC_Temperature_State_TypeDef;
//=======================================================================================

ADC_State_TypeDef 						ADC_State;										// структура с сотоянием батареи
ADC_Temperature_State_TypeDef			ADC_Temperature_State;							// структура с сотоянием внутреннего термодатчика процессора

//=======================================================================================



#define ADC_REF_VOLTAGE_DEFAULT (double)(3.30)											// калибровка батереи: опорное напряжение АЦП
#define ADC_12V_VOLTAGE_DEFAULT (double)(12.27)											// калибровка батереи: опорное напряжение для пересчета батареи

//=======================================================================================
typedef struct
{
	uint8_t 	DataReady;																// структура заполнена

	uint32_t	ADC_RAW;																// сырые данные с АЦП
	double		battery_raw_volts;														// напряженеие на АЦП в чистом виде в вольтах
	double		battery_cell_volts;														// напряженеие на 1 ячейке батареи (4 ячейки сейчас, соотв общее / 4)

	uint8_t		battery_level;															// уровень батареи для графического отображения

	double		ADC_Ref_Voltage;														// калибровка батереи: опорное напряжение АЦП
	double		ADC_12V_Voltage;														// калибровка батереи: опорное напряжение для пересчета батареи

}  MP_Battery_State_TypeDef;
//=======================================================================================

MP_Battery_State_TypeDef 				Battery_State;									// структура с сотоянием батареи








extern ADC_HandleTypeDef hadc;

//======================================================================================
void MX_ADC_Init(void);
void ADC_ScanState(void);																// Замер из АЦП по всем каналам сразу


#ifdef __cplusplus
}
#endif

 #endif /*__ adc_H */
