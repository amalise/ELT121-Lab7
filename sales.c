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

Product *SelectProduct(void)
{
    int i;
    Menu myMenu;
    Product *pTmp;

    InitializeMenu(&myMenu, "", "Please select an item:", MENU_MARGIN, 0, MENU_STYLE_NUMERIC);

    for(i = 0; i < GetProductCount(); i++)
    {
        pTmp = GetProduct(i);
        AddMenuItem(&myMenu, pTmp->sName, i);
    }

    i = DrawMenu(&myMenu);

    return GetProduct(i);
}

int GetQuantity(Product *pProduct)
{
    int qty;

    printf("\n%*sHow many %s do you want? ", MENU_MARGIN, "", pProduct->sName);
    fflush(stdin);
    sscanf("%i", &qty);
    while(qty < 1)
    {
        if(qty < 1)
        {
            printf("\n%*s%sYou need to order non-imaginary food.%s\n%*sPlease enter a positive quantity: ",
                   MENU_MARGIN, "", FG_B_RED, COLOR_RESET,
                   MENU_MARGIN, "");
        }
        fflush(stdin);
        sscanf("%i", &qty);
    }

    return qty;
}

void SalesMenu(void)
{
    Order    myOrder;
    Product *pProduct;
    int      iQuantity;

    Menu     mySalesMenu;
    int      iSaleSelection;

    // Create blank order
    InitializeOrder(&myOrder);

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
        ConsoleClear();

        // Display Current Order
//        DrawOrder(&myOrder);

        iSaleSelection = DrawMenu(&mySalesMenu);
        switch(iSaleSelection)
        {
        case 1:
            pProduct  = SelectProduct();
            iQuantity = GetQuantity(pProduct);
            AddProductToOrder(&myOrder, pProduct, iQuantity);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 9:
            break;
        }
    }while(iSaleSelection != 9);
}
