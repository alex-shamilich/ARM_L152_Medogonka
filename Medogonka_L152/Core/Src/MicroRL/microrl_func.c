#include <string.h>																		// for strcmp, strstr

#include "ExchangeStruct.h"
#include "FreeRTOSUser.h"

#include "microrl.h"
#include "microrl_uart.h"																// взаимодействие с транспортным слоем порта
#include "microrl_func.h"

// Функции пользователя:
#include "microrl_func_help.h"
#include "microrl_func_get.h"
#include "microrl_func_set.h"
#include "microrl_func_calibrate.h"
#include "microrl_func_about.h"
#include "microrl_func_clear.h"
#include "microrl_func_reset.h"
#include "microrl_func_pwroff.h"



//Define this macros with correct write/read terminal functions
#define microrl_getChar			MICRORL_UART_GetCharBlocking
#define microrl_sendString		MICRORL_UART_SendString

microrl_t rl;																			// Main terminal object
microrl_t * prl = &rl;

static int prv_execute(int argc, const char * const * argv);

#ifdef _USE_COMPLETE
  static char ** prv_complet (int argc, const char * const * argv);
#endif

#ifdef _USE_CTLR_C
  static void prv_sigint (void);
#endif

static void prv_registerBasicTerminalFuncs();

char str[255];																			//  буфер sprintf для вывода сообщений в терминал
int terminalFuncArrayIndex = 0;

//=======================================================================================
void microrl_terminalInit()
{
	prv_registerBasicTerminalFuncs();

	if (ExchangeStruct.TerminalFormat == TERMINALFORMAT_HUMAN)
	{
		prv_TerminalFunc_about(0, NULL);												// вывести строку из "About..."
		prv_printMainHelp();															// подсказку с помощью
	}

	microrl_init(prl, microrl_sendString);
	microrl_set_execute_callback (prl, prv_execute);

	#ifdef _USE_COMPLETE
		microrl_set_complete_callback (prl, prv_complet);
	#endif

	#ifdef _USE_CTLR_C
		microrl_set_sigint_callback (prl, prv_sigint);
	#endif
}
//=======================================================================================
void microrl_terminalProcess()
{
	microrl_insert_char(prl, microrl_getChar());
}
//=======================================================================================
void microrl_registerExecuteFunc(int (*func)(int, const char* const*), const char* name, const char* help)
{
	assert_param(terminalFuncArrayIndex < microrlNUM_OF_TERMINAL_FUNC);

	terminalFuncArray[terminalFuncArrayIndex].func = func;
	terminalFuncArray[terminalFuncArrayIndex].name = name;
	terminalFuncArray[terminalFuncArrayIndex].help = help;

	terminalFuncArrayIndex++;
}
//=======================================================================================
void microrl_printString(const char *str)
{
	microrl_sendString(str);
}
//=======================================================================================
void microrl_printStringWithEndl(const char *str)
{
	microrl_sendString(str);
	microrl_sendString(ENDL);
}
//=======================================================================================
void microrl_printEndl()
{
	microrl_sendString(ENDL);
}
//=======================================================================================
static void prv_registerBasicTerminalFuncs()
{
	microrl_registerExecuteFunc(prv_TerminalFunc_about, 	"about", 		"Version Info");
	microrl_registerExecuteFunc(prv_TerminalFunc_help, 		"help", 		"View the available commands and their descriptions");
	microrl_registerExecuteFunc(prv_TerminalFunc_clear, 	"clear", 		"Clears the screen.");
	microrl_registerExecuteFunc(prv_TerminalFunc_get, 		"get", 			"Type 'get' without parameters for help");
	microrl_registerExecuteFunc(prv_TerminalFunc_set, 		"set", 			"Type 'set' without parameters for help");
	microrl_registerExecuteFunc(prv_TerminalFunc_reset,		"reset", 		"Type 'reset' without parameters for help");
	microrl_registerExecuteFunc(prv_TerminalFunc_calibrate, "calibrate", 	"Calibrate compass");
	microrl_registerExecuteFunc(prv_TerminalFunc_pwroff,    "pwroff", 		"Unlock main power switch to gracefull shutdown");
}
//=======================================================================================
int prv_getFuncArrayIndex(const char * name)
{
	int i;
	for (i = 0; i < terminalFuncArrayIndex; ++i) {
		if (strcmp(name, terminalFuncArray[i].name) == 0)	{
			return i;
		}
	}
	return (-1);
}
//=======================================================================================
static int prv_execute(int argc, const char * const * argv)
{
	int funcIndex;

	funcIndex = prv_getFuncArrayIndex(argv[0]);
	if (funcIndex == (-1))	{
		microrl_printStringWithEndl("Unknown command. Type \"help\" to see available commands");
		return (-1);
	}
	return terminalFuncArray[funcIndex].func(--argc, ++argv);
}
//=======================================================================================
#ifdef _USE_COMPLETE
//TODO simplify this. Quite difficult.
static char ** prv_complet (int argc, const char * const * argv)
{
	static char * compl_world [microrlNUM_OF_TERMINAL_FUNC + 1];
	int j = 0, i;
	compl_world[0] = NULL;
	if (argc == 1)	{
		char * bit = (char*)argv [argc-1];
		for (i = 0; i < terminalFuncArrayIndex; i++) {
			if (strstr(terminalFuncArray[i].name, bit) == terminalFuncArray[i].name) {
				compl_world [j++] = (char*)(terminalFuncArray[i].name);
			}
		}
	}
	compl_world [j] = NULL;
	return compl_world;
}
#endif
//=======================================================================================
#ifdef _USE_CTLR_C
static void prv_sigint (void)
{
	NVIC_SystemReset();
}
#endif
//=======================================================================================



