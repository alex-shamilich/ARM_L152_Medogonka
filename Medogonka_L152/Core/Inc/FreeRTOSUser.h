#ifndef INC_FREERTOSUSER_H_
#define INC_FREERTOSUSER_H_

#include "stm32l1xx_hal.h"

#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"



//MicroRL:
osMutexId 		MircoRL_Tx_MutexHandle;													// разграничение доступа к передаче данных в консоль
osMutexId 		MircoRL_TxCMD_MutexHandle;												// разграничение доступа к передаче данных в консоль (чтобы полный блок команды "get all" не разбивался другими командами)

osSemaphoreId 	MicroRL_xTxSemaphore;													// разграничение доступа к передаче данных в консоль
osSemaphoreId 	MicroRL_xRxSemaphore;


char MainCPU_Rx_Buffer[4];

#endif /* INC_FREERTOSUSER_H_ */
