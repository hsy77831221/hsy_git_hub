#include "hsy_shell.h"

uint8_t hsy_shell_buffer;

uint8_t aRxBuffer[CMD_LEN_MAX];
uint8_t aRxBuffer_n = 0;
uint8_t CmdBuffer[CMD_LEN_MAX];
uint8_t CmdLen = 0;
bool CmdFlag = false;

//int argc,char *argv[]

uint8_t CmdDec(uint8_t *src, uint8_t des[CMD_LEN_MAX][PARM_MAX])
{
	uint8_t buf_tmp[CMD_LEN_MAX];
	uint8_t buf_befor[CMD_LEN_MAX];
	uint8_t buf_after[CMD_LEN_MAX];
	uint8_t i, j;
	
	memset(buf_tmp, 0, sizeof(buf_tmp));
	memset(buf_befor, 0, sizeof(buf_befor));
	memset(buf_after, 0, sizeof(buf_after));
	strcpy((char *)buf_tmp, (char *)src);
	
	if(strstr((char *)buf_tmp, " ") == NULL)
	{
		strcpy((char *)des[0], (char *)src);
		return 1;
	}
	
	for(j = 0; j < PARM_MAX; j++)
	{
		strcpy((char *)des[j], (char *)buf_after);
		if(strstr((char *)buf_tmp, " ") == NULL)
			return j + 1;
		
		strcpy((char *)buf_after, strstr((char *)buf_tmp, " "));
		if(buf_after[0] == '\0')
			return j + 1;
	
//		for(i = 0; i < (strlen((char *)buf_tmp)-strlen((char *)buf_after)); i++)
//			buf_befor[i] = buf_tmp[i];

		i = (strlen((char *)buf_tmp)-strlen((char *)buf_after));
		memcpy(buf_befor, buf_tmp, i);
		buf_befor[i] = '\0';
		
		strncpy((char *)buf_after, (char *)buf_after + 1, strlen((char *)buf_after) - 1);
		*(buf_after + strlen((char *)buf_after) - 1) = '\0';
		strcpy((char *)des[j], (char *)buf_befor);
		strcpy((char *)buf_tmp, (char *)buf_after);
	}
	
	return j + 1;
}

void CmdMain(void) 
{
	struct hsy_shell_syscall syscall;
	uint8_t i;
	uint8_t DecBuff[CMD_LEN_MAX][PARM_MAX];
	uint8_t DecLen = 0;
	
	memset(DecBuff, 0, sizeof(DecBuff));
	
	DB_PRINT("%s\r\n", __func__);
	
	DecLen = CmdDec(CmdBuffer, DecBuff);
	
	DB_PRINT("DecLen : %d\r\n", DecLen);
	
	for(i = 0; i < DecLen; i++)
		DB_PRINT("i[%d]:%s\r\n", i, DecBuff[i]);
	
//	uint8_t buf[]
	
	CmdFlag = false;
}

void CmdExcute(void)
{
	memcpy(CmdBuffer, aRxBuffer, CMD_LEN_MAX);
	CmdLen = aRxBuffer_n;
	CmdFlag = true;
	
	memset(aRxBuffer, 0, sizeof(aRxBuffer));
	aRxBuffer_n = 0;
}

void CmdPush(uint8_t pData)
{
	if(aRxBuffer_n < CMD_LEN_MAX)
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
//	DB_PRINT("%s begin\r\n", __func__);
	if(CmdNewLine(pData))
		CmdExcute();
	else
		CmdPush(pData);
//	DB_PRINT("%s end\r\n", __func__);
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