//=======================================================================================
void TerminalPrintINT_KEYS(void)														// если было какое либо изменение состояния кнопок - сразу пишем в терминал сообщение об этом
{
//	osStatus statusTx		= osMutexWait(MircoRL_Tx_MutexHandle, portMAX_DELAY);		// ждем пока не освободиться порт терминала на передачу
//	osStatus statusCMD      = osMutexWait(MircoRL_TxCMD_MutexHandle, portMAX_DELAY);	// ждем пока не закончится передача полного блока команды "get all"
//
//	if ((statusCMD == osOK)&&(statusTx == osOK))
//	{
//		//microrl_printString(ENDL);    // new line
//
//		if (ExchangeStruct.TerminalFormat == TERMINALFORMAT_HUMAN)
//		{
//			microrl_printString(ENDL);    // new line
//		}
//
//		sprintf(str, "KEYS=0x%04X\n", ExchangeStruct.Keys_State->Buttons);
//		microrl_printString(str);
//
//		if (ExchangeStruct.TerminalFormat == TERMINALFORMAT_HUMAN)
//		{
//			microrl_printString(prl->prompt_str);
//		}
//		else
//		{
//		}
//
//		osMutexRelease(MircoRL_TxCMD_MutexHandle);
//		osMutexRelease(MircoRL_Tx_MutexHandle);
//	}
}
//=======================================================================================
void TerminalPrintINT_ENCODER(void)														// если было какое либо изменение состояния энкодера - сразу пишем в терминал сообщение об этом
{
//	osStatus statusTx		= osMutexWait(MircoRL_Tx_MutexHandle, portMAX_DELAY);		// ждем пока не освободиться порт терминала на передачу
//	osStatus statusCMD      = osMutexWait(MircoRL_TxCMD_MutexHandle, portMAX_DELAY);	// ждем пока не закончится передача полного блока команды "get all"
//
//	if ((statusCMD == osOK)&&(statusTx == osOK))
//	{
//		if (ExchangeStruct.TerminalFormat == TERMINALFORMAT_HUMAN)
//		{
//			microrl_printString(ENDL);    // new line
//		}
//
//		//sprintf(str, "ENCODER_VAL=%d\t", 				(int8_t)(MP_ExchangeStruct.Encoder_State->MP_Encoder_Value - ENCODER_VAL_DEFAULT));	microrl_printString(str);
//		sprintf(str, "ENCODER_VAL=%u\t", 				(uint8_t)(ExchangeStruct.Encoder_State->MP_Encoder_Value));						microrl_printString(str);
//		sprintf(str, "ENCODER_DIR=%lu\t", 				ExchangeStruct.Encoder_State->MP_Encoder_Dir);									microrl_printString(str);
//		sprintf(str, "ENCODER_DELTA=%d\n", 				(int8_t)(ExchangeStruct.Encoder_State->MP_Encoder_Delta));						microrl_printString(str);
//		//sprintf(str, "ENCODER_DELTA=%ld\n", 			(MP_ExchangeStruct.Encoder_State->MP_Encoder_Delta));								microrl_printString(str);
//
//		if (ExchangeStruct.TerminalFormat == TERMINALFORMAT_HUMAN)
//		{
//			microrl_printString(prl->prompt_str);
//		}
//		else
//		{
//		}
//
//		osMutexRelease(MircoRL_TxCMD_MutexHandle);
//		osMutexRelease(MircoRL_Tx_MutexHandle);
//	}
}
//=======================================================================================
void TerminalPrintINT_LRF(void)															// если пришли данные от дальномера - сразу пишем в терминал сообщение об этом
{
//	osStatus statusTx		= osMutexWait(MircoRL_Tx_MutexHandle, portMAX_DELAY);		// ждем пока не освободиться порт терминала на передачу
//	osStatus statusCMD      = osMutexWait(MircoRL_TxCMD_MutexHandle, portMAX_DELAY);	// ждем пока не закончится передача полного блока команды "get all"
//
//	if (( ExchangeStruct.LRF1502_State->Target1 >0 ) && (statusCMD == osOK) && (statusTx == osOK))
//
//
//	if ((statusCMD == osOK) )			// если порт свободен и расстояние до цели  > 0
//	{
//		if (ExchangeStruct.TerminalFormat == TERMINALFORMAT_HUMAN)
//		{
//			microrl_printString(ENDL);    // new line
//		}
//
//		sprintf(str, "\nLRF_TARGET_DIST=%d\n", ExchangeStruct.LRF1502_State->Target1);														microrl_printString(str);
//
//		TerminalPrintGet_TARGET();														// если доступны координаты, то показать координаты цели
//		microrl_printString(prl->prompt_str);
//
//		osMutexRelease(MircoRL_TxCMD_MutexHandle);
//		osMutexRelease(MircoRL_Tx_MutexHandle);
//
//	}
}
//=======================================================================================

