#ifndef INC_ORDER_H
#define INC_ORDER_H

#include "product.h"

typedef struct s_OrderItem OrderItem;
typedef struct s_Order Order;

struct s_OrderItem
{
    ProductVariant *pItem;
    int             iQuantity;
    OrderItem      *pNext;
};

struct s_Order
{
    OrderItem *pItems;
};

void  InitializeOrder       (Order *pOrder);

void  DrawOrder             (Order *pOrder);

void  AddProductToOrder     (Order *pOrder, Product *pProduct, int iQuantity);
void  RemoveProductFromOrder(Order *pOrder, Product *pProduct, int iQuantity);
void  ModifyProductQuantity (Order *pOrder, Product *pProduct, int iQuantity);
void  DeleteProductFromOrder(Order *pOrder, Product *pProduct);

void  ClearOrder            (Order *pOrder);

float CalculateTotalPrice   (Order *pOrder);

#endif // INC_ORDER_H
