#ifndef INC_MENU_H
#define INC_MENU_H

#define MENU_STYLE_NONE    0
#define MENU_STYLE_ALPHA   1
#define MENU_STYLE_NUMERIC 2

typedef struct s_MenuItem MenuItem;
typedef struct s_Menu Menu;

struct s_MenuItem
{
	char     *sItem;
	char     *sKeys;
	int       iReturn;
	MenuItem *pNext;
};

struct s_Menu
{
	char     *sHeader;
	char     *sPrompt;
	int       iMargin;
	int       iIndent;
	int       iStyle;
	MenuItem *pItems;
};

void InitializeMenu(Menu *pMenu, char *sHeader, char *sPrompt, int   iMargin, int   iIndent, int   iStyle);
void DestroyMyMenu (Menu *pMenu);

void SetMenuHeader (Menu *pMenu, const char *sHeader);
void SetMenuPrompt (Menu *pMenu, const char *sPrompt);
void SetMenuMargin (Menu *pMenu, const int iMargin);
void SetMenuStyle  (Menu *pMenu, const int iStyle);

void AddMenuItem   (Menu *pMenu, const char *sItem, const int iReturn);
void AddMenuItemKey(Menu *pMenu, const char *sItem, const char *sKeys, const int iReturn);

int  QueryMenu          (Menu *pMenu);
int  QueryMenuWithCancel(Menu *pMenu);

# endif // INC_MENU_H
