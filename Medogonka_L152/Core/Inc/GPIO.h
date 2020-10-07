#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

// Выход на зеленый отладочный светодиод
#define LED_GREEN_Pin 				GPIO_PIN_4
#define LED_GREEN_GPIO_Port 		GPIOC
#define LED_GREEN_SET 				HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,  LED_GREEN_Pin, GPIO_PIN_SET)
#define LED_GREEN_RESET 			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,  LED_GREEN_Pin, GPIO_PIN_RESET)
#define LED_GREEN_INV 				HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin)

// Выход управления светодиодной подсветкой бака
#define LED_LIGHT_Pin 				GPIO_PIN_5
#define LED_LIGHT_GPIO_Port 		GPIOE
#define LED_LIGHT_SET 				HAL_GPIO_WritePin(LED_LIGHT_GPIO_Port,  LED_LIGHT_Pin, GPIO_PIN_SET)
#define LED_LIGHT_RESET 			HAL_GPIO_WritePin(LED_LIGHT_GPIO_Port,  LED_LIGHT_Pin, GPIO_PIN_RESET)
#define LED_LIGHT_INV 				HAL_GPIO_TogglePin(LED_LIGHT_GPIO_Port, LED_LIGHT_Pin)

// Выход на ШИМ управление двигателя охлаждения контроллера мотора
 #define PWM_COOLING_Pin 			GPIO_PIN_1
 #define PWM_COOLING_GPIO_Port 		GPIOE

// Выход выбора направления движения мотора ВПЕРЕД
#define MOTOR_FWD_Pin 				GPIO_PIN_6
#define MOTOR_FWD_GPIO_Port 		GPIOE
#define MOTOR_FWD_SET 				HAL_GPIO_WritePin(MOTOR_FWD_GPIO_Port,  MOTOR_FWD_Pin, GPIO_PIN_SET)
#define MOTOR_FWD_RESET 			HAL_GPIO_WritePin(MOTOR_FWD_GPIO_Port,  MOTOR_FWD_Pin, GPIO_PIN_RESET)
#define MOTOR_FWD_INV 				HAL_GPIO_TogglePin(MOTOR_FWD_GPIO_Port, MOTOR_FWD_Pin)

// Выход выбора направления движения мотора НАЗАД
#define MOTOR_BWD_Pin 				GPIO_PIN_7
#define MOTOR_BWD_GPIO_Port 		GPIOE
#define MOTOR_BWD_SET 				HAL_GPIO_WritePin(MOTOR_BWD_GPIO_Port,  MOTOR_BWD_Pin, GPIO_PIN_SET)
#define MOTOR_BWD_RESET 			HAL_GPIO_WritePin(MOTOR_BWD_GPIO_Port,  MOTOR_BWD_Pin, GPIO_PIN_RESET)
#define MOTOR_BWD_INV 				HAL_GPIO_TogglePin(MOTOR_BWD_GPIO_Port, MOTOR_BWD_Pin)

// Вход прерывания от IMU
#define INT_IMU_Pin 				GPIO_PIN_0
#define INT_IMU_GPIO_Port 			GPIOD

// Вход от датчика оборотова бака
#define SNS_HALL_IN_Pin 			GPIO_PIN_6
#define SNS_HALL_IN_GPIO_Port 		GPIOB

// Вход-выход термодатчика 1-wire. Температура воздуха
#define TEMP_AIR_1W_Pin 			GPIO_PIN_0
#define TEMP_AIR_1W_GPIO_Port 		GPIOB

// Вход-выход термодатчика 1-wire. Температура мотора
#define TEMP_MOTOR_1W_Pin 			GPIO_PIN_1
#define TEMP_MOTOR_1W_GPIO_Port 	GPIOB

// Вход-выход термодатчика 1-wire. Температура драйвера мотора
#define TEMP_DRIVER_1W_Pin 			GPIO_PIN_2
#define TEMP_DRIVER_1W_GPIO_Port 	GPIOB



// USB порт
#define USB_DM_Pin 					GPIO_PIN_11
#define USB_DM_GPIO_Port 			GPIOA

#define USB_DP_Pin 					GPIO_PIN_12
#define USB_DP_GPIO_Port 			GPIOA

// DEBUGGER, прошивка
#define SYS_JTMS_SWDIO_Pin 			GPIO_PIN_13
#define SYS_JTMS_SWDIO_GPIO_Port 	GPIOA

#define SYS_JTCK_SWCLK_Pin 			GPIO_PIN_14
#define SYS_JTCK_SWCLK_GPIO_Port 	GPIOA

#define SYS_JTDO_TRACESWO_Pin 		GPIO_PIN_3
#define SYS_JTDO_TRACESWO_GPIO_Port GPIOB

// Вход от кварца тактового генератора
#define RCC_OSC_IN_Pin 				GPIO_PIN_0
#define RCC_OSC_IN_GPIO_Port 		GPIOH

#define RCC_OSC_OUT_Pin 			GPIO_PIN_1
#define RCC_OSC_OUT_GPIO_Port 		GPIOH

// Выход тактовой частоты MCO
#define MCO_Pin 					GPIO_PIN_8
#define MCO_GPIO_Port 				GPIOA





void MX_GPIO_Init(void);




#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */
