// terminal function: PWROFF
#include <string.h>				// for strcmp, strstr

#include "microrl_func.h"
#include "microrl_func_pwroff.h"

#include "FreeRTOSUser.h"
//#include "MP_Power.h"

//=======================================================================================
int prv_TerminalFunc_pwroff(int argc, const char * const * argv)
{
////	microrl_printString ("Set something...");
////	microrl_printEndl();
//	UNUSED(argc);
//	UNUSED(argv);
//
//	osStatus status = osMutexWait(MircoRL_Tx_MutexHandle, portMAX_DELAY);					// ждем пока не освободиться порт терминала на передачу
//
//	if (status == osOK)
//	{
//		switch (argc)
//		{
//		case 0:																				// если вызвали pwroff без параметра - показать help
//			//prv_printHelpPwroff();
//			microrl_printStringWithEndl("Now ready to gracefull power shutdown");
//			MP_Power_Set_Power_Hold(POWERSTATE_DISABLE);									// Разблокировать выключатель питания
//			break;
//		default:																			// двойной уровень параметров не сделан
//			microrl_printStringWithEndl("pwroff is available only without parameters.");
//			break;
//		}
//
//		osMutexRelease(MircoRL_Tx_MutexHandle);
//	}
//
//
	return 0;

}
//=======================================================================================
void prv_printHelpPwroff(void)
{
	// здесь нужно расписать какие есть параметры у calibrate
	microrl_printStringWithEndl("pwroff <no parameters> - unlock power switch to gracefull power shutdown");

	microrl_printEndl();
}
//=======================================================================================
