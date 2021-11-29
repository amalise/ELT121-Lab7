#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "library/settings.h"
#include "library/menu.h"
#include "product.h"
#include "order.h"

/*
 * Private utility functions, linked lists for
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
    pOrder->sAdjustmentLabel = NULL;
    pOrder->sOverrideLabel = NULL;
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

void DrawOrder(Order *pOrder)
{
    if(!pOrder) return;

    char       cCurrency = GetSettingChar("Currency");
    char       buffer[50];
    float      fSubTotal, fTax, fTotal;
    OrderItem *pCur;

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
    }

    printf("%*s%-35s  %-35s  %-7s  %-3s  %-7s\n", 10, "",
           "-----------------------------------", "-----------------------------------", "-------", "---", "-------");
}

void DrawTotals(Order *pOrder)
{
    if(!pOrder) return;

    int   iItemCount   = CountItemsInOrder(pOrder);
    char  cCurrency    = GetSettingChar("Currency");
    float fSubTotal    = CalculateSubTotal(pOrder);
    float fAdjSubTotal = CalculateAdjustedSubTotal(pOrder);
    float fTax         = CalculateTax(pOrder);
    float fTotal       = CalculateTotal(pOrder);

    printf("%*s%35s  %35s  %-7s  %3d  %c%6.2f\n",
           10, "", "", "SUB-TOTAL", "", iItemCount, cCurrency, fSubTotal);
    if(pOrder->sOverrideLabel)
    {
        printf("%*s%35s  %35s  %-7s  %3d  %c%6.2f\n",
               10, "", "", pOrder->sOverrideLabel, "", iItemCount, cCurrency, pOrder->fOverride);
    }
    if(pOrder->sAdjustmentLabel)
    {
        printf("%*s%35s  %35s  %-7s  %3d  %c%6.2f\n",
               10, "", "", pOrder->sAdjustmentLabel, "", iItemCount, cCurrency, pOrder->fAdjustment);
    }
    printf("%*s%35s  %35s  %-7s  %3s  %c%6.2f\n",
           10, "", "", "TAX", "", "", cCurrency, fTax);
    printf("%*s%35s  %35s  %-7s  %3s  %c%6.2f\n",
           10, "", "", "TOTAL", "", "", cCurrency, fTotal);
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

int   CountItemsInOrder   (Order *pOrder)
{
    if(!pOrder) return 0;

    int        iCount = 0;
    OrderItem *pCur;

    for(iCount = 0, pCur = pOrder->pItems; pCur; pCur = pCur->pNext)
    {
        iCount += pCur->iQty;
    }

    return iCount;
}

/* Total cost of everything in order list w/out adjustments (subtotal) */

float CalculateSubTotal   (Order *pOrder)
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

/* Price adjustments */


float CalculateAdjustedSubTotal(Order *pOrder)
{
    if(!pOrder) return 0.0;

    float fSubTotal = CalculateSubTotal(pOrder);

    if(pOrder->sOverrideLabel)
        fSubTotal -= pOrder->fOverride;

    if(pOrder->sAdjustmentLabel)
        fSubTotal *= (1.0 - pOrder->fAdjustment);

    return fSubTotal;
}

/* Tax calculation */


float CalculateTax(Order *pOrder)
{
    if(!pOrder) return 0.0;

    return CalculateAdjustedSubTotal(pOrder) * GetSettingFloat("Restaurant Tax Rate");
}

/* Total cost of everything in order list w/adjustments (subtotal) */


float CalculateTotal(Order *pOrder)
{
    if(!pOrder) return 0.0;

    return CalculateAdjustedSubTotal(pOrder) + CalculateTax(pOrder);
}

/* adds adjustment to order */

void AddAdjustmentToOrder(Order *pOrder, char *sLabel, float fAdjustment)
{
    if(!pOrder) return;

    if(pOrder->sAdjustmentLabel) free(pOrder->sAdjustmentLabel);
    pOrder->sAdjustmentLabel = malloc(strlen(sLabel) + 1);
    strcpy(pOrder->sAdjustmentLabel, sLabel);
    pOrder->fAdjustment = fAdjustment;
}

