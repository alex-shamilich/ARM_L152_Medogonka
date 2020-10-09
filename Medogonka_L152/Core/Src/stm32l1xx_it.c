#include "main.h"
#include "stm32l1xx_it.h"

extern PCD_HandleTypeDef hpcd_USB_FS;
extern ADC_HandleTypeDef hadc;
extern DMA_HandleTypeDef hdma_spi2_tx;

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim7;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;



//======================================================================================
/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
void NMI_Handler(void)																	// Non maskable interrupt.
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}
//======================================================================================
void HardFault_Handler(void)															// Hard fault interrupt.
{
  while (1)
  {
  }
}
//======================================================================================
void MemManage_Handler(void)															// Memory management fault.
{
  while (1)
  {
  }
}
//======================================================================================
void BusFault_Handler(void)																// Pre-fetch fault, memory access fault.
{
  while (1)
  {
  }
}
//======================================================================================
void UsageFault_Handler(void)															// Undefined instruction or illegal state.
{
  while (1)
  {
  }
}
//======================================================================================
/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
}
//======================================================================================

/******************************************************************************/
/* STM32L1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l1xx.s).                    */
/******************************************************************************/

//======================================================================================
void DMA1_Channel5_IRQHandler(void)														// DMA1 channel5 global interrupt.
{
  HAL_DMA_IRQHandler(&hdma_spi2_tx);
}
//======================================================================================
void ADC1_IRQHandler(void)																// ADC global interrupt.
{
  HAL_ADC_IRQHandler(&hadc);
}
//======================================================================================
void USB_LP_IRQHandler(void)															// USB low priority interrupt.
{
  HAL_PCD_IRQHandler(&hpcd_USB_FS);
}
//======================================================================================
void USART1_IRQHandler(void)															// USART1 global interrupt.
{
  HAL_UART_IRQHandler(&huart1);
}
//======================================================================================
void USART2_IRQHandler(void)															// USART2 global interrupt.
{
  HAL_UART_IRQHandler(&huart2);
}
//======================================================================================
void USART3_IRQHandler(void)															// USART3 global interrupt.
{
  HAL_UART_IRQHandler(&huart3);
}
//======================================================================================
void UART4_IRQHandler(void)																// UART4 global interrupt.
{
  HAL_UART_IRQHandler(&huart4);
}
//======================================================================================
void UART5_IRQHandler(void)																// UART5 global interrupt.
{
  HAL_UART_IRQHandler(&huart5);
}
//======================================================================================
void TIM3_IRQHandler(void)																// TIM3 global interrupt.
{
  HAL_TIM_IRQHandler(&htim3);
}
//======================================================================================
void TIM4_IRQHandler(void)																// TIM4 global interrupt.
{
  HAL_TIM_IRQHandler(&htim4);
}
//======================================================================================
void TIM6_IRQHandler(void)																// TIM6 global interrupt.
{
  HAL_TIM_IRQHandler(&htim6);
}
//======================================================================================
void TIM7_IRQHandler(void)																// TIM7 global interrupt.
{
  HAL_TIM_IRQHandler(&htim7);
}
//======================================================================================

