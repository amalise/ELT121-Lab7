#include <stdlib.h>

#include "product.h"
#include "order.h"

/*
 * Private utility functions
 */
OrderItem *FindProduct(Order *pOrder, Product *pProduct)
{
    OrderItem *pCur;

    if(pOrder)
    {
        for(pCur = pOrder->pItems; pCur; pCur = pCur->pNext)
        {
            if(pCur->pProduct == pProduct)
            {
                return pCur;
            }
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

    if(pOrder)
    {
        printf("%*s%-50s  %-7s  %-3s  %-7s\n", 20, "", "ITEM", "PRICE", "QTY", "EXT $");
        printf("%*s%-50s  %-7s  %-3s  %-7s\n", 20, "",
               "----------------------------------------", "-------", "---", "-------");
        for(pCur = pOrder->pItems; pCur; pCur = pCur->pNext)
        {
            printf("%*s%-50s  $%3.2f  %3d  $%3.2f\n", 20, "",
                   pCur->pProduct->sName, pCur->pProduct->fPrice, pCur->iQuantity,
                   (pCur->iQuantity * pCur->pProduct->fPrice));
        }
        printf("%*s%-50s  %-7s  %-3s  %-7s\n", 20, "",
               "----------------------------------------", "-------", "---", "-------");
        printf("%*s%50s  %-7s  %-3s  $%3.2f\n", 20, "", "TOTAL", "", "",
               CalculateTotalPrice(pOrder));
    }
}

void AddProductToOrder     (Order *pOrder, Product *pProduct, int iQuantity)
{
    ModifyProductQuantity(pOrder, pProduct, iQuantity);
}

void RemoveProductFromOrder(Order *pOrder, Product *pProduct, int iQuantity)
{
    ModifyProductQuantity(pOrder, pProduct, -1 * iQuantity);
}

void ModifyProductQuantity (Order *pOrder, Product *pProduct, int iQuantity)
{
    OrderItem *pCur;

    if(!pProduct)
    {
        return;
    }

    if(pOrder)
    {
        if(pCur = FindProduct(pOrder, pProduct))
        {
            if(iQuantity == 0)
                DeleteProductFromOrder(pOrder, pProduct);
            pCur->iQuantity += iQuantity;
            if(pCur->iQuantity == 0)
                DeleteProductFromOrder(pOrder, pProduct);
        }
        else if(iQuantity > 0)
        {
            pCur = malloc(sizeof(OrderItem));
            pCur->pProduct = pProduct;
            pCur->iQuantity = iQuantity;
            pCur->pNext = pOrder->pItems;
            pOrder->pItems = pCur;
        }
    }
}

void DeleteProductFromOrder(Order *pOrder, Product *pProduct)
{
    OrderItem *pCur, *pPre;

    if(pOrder)
    {
        if(pCur = FindProduct(pOrder, pProduct))
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
            fTotal += (pCur->iQuantity * pCur->pProduct->fPrice);
        }
    }
    return fTotal;
}

