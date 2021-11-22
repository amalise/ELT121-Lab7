#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "libstr.h"
#include "console.h"

#include "menu.h"

void InitializeMenu(Menu *pMenu,
                    const char *sHeader,
                    const char *sPrompt,
                    const int iMargin,
                    const int iIndent,
                    const int iStyle)
{
    if(pMenu)
    {
        pMenu->sHeader = NULL;
        pMenu->sPrompt = NULL;
        pMenu->pItems  = NULL;
        pMenu->iMargin = iMargin;
        pMenu->iIndent = iIndent;
        pMenu->iStyle  = iStyle;

        SetMenuHeader(pMenu, sHeader);
        SetMenuPrompt(pMenu, sPrompt);
    }
}

void SetMenuHeader(Menu *pMenu, const char *sHeader)
{
	if(pMenu)
	{
		if(pMenu->sHeader)
			free(pMenu->sHeader);
		pMenu->sHeader = malloc(sizeof(sHeader));
		strcpy(pMenu->sHeader, sHeader);
	}
}

void SetMenuPrompt(Menu *pMenu, const char *sPrompt)
{
	if(pMenu)
	{
		if(pMenu->sPrompt)
			free(pMenu->sPrompt);
		pMenu->sPrompt = malloc(sizeof(sPrompt));
		strcpy(pMenu->sPrompt, sPrompt);
	}
}

void SetMenuMargin(Menu *pMenu, const int iMargin)
{
	if(pMenu)
		pMenu->iMargin = iMargin;
}

void SetMenuIndent(Menu *pMenu, const int iIndent)
{
	if(pMenu)
		pMenu->iIndent = iIndent;
}

void SetMenuStyle (Menu *pMenu, const int iStyle)
{
	if(pMenu)
		pMenu->iStyle = iStyle;
}

void AddMenuItem   (Menu *pMenu, const char *sItem, const int iReturn)
{
   AddMenuItemKey(pMenu, sItem, "", iReturn);
}

void AddMenuItemKey(Menu *pMenu, const char *sItem, const char *sKeys, const int iReturn)
{
	MenuItem *pCur;

	if(pMenu)
	{
		if(pMenu->pItems)
		{
			pCur = pMenu->pItems;
			while(pCur->pNext)
				pCur = pCur->pNext;
			pCur->pNext = malloc(sizeof(MenuItem));
			pCur = pCur->pNext;
		}
		else
		{
			pMenu->pItems = malloc(sizeof(MenuItem));
			pCur = pMenu->pItems;
		}
		pCur->sItem = malloc(sizeof(sItem));
		pCur->sKeys = malloc(sizeof(sKeys));
		strcpy(pCur->sItem, sItem);
		strcpy(pCur->sKeys, sKeys);
		pCur->iReturn = iReturn;
		pCur->pNext = NULL;
	}
}

char DrawMenu     (Menu *pMenu)
{
	int       i;
	char      c;
	char     *sTok;
	MenuItem *pCur;

	if(pMenu)
	{
		if(pMenu->sHeader)
		{
		    if(strchr(pMenu->sHeader, '\n'))
            {
                sTok = strtok(pMenu->sHeader, "\n");
                printf("%*s%s\n", pMenu->iMargin, "", sTok);
                while(sTok = strtok(NULL, "\n"))
                {
                    printf("%*s%s\n", pMenu->iMargin, "", sTok);
                }
            }
            else
            {
                printf("%*s%s\n", pMenu->iMargin, "", pMenu->sHeader);
            }
		}
		for(pCur = pMenu->pItems, i = 1; pCur; pCur = pCur->pNext, i++)
        {
		    printf("%*s", pMenu->iMargin + pMenu->iIndent, "");
		    switch(pMenu->iStyle)
		    {
            case MENU_STYLE_NONE:
                break;
            case MENU_STYLE_ALPHA:
                printf("%c)  ", 'A' + i);
                break;
            case MENU_STYLE_NUMERIC:
            default:
                printf("%2i)  ", i);
                break;
		    }
		    printf("%s\n", pCur->sItem);
		}
		printf("%*s%s ", pMenu->iMargin, "", pMenu->sPrompt);

		fflush(stdin);
		for( ; ; )
		{
			c = getch(stdin);
			if((pMenu->iStyle == MENU_STYLE_NUMERIC) && (isdigit(c)) && (c != '0'))
			{
				pCur = pMenu->pItems;
				for(i = 1; (pCur && (i < (c - '0'))); pCur = pCur->pNext, i++)
					;
				if(pCur)
				{
				    printf("%c", c);
					return pCur->iReturn;
				}
			}

			if((pMenu->iStyle == MENU_STYLE_ALPHA) && (isalpha(c)))
			{
				pCur = pMenu->pItems;
				for(i = 'a'; (pCur && (i < tolower(c))); pCur = pCur->pNext, i++)
					;
				if(pCur)
				{
				    printf("%c", c);
					return pCur->iReturn;
				}
			}

			if(pMenu->iStyle == MENU_STYLE_NONE)
			{
                for(pCur = pMenu->pItems; pCur; pCur = pCur->pNext)
                {
                    for(i = 0; i < strlen(pCur->sKeys); i++)
                    {
                        if(c == pCur->sKeys)
                        {
                            printf("%c", c);
                            return pCur->iReturn;
                        }
                    }
                }
			}
		}
	}
}
