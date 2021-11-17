#include <stdio.h>
#include <stdlib.h>

#include "flags.h"
#include "branding.h"
#include "category.h"
#include "product.h"

#include "libstr.h"


int main()
{
    struct CategoryList *pCategories = NULL;
    //ProductList  *pProducts   = NULL;
    InitConsole();

    pCategories = ReadCategoryFile(CATEGORY_FILE);
    //pProducts   = ReadProductFile(PRODUCT_FILE, pCategories);

    DrawLogo(COMPANY_NAME, BRAND_LOGO_FILE);

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
