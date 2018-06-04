#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
void giai_ma(char *s,int k)
{
	for(int i=0;i<strlen(s);i++)
	{
		s[i]=tolower(s[i]);
		if(s[i]==' ')
			continue;
		s[i]-=k;
		if(s[i]<97)
			s[i]+=26;
	}
}
void thucthiBai3()
{
	char s[1000];
	char stam[1000];
	int k;
	FILE *OutFile;
	OutFile=fopen("CEASAR.TXT","rt");
	if(OutFile==NULL)
		printf("\nLoi mo file CEASAR.TXT");
	else
	{
		fgets(s,256,OutFile);
		fgets(s,256,OutFile);
		for(k=1;k<=26;k++)
		{
			strcpy(stam,s);
			giai_ma(stam,k);
			printf("k=%d: ",k);
			puts(stam);
		}
	}
}