#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "libstr.h"
#include "console.h"

#include "menu.h"

/*Linked list for the menu system*/
void InitializeMenu(Menu *pMenu, char *sHeader, char *sPrompt, int iMargin, int iIndent, int iStyle)
{
    if(!pMenu) return;

    pMenu->sHeader = NULL;
    pMenu->sPrompt = NULL;
    pMenu->pItems  = NULL;
    pMenu->iMargin = iMargin;
    pMenu->iIndent = iIndent;
    pMenu->iStyle  = iStyle;

    SetMenuHeader(pMenu, sHeader);
    SetMenuPrompt(pMenu, sPrompt);
}

void DestroyMyMenu (Menu *pMenu)
{
    if(!pMenu) return;

    MenuItem *pCur;

    if(pMenu->sHeader) free(pMenu->sHeader);
    if(pMenu->sPrompt) free(pMenu->sPrompt);

    for(pCur = pMenu->pItems; pCur; pCur = pMenu->pItems)
    {
        pMenu->pItems = pCur->pNext;
        if(pCur->sItem) free(pCur->sItem);
        if(pCur->sKeys) free(pCur->sKeys);
        free(pCur);
    }
}

void SetMenuHeader(Menu *pMenu, const char *sHeader)
{
	if(!pMenu) return;

    if(pMenu->sHeader)
        free(pMenu->sHeader);
    pMenu->sHeader = malloc(strlen(sHeader) + 1);
    strcpy(pMenu->sHeader, sHeader);
}

void SetMenuPrompt(Menu *pMenu, const char *sPrompt)
{
	if(!pMenu) return;

    if(pMenu->sPrompt)
        free(pMenu->sPrompt);
    pMenu->sPrompt = malloc(strlen(sPrompt) + 1);
    strcpy(pMenu->sPrompt, sPrompt);
}

void SetMenuMargin(Menu *pMenu, const int iMargin)
{
	if(pMenu) pMenu->iMargin = iMargin;
}

void SetMenuIndent(Menu *pMenu, const int iIndent)
{
	if(pMenu) pMenu->iIndent = iIndent;
}

void SetMenuStyle (Menu *pMenu, const int iStyle)
{
	if(pMenu) pMenu->iStyle = iStyle;
}

void AddMenuItem   (Menu *pMenu, const char *sItem, const int iReturn)
{
   AddMenuItemKey(pMenu, sItem, "", iReturn);
}

void AddMenuItemKey(Menu *pMenu, const char *sItem, const char *sKeys, const int iReturn)
{
    if(!pMenu) return;

	MenuItem *pCur;

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
    pCur->sItem = malloc(strlen(sItem) + 1);
    pCur->sKeys = malloc(strlen(sKeys) + 1);
    strcpy(pCur->sItem, sItem);
    strcpy(pCur->sKeys, sKeys);
    pCur->iReturn = iReturn;
    pCur->pNext = NULL;
}

void DrawBaseMenu    (Menu *pMenu)
{
    if(!pMenu) return ;

   	int       i;
	MenuItem *pCur;

    if(pMenu->sHeader)
    {
        printf("%*s%s\n", pMenu->iMargin, "", pMenu->sHeader);
    }

    for(pCur = pMenu->pItems, i = 1; pCur; pCur = pCur->pNext, i++)
    {
        printf("%*s", pMenu->iMargin + pMenu->iIndent, "");
        switch(pMenu->iStyle)
        {
        case MENU_STYLE_NONE:
            break;
        case MENU_STYLE_ALPHA:
            printf("%c)  ", 'A' + i - 1);
            break;
        case MENU_STYLE_NUMERIC:
        default:
            printf("%i)  ", i);
            break;
        }
        printf("%s\n", pCur->sItem);
    }
}

int QueryMenu    (Menu *pMenu)
{
    if(!pMenu) return -1;

	int       i;
	char      c;
	MenuItem *pCur;

	DrawBaseMenu(pMenu);

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

int QueryMenuWithCancel(Menu *pMenu)
{
    if(!pMenu) return -1;

    if(pMenu->iStyle == MENU_STYLE_NONE) return QueryMenu(pMenu);

	int       i;
	char      c;
	MenuItem *pCur;

	DrawBaseMenu(pMenu);

    printf("%*s", pMenu->iMargin + pMenu->iIndent, "");
    switch(pMenu->iStyle)
    {
    case MENU_STYLE_NUMERIC:
        printf("0)  Cancel\n");
        break;
    case MENU_STYLE_ALPHA:
    default:
        printf("Z)  Cancel\n");
        break;
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

        if((pMenu->iStyle == MENU_STYLE_NUMERIC) && (isdigit(c)) && (c == '0'))
        {
            if(c == '0') return -1;
        }

        if((pMenu->iStyle == MENU_STYLE_ALPHA) && (isalpha(c)))
        {
            if((c == 'z') || (c == 'Z')) return -1;
        }

        if(c == 27)
        {
            return -1;
        }
    }
}
