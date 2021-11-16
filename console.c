#include <stdio.h>
#include <windows.h>

#include "flags.h"
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
void InitConsole(void)
{
	/*
	 * Windows console API
	 * 
	 * https://docs.microsoft.com/en-us/windows/console/console-reference
	 */

	// Change window title for custom branding
#if FEAT_CUSTOM_BRAND == 1
	SetConsoleTitle(COMPANY_NAME);
#else
	SetConsoleTitle("Burger Joint");
#endif

	// Change console to full screen
	// https://www.dreamincode.net/forums/topic/22914-make-console-full-screen/
#if OPT_FULLSCREEN == 1
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
#endif

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
