#ifndef INC_MENU_H
#define INC_MENU_H

#define MENU_STYLE_NONE    0
#define MENU_STYLE_ALPHA   1
#define MENU_STYLE_NUMERIC 2

struct MenuItem
{
	char  *sItem;
	char  *sKeys;
	int    iReturn;
	struct MenuItem *pNext;
};
typedef struct MenuItem MenuItem;

struct Menu
{
	char     *sHeader;
	char     *sPrompt;
	int       iMargin;
	int       iIndent;
	int       iStyle;
	MenuItem *pItems;
};
typedef struct Menu Menu;

void InitializeMenu(Menu *pMenu,
                    const char *sHeader,
                    const char *sPrompt,
                    const int   iMargin,
                    const int   iIndent,
                    const int   iStyle);

void SetMenuHeader (Menu *pMenu, const char *sHeader);
void SetMenuPrompt (Menu *pMenu, const char *sPrompt);
void SetMenuMargin (Menu *pMenu, const int iMargin);
void SetMenuStyle  (Menu *pMenu, const int iStyle);

void AddMenuItem   (Menu *pMenu, const char *sItem, const int iReturn);
void AddMenuItemKey(Menu *pMenu, const char *sItem, const char *sKeys, const int iReturn);

char DrawMenu      (Menu *pMenu);

# endif // INC_MENU_H
