#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "libstr.h"

//String modification function library

char *StringTrim(char *sString)
{
    int iLen = 0;
    char *cFront = sString;
    char *cEnd   = NULL;

    if(sString == NULL)
	{
		return NULL;
	}
    if(sString[0] == '\0')
    {
    	return sString;
    }

    iLen = strlen(sString);
    cEnd = sString + iLen - 1;

    while(isspace(*cFront))
    {
        cFront++;
    }
    if(cEnd != cFront)
    {
        while(isspace(*cEnd) && (cEnd != cFront))
            cEnd--;
    }
    *(cEnd + 1) = '\0';

    if(cFront != sString)
    {
        cEnd = sString;
    	while(*cFront)
    	{
    		*cEnd++ = *cFront++;
    	}
    	*cEnd = '\0';
    }

    return sString;
}

char *StringToUpper(char *sString)
{
    for(int i = 0; i < strlen(sString); i++)
        sString[i] = toupper(sString[i]);
    return sString;
}

char *StringToLower(char *sString)
{
    for(int i = 0; i < strlen(sString); i++)
        sString[i] = tolower(sString[i]);
    return sString;
}
