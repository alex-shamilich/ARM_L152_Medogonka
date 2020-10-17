#ifndef MICRORL_FUNC_HELP_H_
#define MICRORL_FUNC_HELP_H_


void prv_printMainHelp();
void prv_printTerminalFuncHelp(const char *name);
int  prv_TerminalFunc_help(int argc, const char * const * argv);

extern int terminalFuncArrayIndex;

#endif // MICRORL_FUNC_HELP_H_
