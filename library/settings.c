#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "libstr.h"
#include "settings.h"

#define BUFFER_LENGTH 255

/*
 * Global list of settings
 */
typedef struct s_SettingNode SettingNode;//defines a new type

struct s_SettingNode
{
	Setting     *mySetting;
	SettingNode *pNext;
};

SettingNode *SETTINGS = NULL;

/*
 * Debugging
 */
void PrintSettings(void)
{
    SettingNode *pCur;
    for(pCur = SETTINGS; pCur; pCur = pCur->pNext)
    {
        printf("[%s] = [%s]\n", pCur->mySetting->sName, pCur->mySetting->sValue);
    }
}

int CountSettings(void)
{
    SettingNode *pCur;
    int i = 0;

    for(pCur = SETTINGS; pCur; pCur = pCur->pNext, i++)
        ;

    return i;
}

/*
 * File I/O
 */
void LoadSettings(void)
{
	FILE *pFile;
	char  sName[BUFFER_LENGTH];
	char *sValue;

#ifdef SETTINGS_FILE
	pFile = fopen(SETTINGS_FILE, "r");
#else
	pFile = fopen("settings.txt", "r");
#endif // SETTINGS_FILE

	if(pFile)
	{
		while(fgets(sName, BUFFER_LENGTH, pFile))
		{
		    if(strlen(sName))
            {
                sValue = strchr(sName, SETTINGS_DELIM);
                if(sValue)
                {
                    *sValue = '\0';
                    sValue++;
                    AddSetting(sName, sValue);
                }
            }
		}
		fclose(pFile);
	}
}

void SaveSettings(void)
{
	FILE *pFile;
	SettingNode *pCur;

#ifdef SETTINGS_FILE
	pFile = fopen(SETTINGS_FILE, "w");
#else
	pFile = fopen("settings.txt", "w");
#endif // SETTINGS_FILE

	if(pFile)
	{
		for(pCur = SETTINGS; pCur; pCur = pCur->pNext)
		{
			fprintf(pFile, "%s %c %s\n",
				    pCur->mySetting->sName,
				    SETTINGS_DELIM,
				    pCur->mySetting->sValue);
		}
		fclose(pFile);
	}
}

/*
 * Private utility functions
 */
SettingNode *FindSettingNode(const char *sName)
{
	SettingNode *pCur;
	SettingNode *pFound = NULL;
	char *sNeedle = malloc(strlen(sName) + 1);

	if(strlen(sName) == 0)
		return NULL;

	strcpy(sNeedle, sName);
	StringTrim(sNeedle);
#if SETTINGS_CASE_SENSITIVE	== 0
	StringToUpper(sNeedle);
#endif // SETTINGS_CASE_SENSITIVE

	for(pCur = SETTINGS; pCur; pCur = pCur->pNext)
	{
		if(strcmp(sNeedle, pCur->mySetting->sName) == 0)
		{
			pFound = pCur;
		}
	}

	free(sNeedle);
	return pFound;
}

Setting *FindSetting(const char *sName)
{
	SettingNode *pNode = FindSettingNode(sName);

	if(pNode)
		return pNode->mySetting;
}

// Updates iValue and dValue based on sValue
void PopulateSetting(const Setting *pSetting)
{
	sscanf(pSetting->sValue, "%i",  &(pSetting->iValue));
	sscanf(pSetting->sValue, "%lf", &(pSetting->dValue));
}

int  IsSetting(const char *sName)
{
    if(FindSetting(sName))
        return 1;
    return 0;
}

/*
 * Get a setting
 */
const char   *GetSetting      (const char *sName)
{
	return GetSettingString(sName);
}

const char   *GetSettingString(const char *sName)
{
	Setting *pSetting = FindSetting(sName);
	if(pSetting)
		return pSetting->sValue;
	return NULL;
}

const char    GetSettingChar  (const char *sName)
{
	Setting *pSetting = FindSetting(sName);
	if(pSetting)
		return pSetting->sValue[0];
	return (char)0;
}

const int     GetSettingInt   (const char *sName)
{
	Setting *pSetting = FindSetting(sName);
	if(pSetting)
		return pSetting->iValue;
	return 0;
}

