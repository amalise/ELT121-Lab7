#include <stdio.h>
#include <windows.h>

#include "console.h"

/*
 * Global variables which record console parameters
 */
int CONSOLE_WIDTH = 0;
int CONSOLE_HEIGHT = 0;

/*
 * Because even when forced to be standards compliant, Microsoft has to be special about it.
 *
 * https://superuser.com/questions/413073/windows-console-with-ansi-colors-handling
 */
void FixWindows(void)
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

void SetColor(char *sFormat)
{
	printf("%s", sFormat);
}

void SetColors(char *sFG, char *sBG)
{
	printf("%s%s", sFG, sBG);
}

void ColorReset(void)
{
    printf("%s", COLOR_RESET);
}

/*
 * Text formatting functions
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
