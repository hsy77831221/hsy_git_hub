/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HSY_SHELL_H
#define __HSY_SHELL_H

#include "stm32f3xx_hal.h"
#include "main.h"
#include "string.h"
#include "stdlib.h "

struct hsy_shell_syscall
{
	const char* name;		/* the name of system call */
	const char* desc;		/* description of system call */
};

typedef enum
{
  false = 0U,
  true
} bool;

extern UART_HandleTypeDef huart1;

void HsyShellStart(void);
void HsyShellScheduler(void);

#endif /* __LED_H */
