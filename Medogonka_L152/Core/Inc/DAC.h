#ifndef __dac_H
#define __dac_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

// Выход ЦАП на управление скоростью мотора
#define DAC1__MOTOR_SPEED_Pin 			GPIO_PIN_4
#define DAC1__MOTOR_SPEED_GPIO_Port 	GPIOA

#define DACx_CHANNEL                    DAC_CHANNEL_1

extern DAC_HandleTypeDef DacHandle;

void MX_DAC_Init(void);
void DAC_SetValue(uint8_t AValue);														// Установка значения в ЦАП

#ifdef __cplusplus
}
#endif
#endif /*__ dac_H */
