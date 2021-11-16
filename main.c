#include <stdio.h>
#include <stdlib.h>

#include "flags.h"
#include "branding.h"
#include "menu.h"


int main()
{
/*
    FILE *fp;
    fp = fopen("MyDataFile.TXT", "r");

    MenuItem myMenuItem[11];
    for(int i = 0; i < 11; i++)
    {
        char *name;
        fscanf(fp, &name);
        myMenuItem[i].myName = name;
        char *var1, *var2, *var3;
        fscanf(fp, "%s", &var1);
        fscanf(fp, "%s", &var2);
        fscanf(fp, "%s", &var3);
        fscanf(fp, "%f %f %f", myMenuItem.myPrices[0], myMenuItem.myPrices[1], myMenuItem.myPrices[2]);
    }
/**/

/*
    cheeseburger
    small
    medium
    large
    1.09 1.29 1.49

    myMenuItem.myName = new *char('Cheeseburger');
    myMenuItem.myPrices = (1.09, 1.29, 1.49);
/**/

    InitConsole();

    DrawLogo();

    // LoadData();
    // MainMenu();

    DrawCopyright();

    return 0;
}

void MainMenu(void)
{
    /*
        Manager Options
        -
        Begin Business Day
        Exit
        - DEBUG (change date for testing)
     */
/*     do
     {
         switch(selection)
         {
         case 'manager':
             // XXXX
             break;
         case 'business day':
             // XXXX
             break;
         case 'exit':
             // XXXX
             break;
         default:
             // XXXX
             EntryError();
         }
     } while(not exit);
*/
}
