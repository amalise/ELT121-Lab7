#include <stdio.h>
#include <stdlib.h>

#include "library/settings.h"
#include "library/console.h"
#include "library/libstr.h"
#include "library/menu.h"

#include "branding.h"
#include "product.h"

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

    UserMenu();
//    MainMenu();

    DrawCopyright();

    return 0;
}

void SetDefaultSettings(void)
{
    AddSetting("Logo File",    "resource/logo.txt");
    AddSetting("Company Name", "Pretty Big Pickle Company");
    AddSetting("Product File", "products.txt");

    SaveSettings();
}
