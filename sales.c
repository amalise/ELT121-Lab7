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

int GetQuantity(SubProduct *pItem)
{
    int qty = 0;

    char buffer[100];
    sprintf(buffer, "%.45s (%.45s)", pItem->pParent->sName, pItem->sName);

    printf("\n%*sHow many %s do you want? ", MENU_MARGIN, "", buffer);
    while(qty < 1)
    {
        fflush(stdin);
        scanf("%i", &qty);
        if(qty < 1)
        {
            printf("\n%*s%sYou need to order non-imaginary food.%s\n%*sPlease enter a positive quantity: ",
                   MENU_MARGIN, "", FG_B_RED, COLOR_RESET,
                   MENU_MARGIN, "");
        }
    }

    return qty;
}

void SalesMenu(void)
{
    Order        myOrder;
    ProductList  myProductList;

    ProductType  eProductType;
    Product     *pProduct;
    SubProduct  *pItem;
    int          iQty, iDiscountType;
    char         cResponse;
    float        fManagerAdjust, fTenderedCash;

    Menu         mySalesMenu, myAdjustmentMenu;


    InitializeOrder(&myOrder); // Create blank order

    // Initialize Product Database
    InitializeProductList(&myProductList);
    LoadProducts(&myProductList, GetSetting("Product File"));

    // Draw sales menu
    InitializeMenu(&mySalesMenu,
                   "SALES MENU",
                   "Selection:",
                   50, 4, MENU_STYLE_NUMERIC);
    AddMenuItem(&mySalesMenu, "Add item to order",      1);
    AddMenuItem(&mySalesMenu, "Remove item from order", 2);
    AddMenuItem(&mySalesMenu, "Cancel order",           3);
    AddMenuItem(&mySalesMenu, "Finish and Pay",         4);
    AddMenuItem(&mySalesMenu, "Exit",                   9);

    InitializeMenu(&myAdjustmentMenu,
                   "Price Adjustments",
                   "Select an adjustment:",
                   50, 4, MENU_STYLE_NUMERIC);
    AddMenuItem(&myAdjustmentMenu, "Employee Discount", 1);
    AddMenuItem(&myAdjustmentMenu, "Military Discount", 2);
    AddMenuItem(&myAdjustmentMenu, "Favorite Customer", 3);
    AddMenuItem(&myAdjustmentMenu, "Extra Handling",    4);
    AddMenuItem(&myAdjustmentMenu, "Manager Override",  8);
    AddMenuItem(&myAdjustmentMenu, "Manager Discount",  9);

    // Take menu action
    do
    {
        ClearConsole();

        // Display Current Order
        DrawOrder(&myOrder);
        DrawTotals(&myOrder);

        switch(QueryMenu(&mySalesMenu))
        {
        case 1: // add item to order
            DrawFullMenu(&myProductList);
            eProductType = QueryProductType();
            pProduct     = QueryProductByType(&myProductList, eProductType);
            pItem        = QuerySubProduct(pProduct);
            iQty         = GetQuantity(pItem);
            AddItemToOrder(&myOrder, pItem, iQty);
            break;
        case 2: // remove item from order
            DeleteItemFromOrder(&myOrder, QueryItemFromOrder(&myOrder));
            break;
        case 3: // cancel crder
            DestroyOrder(&myOrder);
            InitializeOrder(&myOrder);
            break;
        case 4: // finish and pay
            printf("\n");

/*  Checks for coupon in product list, retrieves coupon from list,
    adds it to order and registers that quantity ordered   */

            if(GetCouponCount(&myProductList))
            {
                cResponse = QueryYesNo("Does the customer have a coupon?");
                printf("%c\n", cResponse);
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

            cResponse = QueryYesNo("Are there any total adjustments?");
            printf("%c\n", cResponse);
            if(cResponse == 'y')
            {
                iDiscountType = QueryMenu(&myAdjustmentMenu);
                switch(iDiscountType)
                {
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
                    AddAdjustmentToOrder(&myOrder, "Extra Handling Fee", GetSettingFloat("Extra Handling"));
                    break;
                case 8: // manager override
                    // XXXX Manager login
                    fManagerAdjust = QueryFloat("How much should the total be reduced?");
                    AddOverrideToOrder(&myOrder, "Manager Override", fManagerAdjust);
                    break;
                case 9: // manager discount
                    // XXXX Manager login
                    fManagerAdjust = QueryFloat("What discount rate should be applied?");
                    AddAdjustmentToOrder(&myOrder, "Manager Discount", fManagerAdjust);
                    break;
                }
            }

/*  Clear the console, redraws order to display updated totals, requests value from user to calculate change,
    records the order, and then refreshes new order */

            ClearConsole();
            DrawOrder(&myOrder);
            DrawTotals(&myOrder);
            fTenderedCash = QueryFloat("How much currency did the customer give you?");
            printf("Customer's change: %c %6.2f", GetSetting("Currency"), fTenderedCash - CalculateTotal(&myOrder));
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
    DestroyMyMenu     (&mySalesMenu);
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
