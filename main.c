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
    ResetSalesTotals(); //--------------------Declaration->sales.h(6)/Implementation->sales.c(178)

    LoadSettings();     //--------------------Declaration->library\settings.h(line 25)/Implementation->library\settings.c(49)
    ValidateSettings(); //--------------------Declaration->main.c(12)/Implementation->main.c(39)
    InitConsole(GetSetting("Company Name"));//Declaration->library\console.h(51)/Implementation->library\console.c(17)

    UserMenu();         //--------------------Declaration->user.h(4)/Implementation->user.c(10)

    DrawCopyright();    //--------------------Declaration->branding.h(6)/Implementation->branding.c(54)

    return 0;
}

void ValidateSettings(void)     //--------------------------Filing system for settings(39-106)
{
    int iChanges = 0;           //--------------------------Sets iChanges to 0
    if(!IsSetting("Logo File")) //--------------------------Declaration->library\settings.h(28)/Implementation->library\settings.c(149)
    {
        AddSetting("Logo File",    "resource/logo.txt");//--Declaration->library\settings.h(38)/Implementation->library\settings.c(199)
        iChanges++;             //--------------------------Adds setting to logo.txt
    }

    if(!IsSetting("Company Name"))//------------------------Checks if company name is setting
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
