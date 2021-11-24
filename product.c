#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "flags.h"
#include "category.h"
#include "product.h"

#include "library/libstr.h"
#include "library/menu.h"

#define SINGLE_MARGIN 50;

/*
 * Prep a ProductList for use
 */
void InitializeProductList(ProductList *pProductList)
{
	if(!pProductList) return;

	pProductList->pSandwiches = NULL;
	pProductList->pSides      = NULL;
	pProductList->pBeverages  = NULL;
	pProductList->pCoupons    = NULL;
}

/*
 * File I/O
 */
void LoadProducts(ProductList *pProductList, char *sFileName)
{
	FILE    *pF;
	Product *pTmp;

	if(!pProductList) return;

/*	pF = fopen(sFileName, "r");
	if(pF)
	{
		// XXXX
	}
	else
*/	{
		pTmp = AddProduct(pProductList, "Hamburger", SANDWICH);
		AddProductVariant(pTmp, "Single", 2.29);
		AddProductVariant(pTmp, "Double", 2.89);
		AddProductVariant(pTmp, "Triple", 3.49);

		pTmp = AddProduct(pProductList, "Cheeseburger", SANDWICH);
		AddProductVariant(pTmp, "Single", 2.69);
		AddProductVariant(pTmp, "Double", 3.09);
		AddProductVariant(pTmp, "Triple", 3.79);

		pTmp = AddProduct(pProductList, "Bacon Cheeseburger", SANDWICH);
		AddProductVariant(pTmp, "Single", 3.19);
		AddProductVariant(pTmp, "Double", 3.59);
		AddProductVariant(pTmp, "Triple", 4.29);

		pTmp = AddProduct(pProductList, "Gardenburger", SANDWICH);
		AddProductVariant(pTmp, "Single", 2.89);
		AddProductVariant(pTmp, "Double", 3.49);
		AddProductVariant(pTmp, "Triple", 4.09);

		pTmp = AddProduct(pProductList, "French Fries", SIDE);
		AddProductVariant(pTmp, "Small",  1.19);
		AddProductVariant(pTmp, "Medium", 1.49);
		AddProductVariant(pTmp, "Large",  1.79);

		pTmp = AddProduct(pProductList, "Sweet Potato Fries", SIDE);
		AddProductVariant(pTmp, "Small",  1.29);
		AddProductVariant(pTmp, "Medium", 1.59);
		AddProductVariant(pTmp, "Large",  1.89);

		pTmp = AddProduct(pProductList, "Onion Rings", SIDE);
		AddProductVariant(pTmp, "Small",  1.39);
		AddProductVariant(pTmp, "Medium", 1.79);
		AddProductVariant(pTmp, "Large",  2.19);

		pTmp = AddProduct(pProductList, "Tater Tots", SIDE);
		AddProductVariant(pTmp, "Small",  1.29);
		AddProductVariant(pTmp, "Medium", 1.59);
		AddProductVariant(pTmp, "Large",  1.89);

		pTmp = AddProduct(pProductList, "Soda", BEVERAGE);
		AddProductVariant(pTmp, "Small",  2.09);
		AddProductVariant(pTmp, "Medium", 2.49);
		AddProductVariant(pTmp, "Large",  2.89);

		pTmp = AddProduct(pProductList, "Vanilla Milkshake", BEVERAGE);
		AddProductVariant(pTmp, "Small",  3.19);
		AddProductVariant(pTmp, "Medium", 3.89);
		AddProductVariant(pTmp, "Large",  4.59);

		pTmp = AddProduct(pProductList, "Chocolate Milkshake", BEVERAGE);
		AddProductVariant(pTmp, "Small",  3.19);
		AddProductVariant(pTmp, "Medium", 3.89);
		AddProductVariant(pTmp, "Large",  4.59);

		pTmp = AddProduct(pProductList, "Coffee", BEVERAGE);
		AddProductVariant(pTmp, "Small",  1.09);
		AddProductVariant(pTmp, "Medium", 1.39);
		AddProductVariant(pTmp, "Large",  1.69);
	}
}

void SaveProducts(ProductList *pProductList, char *sFileName)
{
	if(!pProductList) return;

	// XXXX
}

/*
 * List tidying
 */
void SortProducts(ProductList *pProductList)
{
	if(!pProductList) return;

	// XXXX
}

