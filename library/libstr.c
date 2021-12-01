#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "libstr.h"

//String modification function library

char *StringTrim(char *sString)//Function to remove whitespace from strings
{
    int iLen = 0;//sets iLen to 0
    char *cFront = sString;//sets check to front of string
    char *cEnd   = NULL;//sets check to end of string

    if(sString == NULL)//checks to see if there is a string
	{
		return NULL;
	}
    if(sString[0] == '\0')//checks character array for null character
    {
    	return sString;
    }

    iLen = strlen(sString);//sets iLen to strlen and returns sString
    cEnd = sString + iLen - 1;//sets cEnd to sString and adds iLen, then subtracts one

    while(isspace(*cFront))//pointer navigation
    {
        cFront++;//moves pointer
    }
    if(cEnd != cFront)//checks location of pointer
    {
        while(isspace(*cEnd) && (cEnd != cFront))//checks for spaces and removes them from the end of the string
            cEnd--;
    }
    *(cEnd + 1) = '\0';//captures null character

    if(cFront != sString)//checks front of string for whitespace
    {
        cEnd = sString;
    	while(*cFront)
    	{
    		*cEnd++ = *cFront++;//pointer navigation
    	}
    	*cEnd = '\0';//captures null character
    }

    return sString;
}

char *StringToUpper(char *sString)//function to set string to upper case
{
    for(int i = 0; i < strlen(sString); i++)
        sString[i] = toupper(sString[i]);
    return sString;
}

char *StringToLower(char *sString)//function to set string to lower case
{
    for(int i = 0; i < strlen(sString); i++)
        sString[i] = tolower(sString[i]);
    return sString;
}
