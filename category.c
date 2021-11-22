#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "flags.h"
#include "category.h"

#include "libstr.h"

#define BUFFER_LENGTH 255

/*
struct CategoryList *ReadCategoryFile(const char *sFileName)
{
	FILE *pFile;
	char buffer[BUFFER_LENGTH];
	struct CategoryList *pCategories = NULL;
	struct CategoryList *pTmp;

	pFile = fopen(sFileName, "r");

	if(pFile)
	{
		// XXXX

	}
	else
	{
		pTmp = malloc(sizeof(struct CategoryList));
		pTmp->pItem = malloc(sizeof(struct Category));
		pTmp->pItem->sName = malloc(sizeof(char) * 20);
		strcpy(pTmp->pItem->sName, "All Items");
		pTmp->pItem->iOrder = 1;
		pTmp->pNext = pCategories;
		pCategories = pTmp;

		WriteCategoryFile(pCategories, sFileName);
	}
	return pCategories;
}

void WriteCategoryFile(struct CategoryList *pCategories, const char *sFileName)
{
	// XXXX
}

void CategorySort(struct CategoryList *pCategories)
{
	// XXXX
}

void FreeCategoryList(struct CategoryList *pCategories)
{
	struct CategoryList *pTmp;

	while(pCategories != NULL)
	{
		pTmp = pCategories;
		pCategories = pCategories->pNext;
		if(pTmp->pItem != NULL)
		{
			if(pTmp->pItem->sName != NULL)
			{
				free(pTmp->pItem->sName);
			}
			free(pTmp->pItem);
		}
		free(pTmp);
	}
}
/**/
