#include <stdio.h>
#include <stdlib.h>

#include "library/console.h"
#include "library/settings.h"
#include "library/menu.h"
#include "branding.h"
#include "user.h"

void UserMenu(void)
{
    int iUserSelection;

    // while NOT logged in
    // - Get Username
    // - Get Password

    // Draw user menu
    Menu myMenu;

    InitializeMenu(&myMenu,
                   "USER MENU",
                   "Selection:",
                   50, 4, MENU_STYLE_NUMERIC);

    AddMenuItem(&myMenu, "Start Sale",   1);
    AddMenuItem(&myMenu, "Adjust Tax",   2);
    AddMenuItem(&myMenu, "Exit Program", 9);
//    AddMenuItem(&myMenu, "Logout",       3);

    // Take menu action
    do
    {
        ClearConsole();
        DrawLogo();
        iUserSelection = QueryMenu(&myMenu);
        switch(iUserSelection)
        {
        case 1:
            SalesMenu();
            break;
        case 2:
            break;
        case 9:
            break;
        }
    }while(iUserSelection != 9);
}
