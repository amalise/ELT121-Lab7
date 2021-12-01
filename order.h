#ifndef INC_ORDER_H
#define INC_ORDER_H

#include "product.h"

typedef struct s_OrderItem OrderItem; // contains item with quantity
typedef struct s_Order Order; // scope of order

struct s_OrderItem // structure for OrderItem
{
    SubProduct *pItem; // Specific item ordered "here"
    int         iQty;
    OrderItem  *pNext; // linked list pointer to next row in invoice
};

struct s_Order//Invoice sheet
{
    OrderItem *pItems;
    char      *sAdjustmentLabel; // percentage based
    char      *sOverrideLabel; // fixed
    float      fAdjustment;
    float      fOverride;
};

void  InitializeOrder    (Order *pOrder); // makes all pointers null if needed
void  DestroyOrder       (Order *pOrder); // any pointers that aren't null are free'd for memory conservation (MemoryGuard Certified)

void  DrawOrder          (Order *pOrder); // live receipt
void  DrawTotals         (Order *pOrder); // displaying total under order, separation of totals and subtotals

void  AddItemToOrder     (Order *pOrder, SubProduct *pItem, int iQty); // linked list management
void  RemoveItemFromOrder(Order *pOrder, SubProduct *pItem, int iQty); // linked list management
void  ModifyItemQty      (Order *pOrder, SubProduct *pItem, int iQty); // linked list management
void  DeleteItemFromOrder(Order *pOrder, SubProduct *pItem);           // linked list management

SubProduct *QueryItemFromOrder(Order *pOrder); // linked list management

int   CountItemsInOrder  (Order *pOrder);

void  RemoveCouponsFromOrder(Order *pOrder);
void  RemoveAdjustmentsFromOrder(Order *pOrder);

float CalculateSubTotal(Order *pOrder);
float CalculateAdjustedSubTotal(Order *pOrder);
float CalculateTax(Order *pOrder);
float CalculateTotal(Order *pOrder);

void AddAdjustmentToOrder(Order *pOrder, char *sLabel, float fAdjustment);
void AddOverrideToOrder(Order *pOrder, char *sLabel, float fOverride);

void RecordOrder(Order *pOrder);

#endif // INC_ORDER_H
