/*
Hàm thucthiBai2() có nhiệm vụ giải mã của mật mã Ceasar
Input: Bản rõ và khóa k
Output: Bản mã
*/

//Các dòng khai báo thư viện
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#define MAX_LEN 10000
void thucthiBai2()
{
	char s[MAX_LEN];
	int k;
	FILE *OutFile;
	OutFile=fopen("CEASAR.TXT","rt");
	if(OutFile==NULL)
		printf("\nLoi mo file CEASAR.TXT");
	else
	{
		fgets(s,10000,OutFile);
		fgets(s,10000,OutFile);
		printf("\nDa doc ban ma tu file thanh cong!");
		printf("\nNhap vao khoa k: ");
		scanf("%d", &k);
		k%=26;
		for(int i=0;i<strlen(s);i++)
		{
			s[i]=tolower(s[i]);
			if(s[i]==' ')
				continue;
			s[i]-=k;
			if(s[i]<97)
				s[i]+=26;
		}
		s[0]=toupper(s[0]);
		printf("\nBan ro (Plain text) thu duoc sau khi giai ma la: \n");
		puts(s);
	}
}