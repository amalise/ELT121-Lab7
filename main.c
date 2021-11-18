#include <stdio.h>
#include <stdlib.h>

#include "flags.h"
#include "branding.h"
#include "product.h"

int main()
{
    Product *myProduct;
    // Initialize our control of the Windows console
    InitConsole();
    LoadProducts();
    DrawLogo();


    for(int i = 0; i < GetProductCount(); i++)
    {
        myProduct = GetProduct(i);
        printf("Product Name: %25s\t\t$%5.2f\n", myProduct->sName, myProduct->fPrice);
    }

    myProduct = GetProduct(6);
    printf("\n\nProduct Name: %25s\t\t$%5.2f\n", myProduct->sName, myProduct->fPrice);


    SaveProducts();
    DrawCopyright();

    return 0;
}
