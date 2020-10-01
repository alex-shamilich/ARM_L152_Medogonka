#ifndef _buzzer_h_
#define _buzzer_h_

#include "gpio.h"
#include "Tim.h"

// Динамик на порт
#define BUZZER_TIMER 	TIM6															// таймер для работы (BasicTimer)

// Выход на динамик
#define BUZZER_Pin 						GPIO_PIN_5
#define BUZZER_GPIO_Port 				GPIOB
#define BUZZER_SET 						HAL_GPIO_WritePin(BUZZER_GPIO_Port,  BUZZER_Pin, GPIO_PIN_SET)
#define BUZZER_RESET 					HAL_GPIO_WritePin(BUZZER_GPIO_Port,  BUZZER_Pin, GPIO_PIN_RESET)
#define BUZZER_INV 						HAL_GPIO_TogglePin(BUZZER_GPIO_Port, BUZZER_Pin)
#define BUZZER_ON 						BUZZER_SET
#define BUZZER_OFF 						BUZZER_RESET


#define BUZZER_STSTE_OFF 				0												// баззер выключен
#define BUZZER_STSTE_ON 				1												// баззер включен

#define BUZZER_HALF_PERIOD 				1												// 	Полупериод для колебания в милисекундах
#define BUZZER_HALF_FREQ_TIM			(uint32_t)4000									// 	Частота для колебания в [Гц] при работе через таймер
#define BUZZER_HALF_FREQ_KHZ_TIM		(uint32_t)(BUZZER_HALF_FREQ_TIM/1000)			// 	Частота для колебания в [кГц] при работе через таймер
#define BUZZER_HALF_PERIOD_TIM			(uint32_t)( 500/BUZZER_HALF_FREQ_KHZ_TIM - 4)	// 	Полупериод для колебания в милисекундах при работе через таймер
#define BUZZER_DELAY 		  			20												//	Задержка между бипами в сериях в [мс]
#define BUZZER_NUM_HALF_PERIOD_SHORT	40												// 	Число циклов для получения нужной длительности короткого бипа
#define BUZZER_NUM_HALF_PERIOD_NORM		70												// 	Число циклов для получения нужной длительности нормального бипа
#define BUZZER_NUM_HALF_PERIOD_LONG		150 											//	Число циклов для получения нужной длительности длинного бипа

// Прототипы функций
void BUZZER_Init(uint8_t state);														// Инициализация баззера

void BUZZER_Beep(void);																	// Один стандартный бип
void BUZZER_Beep_Tick(void);															// Один совсем короткий тик
void BUZZER_Beep_Short(void);															// Один короктий бип
void BUZZER_Beep_Dbl(void);																// Двойной бип
void BUZZER_Beep_Tri(void); 															// Тройной бип

// Процедуры через таймер для RTOS
void BUZZER_BeepTIM(void);																// Один стандартный бип
void BUZZER_Beep_TickTIM(void);															// Generates one very-very short beep
void BUZZER_Beep_ShortTIM(void);			 											// Generates one very short beep
void BUZZER_Beep_DblTIM(void); 															// Generates 2 short beeps
void BUZZER_Beep_TriTIM(void); 															// Generates 3 short beeps


#endif
