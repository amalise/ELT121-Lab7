#ifndef INC_PRODUCT_H
#define INC_PRODUCT_H

typedef enum e_ProductType ProductType;
enum e_ProductType {SANDWICH, SIDE, BEVERAGE, COUPON};

typedef struct s_ProductVariant ProductVariant;
typedef struct s_Product        Product;
typedef struct s_ProductList    ProductList;

struct s_ProductVariant
{
	char           *sName;
	float           fPrice;
	// List variables
	ProductVariant *pNext;
	Product        *pParent;
};

struct s_Product
{
	char           *sName;
	ProductType     eType;
	ProductVariant *pVariants;
	// List variables
	Product        *pNext;
	ProductList    *pParent;
};

struct s_ProductList
{
	Product *pSandwiches;
	Product *pSides;
	Product *pBeverages;
	Product *pCoupons;
};

/*
 * Prep a ProductList for use
 */
void InitializeProductList(ProductList *pProductList);

/*
 * File I/O
 */
void LoadProducts(ProductList *pProductList, char *sFileName);
void SaveProducts(ProductList *pProductList, char *sFileName);

/*
 * List tidying
 */
void SortProducts(ProductList *pProductList);

/*
 * Basic menu printing functions
 */
void DrawMenu        (ProductList *pProductList, ProductType eType);
void DrawSandwichMenu(ProductList *pProductList);
void DrawSideMenu    (ProductList *pProductList);
void DrawBeverageMenu(ProductList *pProductList);
void DrawCouponMenu  (ProductList *pProductList);

/*
 * Main functions for interracting with program
 */
void DrawFullMenu    (ProductList *pProductList); // DOES NOT DISPLAY COUPONS
ProductType     QueryProductType   (void);
Product        *QueryProduct       (ProductList *pProductList, ProductType eType);
ProductVariant *QueryProductVariant(Product *pProduct);

/*
 * Product counts
 */
int GetProductCount (ProductList *pProductList); // DOES NOT COUNT COUPONS
int GetSandwichCount(ProductList *pProductList);
int GetSideCount    (ProductList *pProductList);
int GetBeverageCount(ProductList *pProductList);
int GetCouponCount  (ProductList *pProductList);

/*
 * Add Data
 */
Product *AddProduct       (ProductList *pProductList, char *sName, ProductType eType);
void     AddProductVariant(Product *pProduct, char *sName, float fPrice);

/*
 * Modify Products
 */
Product *FindProduct      (ProductList *pProductList, char *sName);
void     RemoveProduct    (Product *pProduct);
void     ChangeProductName(Product *pProduct, char *sName);
void     ChangeProductType(Product *pProduct, ProductType eType);

/*
 * Modify Product Variants
 */
ProductVariant *FindProductVariant       (Product *pProduct, char *sName);
void            RemoveProductVariant     (Product *pProduct, char *sName);
void            ChangeProductVariantName (ProductVariant *pProductVariant, char *sName);
void            ChangeProductVariantPrice(ProductVariant *pProductVariant, float fPrice);

#endif // INC_PRODUCT_H
