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
//    AddMenuItem(&myMenu, "Logout",       3);
    AddMenuItem(&myMenu, "Exit Program", 9);

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
            AdjustTaxes();
            break;
        case 9:
            return;
            break;
        }
    }while(1);
}

void AdjustTaxRate(char *sSetting, char *sRateName)
{
    float fValue;
    char  cConfirm;

    printf("\n\nThe current %s tax rate is: %0.6f\n", sRateName, GetSettingFloat(sSetting));
    do
    {
        printf("     Enter new %s tax rate: ", sRateName);
        fflush(stdin);
        scanf("%f", &fValue);
        cConfirm = 'y';
        if(fValue < 0)
        {
            printf("%sThis is a CREDIT. Please check with your government and try again!%s\n", FG_B_RED, COLOR_RESET);
            cConfirm = 'n';
        }
        if(fValue == 0)
        {
            printf("Do you really not charge any taxes? ");
            do
            {
                fflush(stdin);
                cConfirm = tolower(getch(stdin));
            }while((cConfirm != 'y') && (cConfirm != 'n'));
            printf("%c\n", cConfirm);
        }
        if(fValue > 0.50)
        {
            printf("Those aren't tax rates, those are crimes. Is this legit? ");
            do
            {
                fflush(stdin);
                cConfirm = tolower(getch(stdin));
            }while((cConfirm != 'y') && (cConfirm != 'n'));
            printf("%c\n", cConfirm);
        }
    }while(cConfirm == 'n');

    ChangeSettingFloat(sSetting, fValue);
}

void AdjustTaxes(void)
{
    AdjustTaxRate("Restaurant Tax Rate", "restaurant");
    AdjustTaxRate("Sales Tax Rate",      "sales");
//    SaveSettings();
}
