#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "flags.h"
#include "category.h"
#include "product.h"

#include "libstr.h"

struct ProductList *ReadProductFile(const char *sFileName)
{
	// XXXX
}

void WriteProductFile(struct ProductList *pProducts, const char *sFileName)
{
	// XXXX
}

void ProductSort(struct ProductList *pProducts)
{
	// XXXX
}

void FreeProductList(struct ProductList *pProducts)
{
	struct ProductList *pTmpP;
	struct ProductVariant *pTmpV;

	while(pProducts != NULL)
	{
		pTmpP = pProducts;
		pProducts = pProducts->pNext;
		if(pTmpP->pItem != NULL)
		{
			if(pTmpP->pItem->sName != NULL)
			{
				free(pTmpP->pItem->sName);
			}
			while(pTmpP->pItem->pVariants != NULL)
			{
				pTmpV = pTmpP->pItem->pVariants;
				pTmpP->pItem->pVariants = pTmpP->pItem->pVariants->pNext;
				if(pTmpV->sName != NULL)
				{
					free(pTmpV->sName);
				}
				free(pTmpV);
			}
			free(pTmpP->pItem);
		}
		free(pTmpP);
	}

}
