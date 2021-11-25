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
    int          iQty;

    Menu         mySalesMenu;

    // Create blank order
    InitializeOrder(&myOrder);

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

    // Take menu action
    do
    {
        ClearConsole();

        // Display Current Order
        DrawOrder(&myOrder);

        switch(QueryMenu(&mySalesMenu))
        {
        case 1:
            DrawFullMenu(&myProductList);
            eProductType = QueryProductType();
            pProduct     = QueryProductByType(&myProductList, eProductType);
            pItem        = QuerySubProduct(pProduct);
            iQty         = GetQuantity(pItem);
            AddItemToOrder(&myOrder, pItem, iQty);
            break;
        case 2:
            DeleteItemFromOrder(&myOrder, QueryItemFromOrder(&myOrder));
            break;
        case 3:
            DestroyOrder(&myOrder);
            InitializeOrder(&myOrder);
            break;
        case 4:
//            PayForOrder(&myOrder);
//            RecordOrder(&myOrder);
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
