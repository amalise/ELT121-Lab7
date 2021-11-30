#ifndef INC_SALES_H
#define INC_SALES_H

/* functions implemented in sales.c */

void SalesMenu(void);

void ResetSalesTotals(void);
void DrawSalesTotals(void);

void AddToSalesTotals(float fSale, float fTax);

#endif // INC_SALES_H
