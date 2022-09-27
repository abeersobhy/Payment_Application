#include <stdio.h>
#include <string.h>
#include "std_types.h"
#include "app.h"
#include "card.h"
#include "terminal.h"
#include "server.h"

ST_cardData_t cardData;
ST_terminalData_t termData;
ST_transaction_t transData;
ST_accountsDB_t accountDB;

EN_cardError_t cardError;
EN_terminalError_t terminalError;
EN_transStat_t transState;
EN_serverError_t serverError;

void startApp()
{
	cardError = getCardHolderName(&cardData);
	if(cardError == WRONG_NAME)
	{
		printf("Wrong name !!\n");
	}
	else if(cardError == OK)
	{
		cardError = getCardExpiryDate(&cardData); 
		if(cardError == WRONG_EXP_DATE)
		{
			printf("Wrong expiry date !!\n");
		}
		else if(cardError == OK)
		{
			cardError = getCardPAN(&cardData); 
			if(cardError == WRONG_PAN)
			{
				printf("Wrong PAN !!\n");
			}
			else if(cardError == OK)
			{
				terminalError = getTransactionDate(&termData); 
				if(terminalError == WRONG_DATE)
				{
					printf("Transaction Date Error !!\n");
				}
				else if(terminalError == OKK)
				{
					terminalError = isCardExpired(cardData , termData); 
					if(terminalError == EXPIRED_CARD)
					{
						printf("Card Expired !!\n");
					}
					else if(terminalError == OKK)
					{
						terminalError = getTransactionAmount(&termData); /////////////////////////////////////
						if(terminalError == INVALID_AMOUNT)
						{
							printf("Invalid transaction amount !!\n");
						}
						else if(terminalError == OKK)
						{
							terminalError = setMaxAmount(&termData);
							if(terminalError == INVALID_MAX_AMOUNT)
							{
								printf("Invalid max amount");
							}
							else if(terminalError == OKK)
							{
								terminalError = isBelowMaxAmount(&termData);  
								if(terminalError == EXCEED_MAX_AMOUNT)
								{
			    					printf("This amount exceeds the maximum amount \n");
								}
								else if(terminalError == OKK)
								{
									serverError = isValidAccount(&cardData);									
									if(serverError == ACCOUNT_NOT_FOUND)
									{
										printf("Declined stolen card\n");
									}
									else if(serverError == OKAY)
									{
										serverError = isAmountAvailable(&termData); 	
										if(serverError == LOW_BALANCE)
										{
											printf("low balnace\n");
										}
										else if(serverError == OKAY)
										{
											transState = recieveTransactionData(&transData);
											if(transState == DECLINED_STOLEN_CARD)
											{
												printf("Declined stolen card !!\n");
											}
								    		else if(transState == DECLINED_INSUFFECIENT_FUND)
											{
												printf("declined insuffecient fund !!\n");
											}
											else if(transState == INTERNAL_SERVER_ERROR)
											{
												printf("Internal server error !!\n");
											}
				    						else if(transState == APPROVED)
											{     
			     								serverError = saveTransaction(&transData);
												if(serverError == SAVING_FAILED)
												{
													printf("SAVING_FAILED !!\n");
						    					}
												else if(serverError == OKAY)
												{
													printf("Transaction Saved\n");				
								    			}
											}  
										}										
									}
								}   
							}	
					    }
				    }
			    }
		    }
									
		}
	}

}