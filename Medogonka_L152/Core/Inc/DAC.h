#ifndef __dac_H
#define __dac_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

// Выход ЦАП на управление скоростью мотора
#define DAC1__MOTOR_SPEED_Pin 			GPIO_PIN_4
#define DAC1__MOTOR_SPEED_GPIO_Port 	GPIOA


extern DAC_HandleTypeDef hdac;

void MX_DAC_Init(void);


#ifdef __cplusplus
}
#endif
#endif /*__ dac_H */