/*
 * Basic menu printing functions
 */
void DrawMenu        (ProductList *pProductList, ProductType eType)
{
	Product        *pCurP;
	ProductVariant *pCurV;

	if(!pProductList) return;

	switch(eType)
	{
	case SANDWICH:
		printf("%*s%-50s  %-7s\n", SINGLE_MARGIN, "", "SANDWICHES", "PRICE");
		pCurP = pProductList->pSandwiches;
		break;
	case SIDE:
		printf("%*s%-50s  %-7s\n", SINGLE_MARGIN, "", "SIDES", "PRICE");
		pCurP = pProductList->pSides;
		break;
	case BEVERAGE:
		printf("%*s%-50s  %-7s\n", SINGLE_MARGIN, "", "BEVERGES", "PRICE");
		pCurP = pProductList->pBeverages;
		break;
	case COUPON:
		printf("%*s%-50s  %-7s\n", SINGLE_MARGIN, "", "COUPONS", "VALUE");
		pCurP = pProductList->pCoupons;
		break;
	default:
	}
	printf("%*s%-50s  %-7s\n", SINGLE_MARGIN, "", "--------------------", "-------")
	for( ; pCurP; pCurP = pCurP->pNext)
	{
		printf("%*s%-50s\n", SINGLE_MARGIN, "", pCurP->sName);
		for(pCurV = pCurP->pVariants; pCurV; pCurV = pCurV->pNext)
		{
			printf("%*s    %-46s  $3.2f\n", SINGLE_MARGIN, "", pCurV->sName, pCurV->fPrice);
		}
	}
}

void DrawSandwichMenu(ProductList *pProductList)
{
	if(!pProductList) return;

	DrawMenu(pProductList, SANDWICH);
}

void DrawSideMenu    (ProductList *pProductList)
{
	if(!pProductList) return;

	DrawMenu(pProductList, SIDE);
}

void DrawBeverageMenu(ProductList *pProductList)
{
	if(!pProductList) return;

	DrawMenu(pProductList, BEVERAGE);
}

void DrawCouponMenu  (ProductList *pProductList)
{
	if(!pProductList) return;

	DrawMenu(pProductList, COUPON);
}

/*
 * Main functions for interracting with program
 */
void DrawFullMenu    (ProductList *pProductList)
{
	if(!pProductList) return;

	// XXXX
}

ProductType     QueryProductType   (void)
{
	Menu myMenu;

	InitializeMenu(&myMenu, "", "Choose a product category:", 50, 4, MENU_STYLE_NUMERIC);
	AddMenuItem(&myMenu, "Sandwich", SANDWICH);
	AddMenuItem(&myMenu, "Side"    , SIDE);
	AddMenuItem(&myMenu, "Beverage", BEVERAGE);

	return QueryMenu(&myMenu);
}

Product        *QueryProductByType (ProductList *pProductList, ProductType eType)
{
	if(!pProductList) return;

	// XXXX
}

ProductVariant *QueryProductVariant(Product *pProduct)
{
	if(!pProductList) return;

	// XXXX
}

/*
 * Product counts
 */
int GetProductCount (ProductList *pProductList)
{
	if(!pProductList) return 0;

	return GetSandwichCount(pProductList) + GetSideCount(pProductList) + GetBeverageCount(pProductList);
}

int GetProductTypeCount(ProductList *pProductList, ProductType eType)
{
	int iCount = 0;
	Product *pTmp;

	if(!pProductList) return;

	switch(eType)
	{
	case SANDWICH:
		pTmp = pProductList->pSandwiches;
		break;
	case SIDE:
		pTmp = pProductList->pSides;
		break;
	case BEVERAGE:
		pTmp = pProductList->pBeverages;
		break;
	case COUPON:
		pTmp = pProductList->pCoupons;
		break;
	default:
		return 0;
	}

	for( ; pTmp; pTmp = pTmp->pNext)
		iCount++;

	return iCount;
}

int GetSandwichCount(ProductList *pProductList)
{
	return GetProductTypeCount(pProductList, SANDWICH);
}

int GetSideCount    (ProductList *pProductList)
{
	return GetProductTypeCount(pProductList, SIDE);
}

int GetBeverageCount(ProductList *pProductList)
{
	return GetProductTypeCount(pProductList, BEVERAGE);
}

