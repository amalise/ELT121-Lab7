#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "libstr.h"

char *StringTrim(char *sString)
{
    int iLen = 0;
    char *cFront = sString;
    char *cEnd = NULL;

    if(sString == NULL)
	{
		return NULL;
	}
    if(sString[0] == '\0')
    {
    	return sString;
    }

    iLen = strlen(sString);
    cEnd = sString + iLen;

    while(isspace((unsigned char) *cFront))
        cFront++;
    if(cEnd != cFront)
    {
        while(isspace((unsigned char *) *(--cEnd)) && (cEnd != cFront))
            ;
    }

    if(cFront != sString && cEnd == cFront)
    {
    	*sString = '\0';
    }
    else if(sString + iLen - 1 != cEnd)
    {
    	*(cEnd + 1) = '\0';
    }

    cEnd = sString;
    if(cFront != sString)
    {
    	while (*cFront)
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
