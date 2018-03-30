#include "set_time_main.h"

extern char* optarg;
extern int optind;
extern int opterr;
extern int optopt;
extern int set_time;
extern int real_time;

extern hsy_shell_syscall shell_syscall[CMD_MAX];

void set_time_main(int argc, char *argv[])
{
#if _DEBUG_
	int i;
	DB_PRINT("%s\r\n", __func__);
	
  DB_PRINT("--------------------------\r\n");
	for(i = 0; i < argc; i++)
		DB_PRINT("[%d] : %s\r\n", i, argv[i]);
  printf("--------------------------\r\n");
#endif
	if(argc < 2)
	{
		printf("parameter too short\r\n");
		return;
	}

	int ch;
	unsigned int hour, min, sec;
	while ((ch = getopt(argc, argv, "r:s:")) != -1)
	{
		printf("optind: %d \r\n", optind);
		switch(ch)
			{
			case 's':
				if((optind > argc) || (optind + 1 > argc))
					break;
				sscanf(optarg, "%d", &hour);
				sscanf(argv[optind], "%d", &min);
				sscanf(argv[optind + 1], "%d", &sec);
				set_time = (hour * 3600) + (min * 60) + sec;
				
				printf("Set fetch time : %s:%s:%s\r\n\r\n", optarg, argv[optind], argv[optind + 1]);
				printf("fetch time second : %d\r\n\r\n", set_time);
				break;
			case 'r':
				if((optind > argc) || (optind + 1 > argc))
					break;
				sscanf(optarg, "%d", &hour);
				sscanf(argv[optind], "%d", &min);
				sscanf(argv[optind + 1], "%d", &sec);
				real_time = (hour * 3600) + (min * 60) + sec;
				printf("Set real time : %s:%s:%s\r\n\r\n", optarg, argv[optind], argv[optind + 1]);
				printf("real time second : %d\r\n\r\n", real_time);
				break;
			case '?':
				printf("Unknown option : %c\r\n", (char)optopt);
				break;
			}
	}
	optind = 1;
}

