#ifndef INC_CONSOLE_H
#define INC_CONSOLE_H

#include <windows.h>

/*
 * ANSI color codes, for altering text output. Requires an ANSI compatible terminal,
 * which is disabled by default in Windows. Call FixWindows() before using these.
 *
 * https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
 */
#define FG_BLACK   "\x1b[30m"
#define FG_RED     "\033[31m"
#define FG_GREEN   "\x1b[32m"
#define FG_YELLOW  "\x1b[33m"
#define FG_BLUE    "\x1b[34m"
#define FG_MAGENTA "\x1b[35m"
#define FG_CYAN    "\x1b[36m"
#define FG_WHITE   "\x1b[37m"

#define FG_B_BLACK   "\x1b[90m"
#define FG_B_RED     "\033[91m"
#define FG_B_GREEN   "\x1b[92m"
#define FG_B_YELLOW  "\x1b[93m"
#define FG_B_BLUE    "\x1b[94m"
#define FG_B_MAGENTA "\x1b[95m"
#define FG_B_CYAN    "\x1b[96m"
#define FG_B_WHITE   "\x1b[97m"

#define BG_BLACK   "\x1b[40m"
#define BG_RED     "\x1b[41m"
#define BG_GREEN   "\x1b[42m"
#define BG_YELLOW  "\x1b[43m"
#define BG_BLUE    "\x1b[44m"
#define BG_MAGENTA "\x1b[45m"
#define BG_CYAN    "\x1b[46m"
#define BG_WHITE   "\x1b[47m"

#define BG_B_BLACK   "\x1b[100m"
#define BG_B_RED     "\x1b[101m"
#define BG_B_GREEN   "\x1b[102m"
#define BG_B_YELLOW  "\x1b[103m"
#define BG_B_BLUE    "\x1b[104m"
#define BG_B_MAGENTA "\x1b[105m"
#define BG_B_CYAN    "\x1b[106m"
#define BG_B_WHITE   "\x1b[107m"

#define COLOR_RESET "\x1b[0m"

// Set Windows console to be ANSI compliant
void FixWindows(void);

// Set color (FG and BG can be set separately, or together)
void SetColor(char *sFormat);
void SetColors(char *sFG, char *sBG);

// Reset text to default
void ColorReset(void);

// Determine console size, for text positioning
void InitConsole(void);

// Position text horizontally in the window
void DrawCenteredText(char *sText);
void DrawRightText(char *sText);

/*
 * XXXX
 * Need to add functions for absolute text positioning
 */

#endif // INC_CONSOLE_H
