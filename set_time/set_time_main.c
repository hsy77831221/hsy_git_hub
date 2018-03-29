#include "set_time_main.h"

extern hsy_shell_syscall shell_syscall[CMD_MAX];

void set_time_main(int argc, char *argv[])
{
#if _DEBUG_
	int i;
	DB_PRINT("%s\r\n", __func__);
	
	for(i = 0; i < argc; i++)
		DB_PRINT("[%d] : %s\r\n", i, argv[i]);
#endif
	
}
