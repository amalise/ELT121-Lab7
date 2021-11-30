#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include "console.h"

/*
 * Global variables which record console parameters
 */
int CONSOLE_WIDTH = 0;
int CONSOLE_HEIGHT = 0;

/*
 * Initialize the console, and set some local variables
 */
void InitConsole(char *sWindowTitle)
{
	/*
	 * Windows console API
	 *
	 * https://docs.microsoft.com/en-us/windows/console/console-reference
	 */

	// Change window title for custom branding
	SetConsoleTitle(sWindowTitle);

	// Get console dimensions (the draw functions rely on this info)
	// https://stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	CONSOLE_WIDTH = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	CONSOLE_HEIGHT = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void ClearConsole(void)//Used for refreshing display
{
    system("cls");
}

/*
 * Because even when forced to be standards compliant, Microsoft has to be special about it.
 *
 * https://superuser.com/questions/413073/windows-console-with-ansi-colors-handling
 */
void FixWindows(void)//Allows for console color customization using the ansi library
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(hConsole != INVALID_HANDLE_VALUE)
    {
        DWORD mode = 0;
        if(GetConsoleMode(hConsole, &mode))
        {
            mode |= 0x0004;
            SetConsoleMode(hConsole, mode);
        }
    }
}

/*
 * Access console parameters
 */
int  GetConsoleWidth (void)
{
    return CONSOLE_WIDTH;
}

int  GetConsoleHeight(void)
{
    return CONSOLE_HEIGHT;
}

/*
 * Text format management
 */
void SetColor(char *sFormat)
{
	printf("%s", sFormat);
}

void SetColors(char *sFG, char *sBG)
{
	printf("%s%s", sFG, sBG);
}

void ResetColor(void)
{
    printf("%s", COLOR_RESET);
}

/*
 * Text formatting functions
 */
void DrawCenteredText(char *sText)
{
    if(strlen(sText) >= CONSOLE_WIDTH)
        printf("%s\n", sText);
    else
        printf("%*s%s\n", ((CONSOLE_WIDTH - strlen(sText)) / 2), "", sText);
}

void DrawRightText(char *sText)
{
    if(strlen(sText) >= CONSOLE_WIDTH)
        printf("%s\n", sText);
    else
        printf("%*s%s\n", (CONSOLE_WIDTH - strlen(sText)), "", sText);
}

void DrawCenteredTextBuffer(char *sText, int iWidth)
{
    int i, iBlank; // iBlank = Number of leading spaces

    if(strlen(sText) >= iWidth)
    {
        for(i = 0; i < iWidth; i++)
        {
            printf("%c", sText[i])
        }
    }
    else
    {
        iBlank = (iWidth - strlen(sText)) / 2;
        for(i = 0; i< iWidth; i++)
        {
            if(i < iBlank) printf(" ");
            else if(i < (iBlank + strlen(sText)) printf("%c", sText[iBlank + i]);
            else printf(" ");
        }
    }
}

// User interractions
int   QueryInt  (char *sPrompt)
{
    int i;

    printf("%s ", sPrompt);
    fflush(stdin);
    scanf("%d", &i);
    return i;
}

float QueryFloat(char *sPrompt)
{
    float f;

    printf("%s ", sPrompt);
    fflush(stdin);
    scanf("%f", &f);
    return f;
}

char  QueryYesNo(char *sPrompt)
{
    int c;

    printf("%s y/n: ", sPrompt);
    fflush(stdin);
    do
    {
        c = getch();
        c = tolower(c);
    }while((c != 'y') && (c != 'n'));

    return c;
}
