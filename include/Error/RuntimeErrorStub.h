/**
 * @file RuntimeErrorStub.h
 * @author Tobias Sachse (t.sachse@esa-grimma.de)
 * @brief 
 * @version 3.90-32
 * @date 2022-02-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _RUNTIMEERRORSTUB_
#define _RUNTIMEERRORSTUB_

void RuntimeErrorStub_Reset(void);
const char *RuntimeErrorStub_GetLastError(void);
int RuntimeErrorStub_GetLastParameter(void);

#endif