#ifndef MICRORL_FUNC_GET_H_
#define MICRORL_FUNC_GET_H_

void prv_printHelpGet(void);
int  prv_TerminalFunc_get(int argc, const char * const * argv);
void prv_TerminalFuncGetParams(const char *name);


void TerminalPrintGet_PWR(void);
void TerminalPrintGet_BAT(void);
void TerminalPrintGet_PWRSource(void);
void TerminalPrintGet_BATCatlibration(void);
void TerminalPrintGet_COMPASS(void);
void TerminalPrintGet_KEYS(void);
void TerminalPrintGet_GPS(void);
void TerminalPrintGet_TIME(void);
void TerminalPrintGet_LRF(void);
void TerminalPrintGet_FIRE(void);
void TerminalPrintGet_TARGET(void);
void TerminalPrintGet_MODE(void);
void TerminalPrintGet_SERIAL(void);
void TerminalPrintGet_BUZZER(void);


#endif // MICRORL_FUNC_GET_H_
