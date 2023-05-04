#ifndef LOG_H
#define LOG_H

#include "../../Config.h"
#include <stdio.h>

FILE* OpenLog  ();
void  WriteLog (const char* format_data, ...);
void  CloseLog ();

#endif
