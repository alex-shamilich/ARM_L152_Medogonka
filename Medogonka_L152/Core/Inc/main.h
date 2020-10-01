//======================================================================================
// File Name          : main.h
// Description        : Main program header
//======================================================================================
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal.h"

// LCD LIL9488:
#include "LCD_ili9488.h"
#include "LCD_ili9488_test.h"
//======================================================================================

void Error_Handler(void);

//======================================================================================
#define ENC_A_Pin GPIO_PIN_3
#define ENC_A_GPIO_Port GPIOE
#define ENC_B_Pin GPIO_PIN_4
#define ENC_B_GPIO_Port GPIOE
#define LED_LIGHT_Pin GPIO_PIN_5
#define LED_LIGHT_GPIO_Port GPIOE
#define MOTOR_FWD_Pin GPIO_PIN_6
#define MOTOR_FWD_GPIO_Port GPIOE
#define RCC_OSC_IN_Pin GPIO_PIN_0
#define RCC_OSC_IN_GPIO_Port GPIOH
#define RCC_OSC_OUT_Pin GPIO_PIN_1
#define RCC_OSC_OUT_GPIO_Port GPIOH
#define SPI2_LCD_DC_Pin GPIO_PIN_0
#define SPI2_LCD_DC_GPIO_Port GPIOC
#define SPI2_LCD_RST_Pin GPIO_PIN_1
#define SPI2_LCD_RST_GPIO_Port GPIOC
#define SPI2_LCD_CS_Pin GPIO_PIN_2
#define SPI2_LCD_CS_GPIO_Port GPIOC
#define SPI2_LCD_LED_Pin GPIO_PIN_3
#define SPI2_LCD_LED_GPIO_Port GPIOC
#define ADC_V_MOTOR_Pin GPIO_PIN_0
#define ADC_V_MOTOR_GPIO_Port GPIOA
#define ADC_V_IN_12V_Pin GPIO_PIN_1
#define ADC_V_IN_12V_GPIO_Port GPIOA
#define USART2_TX_Pin GPIO_PIN_2
#define USART2_TX_GPIO_Port GPIOA
#define USART2_RX_Pin GPIO_PIN_3
#define USART2_RX_GPIO_Port GPIOA
#define DAC1__MOTOR_SPEED_Pin GPIO_PIN_4
#define DAC1__MOTOR_SPEED_GPIO_Port GPIOA
#define SPI1_SD_SCK_Pin GPIO_PIN_5
#define SPI1_SD_SCK_GPIO_Port GPIOA
#define SPI1_SD_MISO_Pin GPIO_PIN_6
#define SPI1_SD_MISO_GPIO_Port GPIOA
#define SPI1_SD_MOSI_Pin GPIO_PIN_7
#define SPI1_SD_MOSI_GPIO_Port GPIOA
#define LED_GREEN_Pin GPIO_PIN_4
#define LED_GREEN_GPIO_Port GPIOC
#define ADC_SPEED_Pin GPIO_PIN_5
#define ADC_SPEED_GPIO_Port GPIOC
#define TEMP_AIR_1W_Pin GPIO_PIN_0
#define TEMP_AIR_1W_GPIO_Port GPIOB
#define TEMP_MOTOR_1W_Pin GPIO_PIN_1
#define TEMP_MOTOR_1W_GPIO_Port GPIOB
#define TEMP_DRIVER_1W_Pin GPIO_PIN_2
#define TEMP_DRIVER_1W_GPIO_Port GPIOB
#define MOTOR_BWD_Pin GPIO_PIN_7
#define MOTOR_BWD_GPIO_Port GPIOE
#define ADC_I_IN_12V_Pin GPIO_PIN_8
#define ADC_I_IN_12V_GPIO_Port GPIOE
#define ADC_I_MOTOR_Pin GPIO_PIN_9
#define ADC_I_MOTOR_GPIO_Port GPIOE
#define USART3_TX_Pin GPIO_PIN_10
#define USART3_TX_GPIO_Port GPIOB
#define USART3_RX_Pin GPIO_PIN_11
#define USART3_RX_GPIO_Port GPIOB
#define SPI1_SD_CS_Pin GPIO_PIN_12
#define SPI1_SD_CS_GPIO_Port GPIOB
#define SPI2_SCK_Pin GPIO_PIN_13
#define SPI2_SCK_GPIO_Port GPIOB
#define SPI2_MISO_Pin GPIO_PIN_14
#define SPI2_MISO_GPIO_Port GPIOB
#define SPI2_MOSI_Pin GPIO_PIN_15
#define SPI2_MOSI_GPIO_Port GPIOB
#define BTN_START_Pin GPIO_PIN_8
#define BTN_START_GPIO_Port GPIOD
#define BTN_STOP_Pin GPIO_PIN_9
#define BTN_STOP_GPIO_Port GPIOD
#define BTN_FWD_Pin GPIO_PIN_10
#define BTN_FWD_GPIO_Port GPIOD
#define BTN_BWD_Pin GPIO_PIN_11
#define BTN_BWD_GPIO_Port GPIOD
#define BTN_MOTOR_Pin GPIO_PIN_12
#define BTN_MOTOR_GPIO_Port GPIOD
#define ENC_BTN_Pin GPIO_PIN_13
#define ENC_BTN_GPIO_Port GPIOD
#define MCO_Pin GPIO_PIN_8
#define MCO_GPIO_Port GPIOA
#define USART1_TX_Pin GPIO_PIN_9
#define USART1_TX_GPIO_Port GPIOA
#define USART1_RX_Pin GPIO_PIN_10
#define USART1_RX_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define SYS_JTMS_SWDIO_Pin GPIO_PIN_13
#define SYS_JTMS_SWDIO_GPIO_Port GPIOA
#define SYS_JTCK_SWCLK_Pin GPIO_PIN_14
#define SYS_JTCK_SWCLK_GPIO_Port GPIOA
#define UART4_TX_Pin GPIO_PIN_10
#define UART4_TX_GPIO_Port GPIOC
#define UART4_RX_Pin GPIO_PIN_11
#define UART4_RX_GPIO_Port GPIOC
#define UART5_TX_Pin GPIO_PIN_12
#define UART5_TX_GPIO_Port GPIOC
#define INT_IMU_Pin GPIO_PIN_0
#define INT_IMU_GPIO_Port GPIOD
#define UART5_RX_Pin GPIO_PIN_2
#define UART5_RX_GPIO_Port GPIOD
#define SYS_JTDO_TRACESWO_Pin GPIO_PIN_3
#define SYS_JTDO_TRACESWO_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_5
#define BUZZER_GPIO_Port GPIOB
#define SNS_HALL_IN_Pin GPIO_PIN_6
#define SNS_HALL_IN_GPIO_Port GPIOB
#define I2C1_SCL_Pin GPIO_PIN_8
#define I2C1_SCL_GPIO_Port GPIOB
#define I2C1_SDA_Pin GPIO_PIN_9
#define I2C1_SDA_GPIO_Port GPIOB
#define PWM_COOLING_Pin GPIO_PIN_1
#define PWM_COOLING_GPIO_Port GPIOE

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
//======================================================================================
