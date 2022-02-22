/**
 * @file RuntimeError.h
 * @author Tobias Sachse (t.sachse@esa-grimma.de)
 * @brief 
 * @version 3.90-32
 * @date 2022-02-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _RUNTIMEERROR_
#define _RUNTIMEERROR_

void RuntimeError(const char *message, int parameter, const char *file, int line);

#define RUNIME_ERROR(description, parameter)\
    RuntimeError(description, parameter, __FILE__, __LINE__)

#endif 