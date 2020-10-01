#ifndef __spi_H
#define __spi_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

// GPIO для SPI1
#define SPI1_SD_SCK_Pin 		GPIO_PIN_5
#define SPI1_SD_SCK_GPIO_Port 	GPIOA

#define SPI1_SD_MISO_Pin 		GPIO_PIN_6
#define SPI1_SD_MISO_GPIO_Port 	GPIOA

#define SPI1_SD_MOSI_Pin 		GPIO_PIN_7
#define SPI1_SD_MOSI_GPIO_Port 	GPIOA

#define SPI1_SD_CS_Pin 			GPIO_PIN_12
#define SPI1_SD_CS_GPIO_Port 	GPIOB

// GPIO для SPI2:
#define SPI2_SCK_Pin 			GPIO_PIN_13
#define SPI2_SCK_GPIO_Port 		GPIOB

#define SPI2_MISO_Pin 			GPIO_PIN_14
#define SPI2_MISO_GPIO_Port 	GPIOB

#define SPI2_MOSI_Pin 			GPIO_PIN_15
#define SPI2_MOSI_GPIO_Port 	GPIOB

#define SPI2_LCD_RST_Pin 		GPIO_PIN_1
#define SPI2_LCD_RST_GPIO_Port 	GPIOC

#define SPI2_LCD_CS_Pin 		GPIO_PIN_2
#define SPI2_LCD_CS_GPIO_Port 	GPIOC

#define SPI2_LCD_DC_Pin 		GPIO_PIN_0
#define SPI2_LCD_DC_GPIO_Port 	GPIOC

#define SPI2_LCD_LED_Pin 		GPIO_PIN_3
#define SPI2_LCD_LED_GPIO_Port 	GPIOC





extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

void MX_SPI1_Init(void);
void MX_SPI2_Init(void);

#ifdef __cplusplus
}
#endif
#endif /*__ spi_H */
