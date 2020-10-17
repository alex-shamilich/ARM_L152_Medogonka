// Транспортный слой для MicroRL + STM32L152
#include "microrl_uart.h"

#include "FreeRTOSUser.h"

//=======================================================================================
void MICRORL_UART_SendChar(uint8_t data)
{
	xSemaphoreTake(MicroRL_xTxSemaphore, portMAX_DELAY);
//	prv_SendChar(data);
	while(!(MICRORL_USART->SR & USART_SR_TC)); 											//Ждем установки флага TC - завершения передачи
	MICRORL_USART->DR = data;

	xSemaphoreGive(MicroRL_xTxSemaphore);
}
//=======================================================================================
void MICRORL_UART_SendString(const char *str)
{
	xSemaphoreTake(MicroRL_xTxSemaphore, portMAX_DELAY);
	int i = 0;
	while (str[i] != 0)
	{
//		prv_SendChar(str[i]);
		while(!(MICRORL_USART->SR & USART_SR_TC)); 										//Ждем установки флага TC - завершения передачи
		MICRORL_USART->DR = str[i];
		i++;
	}
	xSemaphoreGive(MicroRL_xTxSemaphore);
}
//=======================================================================================
int MICRORL_UART_GetChar()
{
	uint8_t data;
	if (MircoRL_sRxRingBuf.wrIdx != MircoRL_sRxRingBuf.rdIdx)
	{
		data = MircoRL_sRxRingBuf.data[MircoRL_sRxRingBuf.rdIdx++];
		if (MircoRL_sRxRingBuf.rdIdx >= MICRORL_uartSIZE_OF_RING_BUFFER)
		{
			MircoRL_sRxRingBuf.rdIdx = 0;
		}
		return (int)data;
	}
	else
	{
		return (MICRORL_UART_NO_DATA);
	}
}
//=======================================================================================
int MICRORL_UART_GetCharBlocking()
{
	xSemaphoreTake(MicroRL_xRxSemaphore, portMAX_DELAY);
	return MICRORL_UART_GetChar();
}
//=======================================================================================
