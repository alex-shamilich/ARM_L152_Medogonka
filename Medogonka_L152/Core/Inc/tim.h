#ifndef __tim_H
#define __tim_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim11;

void MX_TIM3_Init(void);
void MX_TIM4_Init(void);
void MX_TIM11_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

#ifdef __cplusplus
}
#endif
#endif /*__ tim_H */
