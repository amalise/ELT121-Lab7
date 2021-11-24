#include <stdlib.h>

#include "product.h"
#include "order.h"

/*
 * Private utility functions
 */
OrderItem *FindOrderItem(Order *pOrder, SubProduct *pItem)
{
    OrderItem *pCur;

    if(!pOrder) return NULL;

    for(pCur = pOrder->pItems; pCur; pCur = pCur->pNext)
    {
        if(pCur->pItem == pItem)
        {
            return pCur;
        }
    }

    return NULL;
 }

void InitializeOrder       (Order *pOrder)
{
    if(pOrder)
    {
        pOrder->pItems = NULL;
    }
}

/*
 * ITEM                       PRICE    QTY   EXT $
 * ---------------------      -------  ---   -------
 * Steak                      $221.20    2   $  4.80
 * Cantalope                             7   $  2.18
 */
void DrawOrder(Order *pOrder)
{
    OrderItem *pCur;

    if(!pOrder) return;

    printf("%*s%-50s  %-7s  %-3s  %-7s\n", 20, "", "ITEM", "PRICE", "QTY", "EXT $");
    printf("%*s%-50s  %-7s  %-3s  %-7s\n", 20, "",
           "----------------------------------------", "-------", "---", "-------");
    for(pCur = pOrder->pItems; pCur; pCur = pCur->pNext)
    {
        printf("%*s%-50s  $%3.2f  %3d  $%3.2f\n", 20, "",
               pCur->pItem->sName, pCur->pItem->fPrice, pCur->iQuantity,
               (pCur->iQuantity * pCur->pItem->fPrice));
    }
    printf("%*s%-50s  %-7s  %-3s  %-7s\n", 20, "",
           "----------------------------------------", "-------", "---", "-------");
    printf("%*s%50s  %-7s  %-3s  $%3.2f\n", 20, "", "TOTAL", "", "",
           CalculateTotalPrice(pOrder));
}

void AddItemToOrder     (Order *pOrder, SubProduct *pItem, int iQty)
{
    ModifyItemQty(pOrder, pItem, iQty);
}

void RemoveItemFromOrder(Order *pOrder, SubProduct *pItem, int iQty)
{
    ModifyItemQty(pOrder, pItem, -1 * iQty);
}

void ModifyItemQty      (Order *pOrder, SubProduct *pItem, int iQty)
{
    OrderItem *pCur;

    if(!pItem) return;

    if(!pOrder) return;

    if(pCur = FindOrderItem(pOrder, pItem))
    {
        if(iQty == 0)
            DeleteItemFromOrder(pOrder, pItem);
        pCur->iQty += iQty;
        if(pCur->iQty == 0)
            DeleteItemFromOrder(pOrder, pItem);
    }
    else if(iQty > 0)
    {
        pCur = malloc(sizeof(OrderItem));
        pCur->pItem    = pItem;
        pCur->iQty     = iQty;
        pCur->pNext    = pOrder->pItems;
        pOrder->pItems = pCur;
    }
}

void DeleteItemFromOrder(Order *pOrder, SubProduct *pItem)
{
    OrderItem *pCur, *pPre;

    if(!pOrder) return;

    if(pCur = FindOrderItem(pOrder, pItem))
    {
        if(pCur == pOrder->pItems)
        {
            pOrder->pItems = pOrder->pItems->pNext;
            free(pCur);
        }
        else
        {
            for(pPre = pOrder->pItems; pPre->pNext != pCur; pPre = pPre->pNext)
                ;
            pPre->pNext = pCur->pNext;
            free(pCur);
        }
    }
}

void ClearOrder            (Order *pOrder)
{
    OrderItem *pTmp;

    if(pOrder)
    {
        for(pTmp = pOrder->pItems; pTmp; pTmp = pOrder->pItems)
        {
            pOrder->pItems = pTmp->pNext;
            free(pTmp);
        }
    }
}

float CalculateTotalPrice   (Order *pOrder)
{
    float fTotal = 0.0;
    OrderItem *pCur;

    if(pOrder)
    {
        for(pCur = pOrder->pItems; pCur; pCur = pCur->pNext)
        {
            fTotal += (pCur->iQty * pCur->pItem->fPrice);
        }
    }
    return fTotal;
}

