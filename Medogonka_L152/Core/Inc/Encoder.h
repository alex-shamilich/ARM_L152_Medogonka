// Работа с механическим инкрементальным энкодером
//
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

#define ENC_BTN_PRESSED		!HAL_GPIO_ReadPin(ENC_BTN_GPIO_Port,  ENC_BTN_Pin);			// Проверка нажатости кнопки энкодера


#define ENCODER_VAL_DEFAULT			0													// Значение счетчика энкодера по-умолчанию
#define ENCODER_VAL_PERIOD			20													// Период счета энкодера от 0 до ...

//=======================================================================================
typedef struct																			// Структура сосотяния энкодера
{
	uint32_t 	MP_Encoder_Value;														// Значение счетчика энкодра
	uint32_t 	MP_Encoder_Value_old;													// Значение счетчика энкодра старое
//	uint32_t 	MP_Encoder_Value_prev;													// Значение счетчика энкодра на предыдущем шаге
	uint32_t 	MP_Encoder_Dir;															// Направление
	int32_t 	MP_Encoder_Delta;														// Изменение счетчика между 2 измерениями, если крутим быстрее периода опроса
	uint8_t  	fEncoder3Changes;														// Если произошло изменение счетчика энкодера

	GPIO_PinState Btn_pressed;															// Нажата ли кнопка на энкодере

}  Encoder_State_TypeDef;
Encoder_State_TypeDef 				Encoder_State;										// структура с сотоянием энкодера
//=======================================================================================

 // Прототипы функций
void  Encoder_Init(void);																// Настройка GPIO портов для энкодера

void Encoder_Start(void);																// Начальная установка для энкодера
void Encoder_Stop(void);																// Остановка энкодера (на время отсутствия питания)
uint8_t Encoder_Scan(void);																// Сканировать состояние энкодера

#endif /* INC_ENCODER_H_ */
