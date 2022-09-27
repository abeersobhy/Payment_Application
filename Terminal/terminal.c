#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "std_types.h"
#include "card.h"
#include "terminal.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{	 
    SYSTEMTIME dt; 
    GetSystemTime(&dt);
    termData->transactionDate[0] = dt.wMonth;
    termData->transactionDate[1] = (dt.wYear%100); 	
	if(strlen(termData->transactionDate) == 0) 
	{
		return WRONG_DATE;
	}
	else
	{
        return OKK; 		
	}
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	if(termData.transactionDate[1] > cardData.cardExpirationDate[1]) /*currentDate is after the expired date.*/
	{
		return EXPIRED_CARD;  /*Card is expired*/
	}
    else if(termData.transactionDate[1] < cardData.cardExpirationDate[1])
	{
		return OKK; /*Card is not expired*/
	}
    else /*the same year*/
	{
		if(termData.transactionDate[0] < cardData.cardExpirationDate[0])
		{
			return OKK;
		}
		else
		{
			return EXPIRED_CARD;
		}
	}
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	int8_t ch; 
    printf("Enter the transaction amount : ");
    scanf("%f", &termData->transAmount);
	scanf("%c", &ch);
	if(termData->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}		
	else
	{
		return OKK;
	}
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	if((termData->transAmount) > (termData->maxTransAmount))
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return OKK;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
	termData->maxTransAmount = 50000;
	if(termData->maxTransAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		return OKK;
	}
}