int GetCouponCount  (ProductList *pProductList)
{
	return GetProductTypeCount(pProductList, COUPON);
}

/*
 * Data Management Private Utility Functions
 */
void FreeProduct(Product *pProduct)
{
	pProductVariants *pRip;

	if(!pProduct) return;

	while(pProduct->pVariants)
	{
		pRip = pProduct->pVariants;
		pProduct->pVariants = pProduct->pVariants->pNext;
		free(pRip->sName);
		free(pRip);
	}
	free(pProduct);
}

/*
 * Add Data
 */
Product *AddProduct       (ProductList *pProductList, char *sName, ProductType eType)
{
	Product *pCur;

	if(!pProductList) return;

	if(pCur = FindProduct(pProductList, sName))
	{
		if(pCur->eType != eType)
			ChangeProductType(pCur, eType);
		return pCur;
	}

	switch(eType)
	{
	case SANDWICH:
		if(!pProductList->pSandwiches)
		{
			pProductList->pSandwiches = malloc(sizeof(Product));
			pCur = pProductList->pSandwiches;
		}
		else
		{
			for(pCur = pProductList->pSandwiches; pCur->pNext; pCur = pCur->pNext)
				;
			pCur->pNext = malloc(sizeof(Product));
			pCur = pCur->pNext;
		}
		break;
	case SIDE:
		if(!pProductList->pSides)
		{
			pProductList->pSides = malloc(sizeof(Product));
			pCur = pProductList->pSides;
		}
		else
		{
			for(pCur = pProductList->pSides; pCur->pNext; pCur = pCur->pNext)
				;
			pCur->pNext = malloc(sizeof(Product));
			pCur = pCur->pNext;
		}
		break;
	case BEVERAGE:
		if(!pProductList->pBeverages)
		{
			pProductList->pBeverages = malloc(sizeof(Product));
			pCur = pProductList->pBeverages;
		}
		else
		{
			for(pCur = pProductList->pBeverages; pCur->pNext; pCur = pCur->pNext)
				;
			pCur->pNext = malloc(sizeof(Product));
			pCur = pCur->pNext;
		}
		break;
	case COUPON:
		if(!pProductList->pCoupons)
		{
			pProductList->pCoupons = malloc(sizeof(Product));
			pCur = pProductList->pCoupons;
		}
		else
		{
			for(pCur = pProductList->pCoupons; pCur->pNext; pCur = pCur->pNext)
				;
			pCur->pNext = malloc(sizeof(Product));
			pCur = pCur->pNext;
		}
		break;
	default:
		return 0;
	}
	pCur->sName = malloc(strlen(sName) + 1);
	strcpy(pCur->sName, sName);
	pCur->eType     = eType;
	pCur->pVariants = NULL;
	pCur->pNext     = NULL;
	pCur->pParent   = pProductList;
}

void     AddProductVariant(Product *pProduct, char *sName, float fPrice)
{
	ProductVariant *pCur;

	if(!pProduct) return;

	if(pCur = FindProductVariant(pProduct, sName))
	{
		pCur->fPrice = fPrice;
		return;
	}

	if(!pProduct->pVariants)
	{
		pProduct->pVariants = malloc(sizeof(ProductVariant));
		pCur = pCur->pVariants;
	}
	else
	{
		for(pCur = pProduct->pVariants; pCur->pNext; pCur = pCur->pNext)
			;
		pCur->pNext = malloc(sizeof(ProductVariant));
		pCur = pCur->pNext;
	}
	pCur->sName = malloc(strlen(sName) + 1);
	strcpy(pCur->sName, sName);
	pCur->fPrice  = fPrice;
	pCur->pNext   = NULL;
	pCur->pParent = pProduct;
}

/*
 * Modify Products
 */
Product *FindProduct      (ProductList *pProductList, char *sName)
{
	Product *pCur;

	if(!pProductList) return NULL;

	for(pCur = pProductList->pSandwiches; pCur; pCur = pCur->pNext)
	{
		if(strcmp(sName, pCur->sName) == 0)
			return pCur;
	}

	for(pCur = pProductList->pSides; pCur; pCur = pCur->pNext)
	{
		if(strcmp(sName, pCur->sName) == 0)
			return pCur;
	}

	for(pCur = pProductList->pBeverages; pCur; pCur = pCur->pNext)
	{
		if(strcmp(sName, pCur->sName) == 0)
			return pCur;
	}

	for(pCur = pProductList->pCoupons; pCur; pCur = pCur->pNext)
	{
		if(strcmp(sName, pCur->sName) == 0)
			return pCur;
	}

	return NULL;
}

