#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "std_types.h"
#include "card.h"
#include "terminal.h"
#include "server.h"
uint8_t position = 0;
ST_accountsDB_t server_side_accounts[255] = {{50000 , "1111222233334444"},
                                            {250000 ,"1111000033334444"}};

ST_transaction_t server_side_transactions[255] = {0}; 

EN_transStat_t recieveTransactionData(ST_transaction_t *transData)
{
	static int32_t numOfTransactions = 0;
	uint8_t flag = 0 , i;
    for(i = 0 ; i < SERVER_ACCOUNTS_NUM ; i++)
	{
		if(strcmp(server_side_accounts[i].primaryAccountNumber , transData->cardHolderData.primaryAccountNumber) == 0)
		{
			flag = 1;
			break;
		}
	}
	if(flag == 0)
	{
		return DECLINED_STOLEN_CARD;
	}
	else
	{
		if(transData->terminalData.transAmount > server_side_accounts[i].balance)
		{
			return DECLINED_INSUFFECIENT_FUND;
		}
		if(numOfTransactions >= 255) /*Transaction can not be saved.*/
		{
            return INTERNAL_SERVER_ERROR;			
		}
		else
		{
			numOfTransactions++;
			server_side_accounts[i].balance -= transData->terminalData.transAmount;
			return APPROVED;
		}
		
	} 
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
	uint8_t flag = 0;
    for(int i = 0 ; i < SERVER_ACCOUNTS_NUM ; i++)
	{
		if(strcmp(server_side_accounts[i].primaryAccountNumber , cardData->primaryAccountNumber) == 0)
		{
			position = i;
			flag = 1;
			break;
		}
	}
	if(flag == 1) /*PAN exist.*/
	{
		return OKAY;
	}
	else /*ACCOUNT_NOT_FOUND*/
	{
		return ACCOUNT_NOT_FOUND;
	}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    if((server_side_accounts[position].balance >= termData->transAmount))
	{
		return OKAY; /*Amount is avilable.*/
	}
    else	
	{
		return LOW_BALANCE; /*Amount is not avilable.*/
	}
}
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
	static uint8_t iterator = 0;
	uint8_t flag = 0 , i;
	if(iterator > 255)
	{
		return SAVING_FAILED;
	}
	else
	{		
        static uint32_t sequenceNumber = 1; 
        strcpy(server_side_transactions[iterator].cardHolderData.cardHolderName , transData->cardHolderData.cardHolderName);
    	strcpy(server_side_transactions[iterator].cardHolderData.primaryAccountNumber , transData->cardHolderData.primaryAccountNumber);
	
		server_side_transactions[iterator].terminalData.transAmount = transData->terminalData.transAmount;
		server_side_transactions[iterator].terminalData.transactionDate[0] = transData->terminalData.transactionDate[0];
		server_side_transactions[iterator].terminalData.transactionDate[1] = transData->terminalData.transactionDate[1];
        
        server_side_transactions[iterator].state = transData->state;
        server_side_transactions[iterator].transactionSequenceNumber = sequenceNumber;
        sequenceNumber++;
        iterator++;
        return OKAY; 		
	}	
}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
 	uint8_t flag = 0 , i;
    for(i = 0 ; i < sizeof(server_side_accounts) ; i++)
	{
		if(server_side_transactions[i].transactionSequenceNumber == transactionSequenceNumber)
		{
			return TRANSACTION_NOT_FOUND;
		}
		else
		{
			return OKAY;
		}
	}
}