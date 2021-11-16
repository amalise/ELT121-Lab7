#ifndef INC_PRODUCT_H
#define INC_PRODUCT_H

#include "category.h"

struct ProductVariant
{
	char   *sName;
	float   fPrice;
	struct  ProductVariant  *pNext;
};
// typedef struct ProductVarint ProducVariant;

struct Product
{
	char   *sName;
	struct  ProductVariant  *pVariants;
};
// typedef struct Product Product;

struct ProductList
{
	struct Product     *pItem;
	struct ProductList *pNext;
};
// typedef struct ProductList ProductList;

struct ProductList *ReadProductFile(const char *sFileName);
void WriteProductFile(struct ProductList *pProducts, const char *sFileName);
void ProductSort(struct ProductList *pProducts);
void FreeProductList(struct ProductList *pProducts);

#endif // INC_PRODUCT_H
