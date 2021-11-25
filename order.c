#include <stdlib.h>

#include "library/menu.h"
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
    if(!pOrder) return;

    pOrder->pItems = NULL;
}

void DestroyOrder          (Order *pOrder)
{
    OrderItem *pTmp;

    if(!pOrder) return;

    for(pTmp = pOrder->pItems; pTmp; pTmp = pOrder->pItems)
    {
        pOrder->pItems = pTmp->pNext;
        free(pTmp);
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
    char       cCurrency = GetSettingChar("Currency");
    char       buffer[50];
    int        iItemCount = 0;
    OrderItem *pCur;

    if(!pOrder) return;

    DrawCenteredText("-- Current Order --");
    printf("\n");
    printf("%*s%-35s  %-35s  %-7s  %-3s  %-5s%c\n", 10, "", "ITEM", "SIZE", "PRICE", "QTY", "EXT  ", cCurrency);
    printf("%*s%-35s  %-35s  %-7s  %-3s  %-7s\n", 10, "",
           "-----------------------------------", "-----------------------------------", "-------", "---", "-------");
    for(pCur = pOrder->pItems; pCur; pCur = pCur->pNext)
    {
        printf("%*s%-35s  %-35s  %c%6.2f  %3d  %c%6.2f\n",
               10, "",
               pCur->pItem->pParent->sName, pCur->pItem->sName,
               cCurrency, pCur->pItem->fPrice,
               pCur->iQty,
               cCurrency, (pCur->iQty * pCur->pItem->fPrice));
               iItemCount += pCur->iQty;
    }
    printf("%*s%-35s  %-35s  %-7s  %-3s  %-7s\n", 10, "",
           "-----------------------------------", "-----------------------------------", "-------", "---", "-------");
    printf("%*s%35s  %35s  %-7s  %3d  %c%6.2f\n",
           10, "", "", "TOTAL", "", iItemCount, cCurrency, CalculateTotalPrice(pOrder));
    printf("\n");
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

SubProduct *QueryItemFromOrder(Order *pOrder)
{
    Menu       myMenu;
    OrderItem *pCur;
    char       buffer[100];
    char       c, cSelection;

    if(!pOrder) return;

    printf("\n");
    InitializeMenu(&myMenu, "Current Items in the Order", "Choose an item:", 40, 4, MENU_STYLE_ALPHA);

    for(c = 'a', pCur = pOrder->pItems; pCur; c++, pCur = pCur->pNext)
    {
        sprintf(buffer, "%.45s (%.45s)", pCur->pItem->pParent->sName, pCur->pItem->sName);
        AddMenuItem(&myMenu, buffer, c);
    }

    cSelection = QueryMenu(&myMenu);

    for(c = 'a', pCur = pOrder->pItems; c < cSelection; c++, pCur = pCur->pNext)
        ;

    DestroyMenu(&myMenu);

    return pCur->pItem;
}

float CalculateTotalPrice   (Order *pOrder)
{
    float      fTotal = 0.0;
    OrderItem *pCur;

    if(!pOrder) return 0.0;

    for(pCur = pOrder->pItems; pCur; pCur = pCur->pNext)
    {
        fTotal += (pCur->iQty * pCur->pItem->fPrice);
    }

    return fTotal;
}

