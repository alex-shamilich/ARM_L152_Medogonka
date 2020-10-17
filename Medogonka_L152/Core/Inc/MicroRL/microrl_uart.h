#ifndef MICRORL_UART_H
#define MICRORL_UART_H

// Транспортный слой для MicroRL + STM32L152
#include "stm32l1xx_hal.h"
#include "usart.h"																		// взаимодействие с транспортным слоем порта


#define MICRORL_USART						UART5										// на каком порту работает MicroRL

#define MICRORL_uartSIZE_OF_RING_BUFFER		128											// размер кольцевого буфера
#define MICRORL_UART_NO_DATA				(-1)										// код возврата, если в кольцевом буфере ничего нет

 typedef struct {
	uint8_t data[MICRORL_uartSIZE_OF_RING_BUFFER];
	int wrIdx;
	int rdIdx;
 } sRingBuf_t;

sRingBuf_t MircoRL_sTxRingBuf;
sRingBuf_t MircoRL_sRxRingBuf;


void MICRORL_UART_SendChar(uint8_t data);
void MICRORL_UART_SendString(const char *str);

int  MICRORL_UART_GetChar();
int  MICRORL_UART_GetCharBlocking();

// https://habrahabr.ru/post/127890/
// https://github.com/Helius/microrl
// http://catethysis.ru/stm32-uart-console/

#endif // MICRORL_UART_H
