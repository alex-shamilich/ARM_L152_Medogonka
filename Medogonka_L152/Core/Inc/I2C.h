#ifndef __i2c_H
#define __i2c_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

// GPIO для I2C
#define I2C1_SCL_Pin 		GPIO_PIN_8
#define I2C1_SCL_GPIO_Port 	GPIOB

#define I2C1_SDA_Pin 		GPIO_PIN_9
#define I2C1_SDA_GPIO_Port 	GPIOB


extern I2C_HandleTypeDef hi2c1;

void MX_I2C1_Init(void);

#ifdef __cplusplus
}
#endif
#endif /*__ i2c_H */
