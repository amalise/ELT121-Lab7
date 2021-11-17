#include <stdio.h>
#include <stdlib.h>

#include "flags.h"
#include "branding.h"
#include "product.h"

int main()
{
    // Initialize our control of the Windows console
    InitConsole();


    DrawLogo();

    DrawCopyright();

    return 0;
}