/* adds manual override to order */

void AddOverrideToOrder(Order *pOrder, char *sLabel, float fOverride)
{
    if(!pOrder) return;

    if(pOrder->sOverrideLabel) free(pOrder->sOverrideLabel);
    pOrder->sOverrideLabel = malloc(strlen(sLabel) + 1);
    strcpy(pOrder->sOverrideLabel, sLabel);
    pOrder->fOverride = fOverride;
}

/* Outputs to log file */

void RecordOrder(Order *pOrder)
{
    static int   iSaleCount     = 1; // sets static value for each time it's called and records the next order
    static char *ReceiptLogFile = NULL; // line by line adds new order to list w/out reprinting the header
    static char *SummaryLogFile = NULL; // saves order total and adds new order to list w/out reprinting the header

    char  buffer[20];
    char  cCurrency = GetSettingChar("Currency"); // settings.txt

/* Asks local machine for time */

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    FILE *fTape;
    FILE *fBook;

    OrderItem *pCur;

    if(!ReceiptLogFile) // logs time as file name
    {
        sprintf(buffer, "register-%d-%02d-%02d.log", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        ReceiptLogFile = malloc(strlen(buffer) + 1);
        strcpy(ReceiptLogFile, buffer);
        fTape = fopen(ReceiptLogFile, "w");
        fprintf(fTape, "%-5s  %-35s  %-35s  %-7s  %-3s  %-5s%c\n",
                "ORD #", "ITEM", "SIZE", "PRICE", "QTY", "EXT ", cCurrency);
        fprintf(fTape, "%-5s  %-35s  %-35s  %-7s  %-3s  %-7s\n",
                "-----", "-----------------------------------", "-----------------------------------",
                "-------", "---", "-------");
        fclose(fTape);

/* linked list interactions for printing items */
    }
    fTape = fopen(ReceiptLogFile, "a");
    for(pCur = pOrder->pItems; pCur; pCur = pCur->pNext)
    {
        fprintf(fTape, "%5d  %-35s  %-35s  %c%6.2f  %-3d  %c%6.2f\n",
                iSaleCount, pCur->pItem->pParent->sName, pCur->pItem->sName,
                cCurrency, pCur->pItem->fPrice,
                pCur->iQty,
                cCurrency, (pCur->iQty * pCur->pItem->fPrice));
    }
    if(pOrder->sOverrideLabel)
    {
        fprintf(fTape, "%5d  %-35s  %-35s  %7s  %-3s  %c%6.2f\n",
                iSaleCount, "", pOrder->sOverrideLabel, "", "",
                cCurrency, pOrder->fOverride);
    }
    if(pOrder->sAdjustmentLabel)
    {
        fprintf(fTape, "%5d  %-35s  %-35s  %7s  %-3s  %0.4f\%\n",
                iSaleCount, "", pOrder->sAdjustmentLabel, "", "",
                pOrder->fAdjustment);
    }
    fclose(fTape);

    if(!SummaryLogFile)
    {
        sprintf(buffer, "summary-%d-%02d-%02d.log", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        SummaryLogFile = malloc(strlen(buffer) + 1);
        strcpy(SummaryLogFile, buffer);
        fBook = fopen(SummaryLogFile, "w");
        fprintf(fBook, "%-5s  %-5s  %-10s  %-10s  %-10s  %-10s\n",
                "ORD #", "ITEMS", "SUB-TOTAL", "ADJUST", "TOTAL", "TAX");
        fprintf(fBook, "%-5s  %-5s  %-10s  %-10s  %-10s  %-10s\n",
                "-----", "-----", "----------", "----------", "----------", "----------");
        fclose(fBook);
    }
    fBook = fopen(SummaryLogFile, "a");
    fprintf(fBook, "%5d  %5d  %c%9.2f  %c%9.2f  %c%9.2f  %c%9.2f\n",
            iSaleCount, CountItemsInOrder(pOrder), CalculateSubTotal(pOrder),
            (CalculateAdjustedSubTotal(pOrder) - CalculateSubTotal(pOrder)),
            CalculateTax(pOrder));
    fclose(fBook);

    iSaleCount++;
}
