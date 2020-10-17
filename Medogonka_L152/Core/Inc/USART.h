#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

// GPIO для UART
#define USART1_TX_Pin 		GPIO_PIN_9
#define USART1_TX_GPIO_Port GPIOA

#define USART1_RX_Pin 		GPIO_PIN_10
#define USART1_RX_GPIO_Port GPIOA

// Virtual COM-Port возможность вывода сообщений с помощью простого printf (переопределен putc и заглушки к stdlib)
#define USART2_TX_Pin 		GPIO_PIN_2
#define USART2_TX_GPIO_Port GPIOA

#define USART2_RX_Pin 		GPIO_PIN_3
#define USART2_RX_GPIO_Port GPIOA


#define USART3_TX_Pin 		GPIO_PIN_10
#define USART3_TX_GPIO_Port GPIOB

#define USART3_RX_Pin 		GPIO_PIN_11
#define USART3_RX_GPIO_Port GPIOB

// терминальная связь с ПК
#define UART4_TX_Pin 		GPIO_PIN_10
#define UART4_TX_GPIO_Port 	GPIOC

#define UART4_RX_Pin 		GPIO_PIN_11
#define UART4_RX_GPIO_Port 	GPIOC

 // Консоль MicroRL
#define UART5_TX_Pin 		GPIO_PIN_12
#define UART5_TX_GPIO_Port 	GPIOC

#define UART5_RX_Pin 		GPIO_PIN_2
#define UART5_RX_GPIO_Port 	GPIOD


extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;


void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);
void MX_UART4_Init(void);
void MX_UART5_Init(void);

#define PRIORITY_ISR_USART5_MainCPU	5
#define PRIORITY_ISR_USART4			6
#define PRIORITY_ISR_USART3 		7
#define PRIORITY_ISR_USART2 		8
#define PRIORITY_ISR_USART1 		9


#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */
