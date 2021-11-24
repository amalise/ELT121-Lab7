#ifndef INC_SETTINGS_H
#define INC_SETTINGS_H

// These values cannot be mutable outside this context.
// The delimiter cannot be used in a setting name, but can appear in a value.
#define SETTINGS_FILE           "settings.txt"
#define SETTINGS_DELIM          '='
#define SETTINGS_CASE_SENSITIVE 0

typedef struct s_Setting Setting;

struct s_Setting
{
	char   *sName;
	char   *sValue;
	int     iValue;
	double  dValue;
};

// Debugging
void PrintSettings(void);
int  CountSettings(void);

// File I/O
void LoadSettings(void);
void SaveSettings(void);

// Get a setting
const char   *GetSetting      (const char *sName); // char blob by default
const char   *GetSettingString(const char *sName);
const char    GetSettingChar  (const char *sName);
const int     GetSettingInt   (const char *sName);
const double  GetSettingFloat (const char *sName);

// Add a setting
void AddSetting      (const char *sName, const char   *sValue);
void AddSettingString(const char *sName, const char   *sValue);
void AddSettingChar  (const char *sName, const char    cValue);
void AddSettingInt   (const char *sName, const int     iValue);
void AddSettingFloat (const char *sName, const double  dValue);

// Change a setting
void ChangeSetting      (const char *sName, const char   *sValue);
void ChangeSettingString(const char *sName, const char   *sValue);
void ChangeSettingChar  (const char *sName, const char    cValue);
void ChangeSettingInt   (const char *sName, const int     iValue);
void ChangeSettingFloat (const char *sName, const double  dValue);

// Remove a setting
void RemoveSetting      (const char *sName);

#endif // INC_SETTINGS_H
