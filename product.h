#ifndef INC_PRODUCT_H
#define INC_PRODUCT_H

struct Product
{
	char   *sName;
	float   fPrice;
};

typedef struct Product Product;


void LoadProducts(void);

void SaveProducts(void);

void SortProductsByName(void);

void SortProductsByPrice(void);

// Returns number of total products
int GetProductCount(void);

// Returns the ith product
Product *GetProduct(int i);

// Add a product to the list
void AddProduct(Product *p);

void RemoveProduct(int i);

void ReplaceProduct(int i, Product *p);

void UpdateProductName(int i, char *sName);

void UpdateProductPrice(int i, float fPrice);

Product *CreateProduct(char *sName, float fPrice);

void DeleteProduct(Product *p);





/*
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
/**/

#endif // INC_PRODUCT_H