void     RemoveProduct    (Product *pProduct)
{
	Product *pPre;

	if(!pProduct) return;

	switch(pProduct->eType)
	{
	case SANDWICH:
		if(pProduct->pParent->pSandwiches == pProduct)
		{
			pPre = pProduct->pParent->pSandwiches;
			pProduct->pParent->pSandwiches = pPre->pNext;
			FreeProduct(pPre);
			return;
		}
		pPre = pProduct->pParent->pSandwiches;
		break;
	case SIDE:
		if(pProduct->pParent->pSides == pProduct)
		{
			pPre = pProduct->pParent->pSides;
			pProduct->pParent->pSides = pPre->pNext;
			FreeProduct(pPre);
			return;
		}
		pPre = pProduct->pParent->pSides;
		break;
	case BEVERAGE:
		if(pProduct->pParent->pBeverages == pProduct)
		{
			pPre = pProduct->pParent->pBeverages;
			pProduct->pParent->pBeverages = pPre->pNext;
			FreeProduct(pPre);
			return;
		}
		pPre = pProduct->pParent->pBeverages;
		break;
	case COUPON:
		if(pProduct->pParent->pCoupons == pProduct)
		{
			pPre = pProduct->pParent->pCoupons;
			pProduct->pParent->pCoupons = pPre->pNext;
			FreeProduct(pPre);
			return;
		}
		pPre = pProduct->pParent->pCoupons;
		break;
	default:
		return;
	}
	for( ; pPre->pNext != pProduct; pPre = pPre->pNext)
		;
	pPre->pNext = pProduct->pNext;
	FreeProduct(pProduct);
}

void     ChangeProductName(Product *pProduct, char *sName)
{
	if(!pProduct) return;

	free(pProduct->sName);
	pProduct->sName = malloc(strlen(sName) + 1);
	strcpy(pProduct->sName, sName);
}

void     ChangeProductType(Product *pProduct, ProductType eType)
{
	Product        *pNewProduct;
	ProductVariant *pCurVariant;

	if(!pProduct) return;

	if(pProduct->eType == eType) return;

	pNewProduct = AddProduct(pProduct->pParent, "AAAAAABBBBBBCCCCCCDDDDDDEEEEEE", eType);
	ChangeProductName(pNewProduct, pProduct->sName);
	for(pCurVariant = pProduct->pVariants; pCurVariant; pCurVariant = pCurVariant->pNext)
	{
		AddProductVariant(pNewProduct, pCurVariant->sName, pCurVariant->fPrice);
	}
	RemoveProduct(pProduct);
}

/*
 * Modify Product Variants
 */
ProductVariant *FindProductVariant       (Product *pProduct, char *sName)
{
	ProductVariant *pCur;

	if(!pProduct) return;

	for(pCur = pProduct->pVariants; pCur; pCur = pCur->pNext)
	{
		if(strcmp(sName, pCur->sName) == 0)
			return pCur;
	}

	return NULL;
}

void            RemoveProductVariant     (Product *pProductVariant)
{
	ProductVariant *pPre;

	if(!pProductVariant) return;

	if(pProductVariant->pParent->pVariants == pProductVariant)
	{
		pProductVariant->pParent->pVariants = pProductVariant->pNext;
		free(pProductVariant->sName);
		free(pCur);
	}
	else
	{
		for(pPre - pProductVariant->pParent->pVariants; pPre->pNext != pProductVariant; pPre = pPre->pNext)
			;
		pPre->pNext = pCur->pNext;
		free(pPre->sName);
		free(pPre);
	}
}

void            ChangeProductVariantName (ProductVariant *pProductVariant, char *sName)
{
	if(!pProductVariant) return;

	free(pProductVariant->sName);
	pProductVariant->sName = malloc(strlen(sName) + 1);
	strcpy(pProductVariant->sName, sName);
}

void            ChangeProductVariantPrice(ProductVariant *pProductVariant, float fPrice)
{
	if(!pProductVariant) return;

	pProductVariant->fPrice = fPrice;
}
