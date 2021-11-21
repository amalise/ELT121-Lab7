#include <stdio.h>
#include <stdlib.h>

#include "flags.h"
#include "lib/console.h"

void MainMenu(void);

/*
 *
 */
void main(void)
{
    InitConsole();           // Initialize the UI

    MainMenu();              // Main Program Loop

    DrawCopyright();         // Credits on Exit
}

void MainMenu(void)
{

}
