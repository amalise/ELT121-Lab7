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
    char      *sAdjustmentLabel;
    char      *sOverrideLabel;
    float      fAdjustment;
    float      fOverride;
};

void  InitializeOrder    (Order *pOrder);
void  DestroyOrder       (Order *pOrder);

void  DrawOrder          (Order *pOrder);
void  DrawTotals         (Order *pOrder);

void  AddItemToOrder     (Order *pOrder, SubProduct *pItem, int iQty);
void  RemoveItemFromOrder(Order *pOrder, SubProduct *pItem, int iQty);
void  ModifyItemQty      (Order *pOrder, SubProduct *pItem, int iQty);
void  DeleteItemFromOrder(Order *pOrder, SubProduct *pItem);

SubProduct *QueryItemFromOrder(Order *pOrder);

float CalculateSubTotal(Order *pOrder);
float CalculateAdjustedSubTotal(Order *pOrder);
float CalculateTax(Order *pOrder);
float CalculateTotal(Order *pOrder);

void RecordOrder(Order *pOrder);

#endif // INC_ORDER_H
