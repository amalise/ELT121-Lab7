#include <stdio.h>

#include "library/settings.h"
#include "library/console.h"
#include "library/settings.h"

#include "flags.h"
#include "branding.h"
#include "sales.h"

#define BUFFER_LENGTH 255

/*This series of functions are supported by the .h files and draw the logo of the program*/
void DrawLogo(void)
{
	FILE *pFile; // opens file using settings
	char buffer[BUFFER_LENGTH]; // reads one line a time in the buffer and prints to screen

#if FEAT_CUSTOM_LOGO == 1
	pFile = fopen(GetSetting("Logo File"), "r"); // locates setting for the logo and applies it to the display
#else
	pFile = NULL;
#endif
	if(pFile)
	{
		while(fgets(buffer, BUFFER_LENGTH, pFile)) // reads one line from file, exits loop if no line.
		{
			printf("%s", buffer); // prints buffered string
		}
		fclose(pFile); // closes the file
		printf("\n");
	}
	else
	{
/* Draws header display */
		DrawCenteredText("Welcome to the");
/* flags.h */
#if FEAT_CUSTOM_BRAND == 1
		DrawCenteredText(GetSetting("Company Name"));
#else
		DrawCenteredText("Burger Joint");
#endif
		DrawCenteredText("Point-of-Sale system");
		printf("\n");
	}
	DrawCenteredText("------------------------------");

	sprintf(buffer, "Restaurant Tax Rate: %.5f", GetSettingFloat("Restaurant Tax Rate"));
	if(GetSettingFloat("Restaurant Tax Rate") > 0)
        DrawCenteredText(buffer);
	sprintf(buffer, "Sales Tax Rate: %.5f", GetSettingFloat("Sales Tax Rate"));
	if(GetSettingFloat("Sales Tax Rate") > 0) // checks to see if the sales tax rate is greater than 0
        DrawCenteredText(buffer); // centers displayed string stored in the buffer
	printf("\n\n");
}

void DrawCopyright(void) // Draws the footer
{
	printf("\n\n");
	DrawSalesTotals(); // Displays total sales(sales.h)
	DrawCenteredText("------------------------------"); // Centers text on display(console.h)
	printf("\n");
	DrawCenteredText("COPYRIGHT"); // console.h
	DrawCenteredText("15 November 2021"); // console.h
	printf("\n");
	DrawCenteredText("DEVELOPERS"); // console.h
	DrawCenteredText("Adal Catano, Andrew Knight"); // console.h
	DrawCenteredText("Karl Mariger, Alex Woodley"); // console.h
	printf("\n");
	DrawCenteredText("\"A Sandwich with a Pretty Big Pickle In It\""); // console.h
	DrawCenteredText("Ryan George"); // console.h
}
