#include <stdio.h>
#include <stdlib.h>

#include "library/settings.h"
#include "library/console.h"
#include "library/libstr.h"
#include "library/menu.h"

#include "branding.h"

void SetDefaultSettings(void);
void MainMenu(void);

/*
 * Program Name:   Lab 8
 *
 * Description:    This is a Point of Sale program.
 *
 * Features:       flags.h    - Global preprocessor settings
 *                 settings.h - Run-time settings
 *
 */
int main(void)
{
    LoadSettings();
    if(CountSettings() == 0)
        SetDefaultSettings();

    InitConsole(GetSetting("Company Name"));

    DrawLogo();

    MainMenu();

    DrawCopyright();

    return 0;
}

void SetDefaultSettings(void)
{
    AddSetting("Logo File",    "resource/logo.txt");
    AddSetting("Company Name", "Pretty Big Pickle Company");

    SaveSettings();
}

void MainMenu(void)
{
    Menu *myMenu = malloc(sizeof(Menu));

    InitializeMenu(myMenu, "Main Menu\n---------", "Selection:", 10, 5, MENU_STYLE_NUMERIC);
    AddMenuItem  (myMenu, "Square",   1);
    AddMenuItem  (myMenu, "Triangle", 2);
    AddMenuItem  (myMenu, "Circle",   3);

    int i = DrawMenu(myMenu);

    printf("\n\nMenu selection: %i\n", i);


    // XXXX

}
