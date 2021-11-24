#ifndef INC_PRODUCT_H
#define INC_PRODUCT_H

typedef enum e_ProductType ProductType;
enum e_ProductType {SANDWICH, SIDE, BEVERAGE, COUPON};

typedef struct s_SubProduct  SubProduct;
typedef struct s_Product     Product;
typedef struct s_ProductList ProductList;

struct s_SubProduct
{
	char       *sName;
	float       fPrice;
	// List variables
	SubProduct *pNext;
	Product    *pParent;
};

struct s_Product
{
	char        *sName;
	ProductType  eType;
	SubProduct  *pSubProducts;
	// List variables
	Product     *pNext;
	ProductList *pParent;
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
 * Main functions for interacting with program
 */
void         DrawFullMenu    (ProductList *pProductList); // DOES NOT DISPLAY COUPONS
ProductType  QueryProductType(void);
Product     *QueryProduct    (ProductList *pProductList, ProductType eType);
SubProduct  *QuerySubProduct (Product *pProduct);

/*
 * Get counts
 */
int GetProductCount   (ProductList *pProductList); // DOES NOT COUNT COUPONS
int GetSandwichCount  (ProductList *pProductList);
int GetSideCount      (ProductList *pProductList);
int GetBeverageCount  (ProductList *pProductList);
int GetCouponCount    (ProductList *pProductList);
int GetSubProductCount(Product *pProduct);

/*
 * Add Data
 */
Product *AddProduct   (ProductList *pProductList, char *sName, ProductType eType);
void     AddSubProduct(Product *pProduct, char *sName, float fPrice);

/*
 * Work with Products
 */
Product *FindProduct      (ProductList *pProductList, char *sName);
void     RemoveProduct    (Product *pProduct);
void     ChangeProductName(Product *pProduct, char *sName);
void     ChangeProductType(Product *pProduct, ProductType eType);

/*
 * Work with SubProducts
 */
SubProduct *FindSubProduct       (Product *pProduct, char *sName);
void        RemoveSubProduct     (SubProduct *pProduct, char *sName);
void        ChangeSubProductName (SubProduct *pSubProduct, char *sName);
void        ChangeSubProductPrice(SubProduct *pSubProduct, float fPrice);

#endif // INC_PRODUCT_H
