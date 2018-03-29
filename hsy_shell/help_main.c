#include "help_main.h"

void help_main(int argc, char *argv[])
{
#if _DEBUG_
	int i;
	DB_PRINT("%s\r\n", __func__);
	
	for(i = 0; i < argc; i++)
		DB_PRINT("[%d] : %s\r\n", i, argv[i]);
#endif
	DB_PRINT("help information\r\n");
	DB_PRINT("no more ' '\r\n");
	DB_PRINT("parameter no '-'\r\n");
	DB_PRINT("use CMD \"list\" print all CMD\r\n");
}

