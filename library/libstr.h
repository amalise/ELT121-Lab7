#ifndef INC_STRLIB_H
#define INC_STRLIB_H

/*
 * Character manipulation and transformation library.
 *
 * WARNING: These functions modify their parameter string. The returned
 *          pointer is for convenience.
 */

// Strip white-space from the beginning and end of a string
char *StringTrim(char *sString);

// Convert a string to upper case
char *StringToUpper(char *sString);

// Convert a string to upper case
char *StringToLower(char *sString);

#endif // INC_STRLIB_H
