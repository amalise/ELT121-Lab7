#ifndef INC_ORDER_H
#define INC_ORDER_H

#include "product.h"

typedef struct s_OrderItem OrderItem;
typedef struct s_Order Order;

struct s_OrderItem
{
    SubProduct *pItem;
    int         iQty;
    OrderItem  *pNext;
};

struct s_Order
{
    OrderItem *pItems;
};

void  InitializeOrder    (Order *pOrder);

void  DrawOrder          (Order *pOrder);

void  AddItemToOrder     (Order *pOrder, SubProduct *pItem, int iQty);
void  RemoveItemFromOrder(Order *pOrder, SubProduct *pItem, int iQty);
void  ModifyItemQty      (Order *pOrder, SubProduct *pItem, int iQty);
void  DeleteItemFromOrder(Order *pOrder, SubProduct *pItem);

void  ClearOrder         (Order *pOrder);

float CalculateTotalPrice(Order *pOrder);

#endif // INC_ORDER_H
