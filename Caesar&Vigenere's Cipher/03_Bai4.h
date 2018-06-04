#ifndef Bai4
#define Bai4
void createVigenere(char arr[][26]);
void writeFile(FILE *file, char arr[][26]);
int countChar(char *str);
void insert(char *str, int iLocation);
bool checkKey(char *strCource, char *strKey);
void establishKey(char *strCource, char *strKey);
void encryption(char *strCource, char *strKey, char *strCode, char arr[][26]);
void thucthiBai4();
#endif
