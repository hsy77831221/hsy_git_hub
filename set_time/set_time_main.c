#include "set_time_main.h"

extern char* optarg;
extern int optind;
extern int opterr;
extern int optopt;

extern hsy_shell_syscall shell_syscall[CMD_MAX];

void set_time_main(int argc, char *argv[])
{
#if _DEBUG_
	int i;
	DB_PRINT("%s\r\n", __func__);
	
  DB_PRINT("--------------------------\n");
	for(i = 0; i < argc; i++)
		DB_PRINT("[%d] : %s\r\n", i, argv[i]);
  printf("--------------------------\n");
#endif
	if(argc < 5)
	{
		printf("parameter too short");
		return;
	}

	int ch;
	printf("\n\n");
	printf("optind:%d,opterr:%d\n",optind,opterr);
	printf("--------------------------\n");
	while ((ch = getopt(argc, argv, "ab:c:de::")) != -1)
	{
		printf("optind: %d\n", optind);
		switch (ch) 
        {
               case 'a':
                       printf("HAVE option: -a\n\n");   
                       break;
               case 'b':
                       printf("HAVE option: -b\n"); 
                       printf("The argument of -b is %s\n\n", optarg);
                       break;
               case 'c':
                       printf("HAVE option: -c\n");
                       printf("The argument of -c is %s\n\n", optarg);
                       break;
               case 'd':
                   printf("HAVE option: -d\n");
                     break;
              case 'e':
                    printf("HAVE option: -e\n");
                    printf("The argument of -e is %s\n\n", optarg);
                  break;
              case '?':
                       printf("Unknown option: %c\n",(char)optopt);
                       break;
               }
       }
    
       printf("----------------------------\n");
      printf("optind=%d,argv[%d]=%s\n",optind,optind,argv[optind]);

    printf("--------------------------\n");
    for(i=0;i<argc;i++)
    {
        printf("%s\n",argv[i]);
    }
    printf("--------------------------\n");
	
}

