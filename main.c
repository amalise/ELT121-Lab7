#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *myName;        // cheeeseburger
    char *myVariants[3]; // small, medium, large
    float myPrices[3];   // $1.09, $1.29, $1.49
} MenuItem;

typedef struct
{
    MenuItem *myItem;
    MenuList *nextItem;
} MenuList;

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
/**/

    myMenuItem.myName = new *char('Cheeseburger');
    myMenuItem.myPrices = (1.09, 1.29, 1.49);


    Menu *FoodMenu;

    DisplayLogo();

    LoadData();

    MainMenu();

    return 0;
}

void DisplayLogo(void)
{
    // XXXX
}

/*
 * Read menu from a file
 */
void LoadData(void)
{
    // XXXX
}

/*
 * Save menu to a file
 */
void WriteData(void)
{

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
     do
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
}
