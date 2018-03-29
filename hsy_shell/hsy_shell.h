/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HSY_SHELL_H
#define __HSY_SHELL_H

#include "stm32f3xx_hal.h"
#include "main.h"
#include "string.h"
#include "stdlib.h "
#include "help_main.h"
#include "list_main.h"
#include "set_time_main.h"

#define _DEBUG_		0

#if _DEBUG_
#define DB_PRINT(...) printf(__VA_ARGS__)
#else
#define DB_PRINT(...) 
#endif

#define CMD_LEN_MAX			64
#define	PARM_MAX				10
#define CMD_MAX					32

typedef struct
{
	const char* name;					/* the name of system call */
	void (*syscall)(); 	/* system call */
}hsy_shell_syscall;

typedef enum
{
  false = 0U,
  true
} bool;

extern UART_HandleTypeDef huart1;

void HsyShellStart(void);
void HsyShellScheduler(void);

#endif /* __LED_H */
