#include <stdio.h>

#include "library/settings.h"
#include "library/console.h"
#include "library/settings.h"

#include "flags.h"
#include "branding.h"

#define BUFFER_LENGTH 255

void DrawLogo(void)
{
	FILE *pFile;
	char buffer[BUFFER_LENGTH];

#if FEAT_CUSTOM_LOGO == 1
	pFile = fopen(GetSetting("Logo File"), "r");
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
	if(GetSettingFloat("Sales Tax Rate") > 0)
        DrawCenteredText(buffer);
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
	printf("\n");
	DrawCenteredText("\"A Sandwich with a Pretty Big Pickle In It\"");
	DrawCenteredText("Ryan George");
}
