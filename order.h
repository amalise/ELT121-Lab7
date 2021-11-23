#ifndef INC_ORDER_H
#define INC_ORDER_H

#include "product.h"

struct OrderItem
{
    Product *pProduct;
    int      iQuantity;
    struct OrderItem *pNext;
};
typedef struct OrderItem OrderItem;

struct Order
{
    OrderItem *pItems;
};
typedef struct Order Order;

void InitializeOrder       (Order *pOrder);

void DrawOrder             (Order *pOrder);

void AddProductToOrder     (Order *pOrder, Product *pProduct, int iQuantity);
void RemoveProductFromOrder(Order *pOrder, Product *pProduct, int iQuantity);
void ModifyProductQuantity (Order *pOrder, Product *pProduct, int iQuantity);
void DeleteProductFromOrder(Order *pOrder, Product *pProduct);

void ClearOrder            (Order *pOrder);

float CalculateTotalPrice  (Order *pOrder);

#endif // INC_ORDER_H
