#include <stdio.h>
#include <stdlib.h>

#include "library/settings.h"
#include "library/console.h"
#include "library/libstr.h"
#include "library/menu.h"

#include "branding.h"
#include "product.h"

void ValidateSettings(void);//declaration of the validate settings function
void MainMenu(void);//

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
    ResetSalesTotals();//sales.h
    LoadSettings();//settings.h
    ValidateSettings();//main.c
    InitConsole(GetSetting("Company Name"));//console.h

    UserMenu();//user.h

    ClearConsole();
    DrawCopyright();//branding.h

    return 0;
}

void ValidateSettings(void)//Checks to see if setting exists and adds setting if not found(38-105)
{
    int iChanges = 0;//Sets iChanges to 0
    if(!IsSetting("Logo File"))//Checks for Logo File setting(settings.h)
    {
        AddSetting("Logo File",    "resource/logo.txt");//Adds setting if not found(settings.h)
        iChanges++;//Saves Changes
    }

    if(!IsSetting("Company Name"))//Checks for Company name in setting(settings.h)
    {
        AddSetting("Company Name", "Pretty Big Pickle Company");//Adds setting if not found
        iChanges++;//Saves changes
    }

    if(!IsSetting("Product File"))//Checks for Product File in setting(settings.h)
    {
        AddSetting("Product File", "products.txt");//Adds setting if not found
        iChanges++;//Saves changes
    }

    if(!IsSetting("Currency"))//Checks for Currency in setting(settings.h)
    {
        AddSettingChar("Currency",'$');//Adds setting if not found
        iChanges++;//Saves changes
    }

    if(!IsSetting("Restaurant Tax Rate"))//Checks for Restaurant Tax Rate in setting(settings.h)
    {
        AddSettingFloat("Restaurant Tax Rate", 0.0509);//sets tax rate in settings(settings.h)
        iChanges++;//Saves changes
    }

    if(!IsSetting("Sales Tax Rate"))//Checks for Sales Tax Rate in settings(settings.h)
    {
        AddSettingFloat("Sales Tax Rate", 0.0635);//sets sales tax rate in settings(settings.h)
        iChanges++;//Saves changes
    }

    if(!IsSetting("Employee Discount"))//Checks for Employee Discount in settings(settings.h)
    {
        AddSettingFloat("Employee Discount", 0.05);//Sets employee discount
        iChanges++;//Saves changes
    }

    if(!IsSetting("Military Discount"))//Checks for Military Discount in settings(settings.h)
    {
        AddSettingFloat("Military Discount", 0.10);//Adds military discount to settings(settings.h)
        iChanges++;//Saves changes
    }

    if(!IsSetting("Loyalty Discount"))//Checks for loyalty discount in setting(settings.h)
    {
        AddSettingFloat("Loyalty Discount", 0.10);//Adds and sets default loyalty discount
        iChanges++;//Saves changes
    }

    if(!IsSetting("Karen Surcharge"))//Checks for extra handling in setting(settings.h)
    {
        AddSettingFloat("Karen Surcharge", -0.20);//Adds and sets the default "Karen" charge
        iChanges++;//Saves changes
    }

    if(iChanges)//Checks to see if changes were made
    {
        SaveSettings();//Saves all the changes if any were made
    }
}
