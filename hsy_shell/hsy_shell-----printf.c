#include "hsy_shell.h"

uint8_t hsy_shell_buffer;

uint8_t aRxBuffer[64];
uint8_t aRxBuffer_n = 0;
uint8_t CmdBuffer[64];
uint8_t CmdLen = 0;
bool CmdFlag = false;

//int argc,char *argv[]

uint8_t CmdDec(uint8_t *src, uint8_t des[64][8])
{
	uint8_t buf_tmp[64];
	uint8_t buf_befor[64];
	uint8_t buf_after[64];
	uint8_t i, j;
	
	memset(buf_tmp, 0, sizeof(buf_tmp));
	memset(buf_befor, 0, sizeof(buf_befor));
	memset(buf_after, 0, sizeof(buf_after));
	strcpy((char *)buf_tmp, (char *)src);
	
	for(j = 0; j < 8; j++)
	{
		printf("j : %d\r\n", j);
		
		strcpy((char *)des[j], (char *)buf_after);
		
		if(strstr((char *)buf_tmp, " ") == NULL)
			return j;
	
		strcpy((char *)buf_after, strstr((char *)buf_tmp, " "));
	
		if(buf_after[0] == '\0')
			return j;
	
		printf("len_full: %d len_after : %d\r\n", strlen((char *)buf_tmp), strlen((char *)buf_after));
	
		for(i = 0; i < (strlen((char *)buf_tmp)-strlen((char *)buf_after)); i++)
		{
			printf("i[%d] bef:%x tmp:%x\r\n", i, buf_befor[i], buf_tmp[i]);
			buf_befor[i] = buf_tmp[i];
		}
	
		buf_befor[i] = '\0';
	
		strncpy((char *)buf_after, (char *)buf_after + 1, strlen((char *)buf_after) - 1);
	
		*(buf_after + strlen((char *)buf_after) - 1) = '\0';
	
		printf("buf_tmp:%s\r\n", buf_tmp);
		printf("buf_befor:%s\r\n", buf_befor);
		printf("buf_after:%s\r\n", buf_after);
		
		strcpy((char *)des[j], (char *)buf_befor);
		strcpy((char *)buf_tmp, (char *)buf_after);
	}
	
	return j;
}

void CmdMain(void) 
{
	struct hsy_shell_syscall syscall;
	uint8_t i;
	uint8_t DecBuff[64][8];
	uint8_t DecLen = 0;
	
	memset(DecBuff, 0, sizeof(DecBuff));
	
	printf("%s\r\n", __func__);
	
	DecLen = CmdDec(CmdBuffer, DecBuff);
	
	for(i = 0; i < DecLen + 1; i++)
		printf("i[%d]:%s\r\n", i, DecBuff[i]);
	
//	uint8_t buf[]
	
	CmdFlag = false;
}

void CmdExcute(void)
{
	memcpy(CmdBuffer, aRxBuffer, 64);
	CmdLen = aRxBuffer_n;
	CmdFlag = true;
	
	memset(aRxBuffer, 0, sizeof(aRxBuffer));
	aRxBuffer_n = 0;
}

void CmdPush(uint8_t pData)
{
	if(aRxBuffer_n < 64)
	{
		aRxBuffer[aRxBuffer_n] = pData;
		aRxBuffer_n++;
	}
}

bool CmdNewLine(uint8_t pData)
{
	if((pData == '\n') || (pData == '\r'))
		return true;
	
	return false;
}

void UartPro(uint8_t pData)
{
//	printf("%s begin\r\n", __func__);
	if(CmdNewLine(pData))
		CmdExcute();
	else
		CmdPush(pData);
//	printf("%s end\r\n", __func__);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UNUSED(huart);
	HAL_UART_Transmit(&huart1, &hsy_shell_buffer, 1,0xFFFF);
	UartPro(hsy_shell_buffer);
	HAL_UART_Receive_IT(&huart1, &hsy_shell_buffer, 1);
}

void HsyShellStart(void)
{
	HAL_UART_Receive_IT(&huart1, &hsy_shell_buffer, 1);
}

void HsyShellScheduler(void)
{
	if(CmdFlag)
		CmdMain();
	HAL_UART_Receive_IT(&huart1, &hsy_shell_buffer, 1);
}


