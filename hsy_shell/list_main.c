#include "list_main.h"

extern hsy_shell_syscall shell_syscall[CMD_MAX];

void list_main(int argc, char *argv[])
{
#if _DEBUG_
	int i;
	DB_PRINT("%s\r\n", __func__);
	
	for(i = 0; i < argc; i++)
		DB_PRINT("[%d] : %s\r\n", i, argv[i]);
#endif
	int j;
	DB_PRINT("CMD LIST:\r\n");
	for(j = 0; j < CMD_MAX; j++)
	{
		DB_PRINT("	%s\r\n", shell_syscall[j].name );
		if(shell_syscall[j + 1].name == NULL)
			break;
	}
}

