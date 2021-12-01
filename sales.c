#include <stdio.h>
#include <stdlib.h>

#include "library/console.h"
#include "library/settings.h"
#include "library/menu.h"
#include "branding.h"
#include "user.h"
#include "product.h"
#include "order.h"

#define MENU_MARGIN 50

/* User input to obtain quantity of subproduct */

int QueryQuantity(SubProduct *pItem)
{
    int qty = -1;

    char buffer[100];
    sprintf(buffer, "%.35s (%.35s)", pItem->pParent->sName, pItem->sName);

    printf("\n%*sHow many %s would you like? ", MENU_MARGIN - 15, "", buffer);
    while(qty < 0)
    {
        fflush(stdin);
        scanf("%i", &qty);
        if(qty < 0)
        {
            printf("\n%*s%sYou need to order non-imaginary food.%s\n%*sPlease enter a positive quantity (0 to cancel): ",
                   MENU_MARGIN - 15, "", FG_B_RED, COLOR_RESET,
                   MENU_MARGIN - 15, "");
        }
    }

    return qty;
}

void SalesMenu(void)
{
    ProductList  myProductList;
    Order        myOrder;
    Menu         mySalesMenu;
    Menu         myAdjustmentMenu;
    int          iSelection;
    char         cResponse;
    char         cCurrency = GetSettingChar("Currency");

    ProductType  eProductType;
    Product     *pProduct;
    SubProduct  *pItem;
    int          iQty;
    float        fManagerAdjust;
    float        fTotalBalance, fRemainingBalance, fTenderedCash;

    // Initialize Product Database
    InitializeProductList(&myProductList);
    LoadProducts(&myProductList, GetSetting("Product File"));

    InitializeOrder(&myOrder); // Create blank order

    InitializeMenu(&myAdjustmentMenu,
                   "Price Adjustments",
                   "Select an adjustment:",
                   50, 4, MENU_STYLE_NUMERIC);
    AddMenuItem(&myAdjustmentMenu, "Employee Discount", 1);
    AddMenuItem(&myAdjustmentMenu, "Military Discount", 2);
    AddMenuItem(&myAdjustmentMenu, "Favorite Customer", 3);
    AddMenuItem(&myAdjustmentMenu, "Karen Surcharge",   4);
//    AddMenuItem(&myAdjustmentMenu, "Manager Override",  5);
//    AddMenuItem(&myAdjustmentMenu, "Manager Discount",  6);

    // Take menu action
    do
    {
        ClearConsole();

        // Display Current Order
        DrawOrder(&myOrder);
        DrawTotals(&myOrder);

     // Draw sales menu
        InitializeMenu(&mySalesMenu,
                       "SALES MENU",
                       "Selection:",
                       50, 4, MENU_STYLE_NUMERIC);
        AddMenuItem(&mySalesMenu, "Add item to order",      1);
        if(CountItemsInOrder(&myOrder) > 0)
        {
            AddMenuItem(&mySalesMenu, "Remove item from order", 2);
            AddMenuItem(&mySalesMenu, "Cancel order",           3);
            AddMenuItem(&mySalesMenu, "Finish and pay",         4);
        }
        AddMenuItem(&mySalesMenu, "Exit", 9);

        iSelection = QueryMenu(&mySalesMenu);
        DestroyMyMenu(&mySalesMenu);

        switch(iSelection)
        {
        case 1: // add item to order
            ClearConsole(); DrawFullMenu(&myProductList);
            if((eProductType = QueryProductType())                               == -1)   continue;
            ClearConsole(); DrawFullMenu(&myProductList);
            if((pProduct     = QueryProductByType(&myProductList, eProductType)) == NULL) continue;
            ClearConsole(); DrawFullMenu(&myProductList);
            if((pItem        = QuerySubProduct(pProduct))                        == NULL) continue;
            ClearConsole(); DrawFullMenu(&myProductList);
            if((iQty         = QueryQuantity(pItem))                             < 1)     continue;
            AddItemToOrder(&myOrder, pItem, iQty);
            break;
        case 2: // remove item from order
            ClearConsole();
            if((pItem        = QueryItemFromOrder(&myOrder))                     == NULL) continue;
            DeleteItemFromOrder(&myOrder, pItem);
            break;
        case 3: // cancel order
            DestroyOrder(&myOrder);
            InitializeOrder(&myOrder);
            break;
        case 4: // finish and pay

/*  Checks for coupon in product list, retrieves coupon from list,
    adds it to order and registers that quantity ordered   */

            if(GetCouponCount(&myProductList))
            {
                ClearConsole(); DrawOrder(&myOrder); DrawTotals(&myOrder);
                printf("\n\n");
                cResponse = QueryYesNo("Does the customer have a coupon?");
                if(cResponse == 'y')
                {
                    pProduct  = QueryProductByType(&myProductList, COUPON);
                    if(GetSubProductCount(pProduct) > 1)
                        pItem = QuerySubProduct(pProduct);
                    else
                        pItem = pProduct->pSubProducts;
                    AddItemToOrder(&myOrder, pItem, 1);
                }
            }

/* Checks for adjustments and applies setting for discount or fee */

            ClearConsole(); DrawOrder(&myOrder); DrawTotals(&myOrder);
            printf("\n\n");
            cResponse = QueryYesNo("Are there any discounts to add?");
            if(cResponse == 'y')
            {
                iSelection = QueryMenuWithCancel(&myAdjustmentMenu);
                switch(iSelection)
                {
                case -1:
                    RemoveCouponsFromOrder(&myOrder);
                    continue;
                case 1: // employee discount
                    AddAdjustmentToOrder(&myOrder, "Employee Discount", GetSettingFloat("Employee Discount"));
                    break;
                case 2: // military discount
                    AddAdjustmentToOrder(&myOrder, "Military Discount", GetSettingFloat("Military Discount"));
                    break;
                case 3: // Favorite Customer
                    AddAdjustmentToOrder(&myOrder, "Loyalty Discount", GetSettingFloat("Loyalty Discount"));
                    break;
                case 4: // Karen Tax
                    AddAdjustmentToOrder(&myOrder, "Karen Surcharge", GetSettingFloat("Karen Surcharge"));
                    break;
                case 5: // manager override
                    // XXXX Manager login
                    fManagerAdjust = QueryFloat("How much should the total be reduced?");
                    AddOverrideToOrder(&myOrder, "Manager Override", fManagerAdjust);
                    break;
                case 6: // manager discount
                    // XXXX Manager login
                    fManagerAdjust = QueryFloat("What discount rate should be applied?");
                    AddAdjustmentToOrder(&myOrder, "Manager Discount", fManagerAdjust);
                    break;
                }
            }

/*  Clear the console, redraws order to display updated totals, requests value from user to calculate change,
    records the order, and then refreshes new order */

            fRemainingBalance = fTotalBalance = CalculateTotal(&myOrder);
            while(fRemainingBalance > 0)
            {
                ClearConsole(); DrawOrder(&myOrder); DrawTotals(&myOrder);
                printf("\n\n");
                if(fRemainingBalance < fTotalBalance)
                {
                    printf("%*s%35s  %35s  %-7s  %3s  %c%6.2f\n",
                           10, "", "", "TENDERED PAYMENT", "", "-", cCurrency, fTotalBalance - fRemainingBalance);
                    printf("%*s%35s  %35s  %-7s  %3s  %c%6.2f\n",
                           10, "", "", "REMAINING BALANCE", "", "", cCurrency, fRemainingBalance);
                }
                printf("\n");
                fTenderedCash = QueryFloat("How much currency did the customer give you (-1 to go back)?");
                if(fTenderedCash < 0) break;
                fRemainingBalance -= fTenderedCash;
            }
            if(fTenderedCash < 0)
            {
                RemoveCouponsFromOrder(&myOrder);
                RemoveAdjustmentsFromOrder(&myOrder);
                continue;
            }
            printf("\n\n%*sCustomer's change: %c %6.2f\n\n", MENU_MARGIN, "", cCurrency, 0 - fRemainingBalance);
            DrawCenteredText("Press any key to continue.");
            getch();
            AddToSalesTotals(CalculateTotal(&myOrder), CalculateTax(&myOrder));
            RecordOrder(&myOrder);
            DestroyOrder(&myOrder);
            InitializeOrder(&myOrder);
            break;
        case 9:
            return;
            break;
        }
    }while(1);

    DestroyOrder      (&myOrder);
    DestroyProductList(&myProductList);
    DestroyMyMenu     (&myAdjustmentMenu);
}

float SALES_TOTAL = 0.0; // sets sales total to 0
float TAX_TOTAL   = 0.0; // sets tax total to 0

/* function that rests total sales and tax */

void ResetSalesTotals(void)
{
    SALES_TOTAL = 0.0;
    TAX_TOTAL = 0.0;
}

/* function that displays total sales on screen */

void DrawSalesTotals(void)
{
    char cCurrency = GetSettingChar("Currency");
    printf("\n");
    printf("%*s  Total sales today: %c%8.2f\n", 45, "", cCurrency, SALES_TOTAL);
    printf("%*sTotal tax collected: %c%8.2f\n", 45, "", cCurrency, TAX_TOTAL);
}

/* adds sales and taxes to totals */

void AddToSalesTotals(float fSale, float fTax)
{
    SALES_TOTAL += fSale;
    TAX_TOTAL   += fTax;
}
