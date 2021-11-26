#include <stdio.h>
#include <stdlib.h>

#include "library/settings.h"
#include "library/console.h"
#include "library/libstr.h"
#include "library/menu.h"

#include "branding.h"
#include "product.h"

void ValidateSettings(void);
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
    ResetSalesTotals();

    LoadSettings();
    ValidateSettings();

    InitConsole(GetSetting("Company Name"));

    UserMenu();

    DrawCopyright();

    return 0;
}

void ValidateSettings(void)
{
    int iChanges = 0;
    if(!IsSetting("Logo File"))
    {
        AddSetting("Logo File",    "resource/logo.txt");
        iChanges++;
    }

    if(!IsSetting("Company Name"))
    {
        AddSetting("Company Name", "Pretty Big Pickle Company");
        iChanges++;
    }

    if(!IsSetting("Product File"))
    {
        AddSetting("Product File", "products.txt");
        iChanges++;
    }

    if(!IsSetting("Currency"))
    {
        AddSettingChar("Currency",'$');
        iChanges++;
    }

    if(!IsSetting("Restaurant Tax Rate"))
    {
        AddSettingFloat("Restaurant Tax Rate", 0.0509);
        iChanges++;
    }

    if(!IsSetting("Sales Tax Rate"))
    {
        AddSettingFloat("Sales Tax Rate", 0.0635);
        iChanges++;
    }

    if(!IsSetting("Employee Discount"))
    {
        AddSettingFloat("Employee Discount", 0.05);
        iChanges++;
    }

    if(!IsSetting("Military Discount"))
    {
        AddSettingFloat("Military Discount", 0.10);
        iChanges++;
    }

    if(!IsSetting("Loyalty Discount"))
    {
        AddSettingFloat("Loyalty Discount", 0.10);
        iChanges++;
    }

    if(!IsSetting("Extra Handling"))
    {
        AddSettingFloat("Extra Handling", -0.20);
        iChanges++;
    }

    if(iChanges)
    {
        SaveSettings();
    }
}
