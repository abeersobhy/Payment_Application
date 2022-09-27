#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "std_types.h"
#include "card.h"
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    printf("Enter Card Name : ");
    gets(cardData->cardHolderName);
	if((cardData->cardHolderName == NULL) || (strlen(cardData->cardHolderName) < 14 ) || (strlen(cardData->cardHolderName) > 20 ))
	{
		return WRONG_NAME;
	}
	else
	{
		return OK;
	}
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	printf("Enter Expiry date in the form of 05/24 : ");
	gets(cardData->cardExpirationDate);
	if((cardData->cardExpirationDate == NULL) || (strlen(cardData->cardExpirationDate) != 5))
	{
		return WRONG_EXP_DATE;
	}
	else
	{
		char *month = strtok(cardData->cardExpirationDate ,"/");
		int8_t *year = &cardData->cardExpirationDate[3];
	    cardData->cardExpirationDate[0] = atoi(month);
		cardData->cardExpirationDate[1] = atoi(year);
		return OK;
	}
     	
}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
	printf("Enter PAN Function : ");
    gets(cardData->primaryAccountNumber);
    if((cardData->primaryAccountNumber == NULL) || ((strlen(cardData->primaryAccountNumber) < 16) || (strlen(cardData->primaryAccountNumber) > 19)))
	{
		return WRONG_PAN;
	}
	else
	{
		return OK;
	}	
}