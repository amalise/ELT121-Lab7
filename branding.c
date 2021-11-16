#include <stdio.h>

#include "flags.h"
#include "branding.h"
#include "console.h"

#define BUFFER_LENGTH 255

void DrawLogo(void)
{
	FILE *pFile;
	char buffer[BUFFER_LENGTH];

#if FEAT_CUSTOM_LOGO == 1
	pFile = fopen(BRAND_LOGO_FILE, "r");
#else
	pFile = NULL;
#endif
	if(pFile)
	{
		while(fgets(buffer, BUFFER_LENGTH, pFile))
		{
			printf("%s", buffer);
		}
		fclose(pFile);
		printf("\n");
	}
	else
	{
		DrawCenteredText("Welcome to the");
#if FEAT_CUSTOM_BRAND == 1
		DrawCenteredText(COMPANY_NAME);
#else
		DrawCenteredText("Burger Joint");
#endif
		DrawCenteredText("Point-of-Sale sytem");
		printf("\n");
	}
	DrawCenteredText("------------------------------");
	printf("\n\n");
}

void DrawCopyright(void)
{
	printf("\n\n");
	DrawCenteredText("------------------------------");
	printf("\n");
	DrawCenteredText("COPYRIGHT");
	DrawCenteredText("15 November 2021");
	printf("\n");
	DrawCenteredText("DEVELOPERS");
	DrawCenteredText("Adal Catano, Andrew Knight");
	DrawCenteredText("Karl Mariger, Alex Woodley");
}
