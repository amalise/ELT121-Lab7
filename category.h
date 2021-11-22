#ifndef INC_CATEGORY_H
#define INC_CATEGORY_H

/*
struct Category
{
	char   *sName;
	int     iOrder;
};
// typedef struct Category Category;

struct CategoryList
{
	struct Category     *pItem;
	struct CategoryList *pNext;
};
// typedef struct CategoryList CategoryList;

struct CategoryList *ReadCategoryFile(const char *sFileName);
void WriteCategoryFile(struct CategoryList *pCategories, const char *sFileName);
void CategorySort(struct CategoryList *pCategories);
void FreeCategoryList(struct CategoryList *pCategories);
/**/

#endif // INC_CATEGORY_H
