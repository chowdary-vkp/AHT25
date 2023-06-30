/*
 * uart.h
 *
 *  Created on: Jun 24, 2023
 *      Author: dinesh
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
/* Include END */

/* Defines BEGIN */
#define UART_MAXDELAY 1000U
/* Defines END */



/* PFP BEGIN */
void UART_Printf(const char* fmt, ...);
void UART_Printf_Dbg(const char* fmt, ...);
/* PFP END */



#endif /* INC_UART_H_ */
