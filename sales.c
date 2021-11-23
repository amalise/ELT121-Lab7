#include <stdio.h>
#include <stdlib.h>

#include "library/console.h"
#include "library/settings.h"
#include "library/menu.h"
#include "branding.h"
#include "user.h"

void SalesMenu(void)
{
    Menu mySalesMenu;
    int iSaleSelection;

    // Create blank order


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
        DrawLogo();

        iSaleSelection = DrawMenu(&mySalesMenu);
        switch(iSaleSelection)
        {
        case 1:
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
