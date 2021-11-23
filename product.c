#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "flags.h"
#include "category.h"
#include "product.h"

#include "library/libstr.h"

#define MAX_PRODUCTS 40

int      PRODUCT_COUNT = 0;
Product *PRODUCTS[MAX_PRODUCTS];

void LoadProducts(void)
{
    for(int i = 0; i < MAX_PRODUCTS; i++)
    {
        PRODUCTS[i] = NULL;
    }

	FILE *pF;

	pF = fopen("NoFile.txt", "r");

	if(pF)
	{
		// XXXX
	}
	else
	{
	    AddProduct(CreateProduct("Burger (single)", 1.29));
	    AddProduct(CreateProduct("Burger (double)", 1.49));
	    AddProduct(CreateProduct("Burger (triple)", 1.69));
	    AddProduct(CreateProduct("CheeseBurger (single)", 1.39));
	    AddProduct(CreateProduct("CheeseBurger (double)", 1.59));
	    AddProduct(CreateProduct("CheeseBurger (triple)", 1.79));
	    AddProduct(CreateProduct("VeggieBurger (single)", 9.29));
	    AddProduct(CreateProduct("VeggieBurger (double)", 9.49));
	    AddProduct(CreateProduct("VeggieBurger (triple)", 9.69));
	}
    for(int i = 0; i < MAX_PRODUCTS; i++)
    {
        printf("PRODUCT[%d]: %d\n", i, &PRODUCTS[i]);
    }
}

void SaveProducts(void)
{

}

void SortProductsByName(void)
{

}

void SortProductsByPrice(void)
{

}

int GetProductCount(void)
{
    return PRODUCT_COUNT;
}

Product *GetProduct(int i)
{
    if(i < 0)              { return NULL; }
    if(i >= PRODUCT_COUNT) { return NULL; }

    return PRODUCTS[i];
}

void AddProduct(Product *p)
{
    if(PRODUCT_COUNT >= MAX_PRODUCTS) { return; }
    PRODUCTS[PRODUCT_COUNT++] = p;
}

void RemoveProduct(int i)
{
    // XXXX
}

void ReplaceProduct(int i, Product *p)
{
    if(i < 0)              { return; }
    if(i >= PRODUCT_COUNT) { return; }

    DeleteProduct(PRODUCTS[i]);
    PRODUCTS[i] = p;
}

void UpdateProductName(int i, char *sName)
{

}

void UpdateProductPrice(int i, float fPrice)
{

}

Product *CreateProduct(char *sName, float fPrice)
{
    Product *p = malloc(sizeof(Product));
    p->sName = malloc(sizeof(sName));
    strcpy(p->sName, sName);
    p->fPrice = fPrice;
    return p;
}

void DeleteProduct(Product *p)
{

}


/*
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
/**/