const double  GetSettingFloat (const char *sName)
{
	Setting *pSetting = FindSetting(sName);
	if(pSetting)
		return pSetting->dValue;
	return 0.0;
}

/*
 * Add a setting
 */
void AddSetting      (const char *sName, const char   *sValue)
{
	if(FindSettingNode(sName))
	{
		ChangeSetting(sName, sValue);
		return;
	}

	SettingNode *pNode;
	char *sNeedle = malloc(strlen(sName) + 1);

	strcpy(sNeedle, sName);
	StringTrim(sNeedle);
#if SETTINGS_CASE_SENSITIVE	== 0
	StringToUpper(sNeedle);
#endif // SETTINGS_CASE_SENSITIVE

	// Add to the stack
	pNode = malloc(sizeof(SettingNode));
	pNode->pNext = SETTINGS;
	SETTINGS = pNode;

	// Create the setting data
	pNode->mySetting = malloc(sizeof(Setting));
	pNode->mySetting->sName = malloc(strlen(sNeedle) + 1);
	pNode->mySetting->sValue = malloc(strlen(sValue) + 1);
	strcpy(pNode->mySetting->sName,  sNeedle);
	strcpy(pNode->mySetting->sValue, sValue);
	StringTrim(pNode->mySetting->sValue);

	// Update the non-string setting data
	PopulateSetting(pNode->mySetting);
}

void AddSettingString(const char *sName, const char   *sValue)
{
	AddSetting(sName, sValue);
}

void AddSettingChar  (const char *sName, const char    cValue)
{
	char sVal[20];
	sprintf(sVal, "%c", cValue);
	AddSetting(sName, sVal);
}

void AddSettingInt   (const char *sName, const int     iValue)
{
	char sVal[20];
	sprintf(sVal, "%i", iValue);
	AddSetting(sName, sVal);
}

void AddSettingFloat (const char *sName, const double  dValue)
{
	double sVal[20];
	sprintf(sVal, "%f", dValue);
	AddSetting(sName, sVal);
}

/*
 * Change a setting
 */
void ChangeSetting      (const char *sName, const char   *sValue)
{
	Setting *pSetting = FindSetting(sName);

	if(strlen(sValue) == 0)
	{
        RemoveSetting(sName);
	}
	else if(pSetting)
	{
		free(pSetting->sValue);
		pSetting->sValue = malloc(strlen(sValue) + 1);
		strcpy(pSetting->sValue, sValue);
		StringTrim(pSetting->sValue);
		PopulateSetting(pSetting);
	}
	else
	{
		AddSetting(sName, sValue);
	}
}

void ChangeSettingString(const char *sName, const char   *sValue)
{
	ChangeSetting(sName, sValue);
}

void ChangeSettingChar  (const char *sName, const char    cValue)
{
	char sVal[20];
	sprintf(sVal, "%c", cValue);
	ChangeSetting(sName, sVal);
}

void ChangeSettingInt   (const char *sName, const int     iValue)
{
	char sVal[20];
	sprintf(sVal, "%i", iValue);
	ChangeSetting(sName, sVal);
}

void ChangeSettingFloat (const char *sName, const double  dValue)
{
	double sVal[20];
	sprintf(sVal, "%f", dValue);
	ChangeSetting(sName, sVal);
}

/*
 * Remove a setting
 */
void RemoveSetting      (const char *sName)
{
	SettingNode *pNode = FindSettingNode(sName);
	SettingNode *pNTmp;

	// If not found, do nothing
	if(!pNode)
		return;

	// Weave pNode out of the stack
	if(SETTINGS == pNode)
	{
		SETTINGS = pNode->pNext;
	}
	else
	{
		for(pNTmp = SETTINGS; pNTmp->pNext != pNode; pNTmp = pNTmp->pNext)
			;
		pNTmp->pNext = pNode->pNext;
	}

	// Abolish pNode
	free(pNode->mySetting->sName);
	free(pNode->mySetting->sValue);
	free(pNode->mySetting);
	free(pNode);
}
