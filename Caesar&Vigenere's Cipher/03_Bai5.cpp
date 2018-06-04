# include <stdio.h>
# include <conio.h>
# include <string.h>
# include "03_Bai5.h"
# include "03_Bai4.h"
//# include "DecryptionVigenere.h"
//# include "EncryptionVigenere.h"

void createVigenere_2(char arr[][26])
{
	int iRow = 0, iColumn;
	int iCheck = 0;
	char cChar, ch = 'B';

	while (iRow < 26)
	{
		cChar = 'A';
		for (iColumn = iCheck; iColumn < 26; iColumn ++)
			arr[iRow][iColumn] = cChar ++;
		iRow ++;
		iCheck ++;
	}
	iCheck = 24;
	iRow --;
	while (iRow > 0)
	{
		cChar = ch ++;
		for (iColumn = 0; iColumn <= iCheck; iColumn ++)
			arr[iRow][iColumn] = cChar ++;
		iRow --;
		iCheck --;
	}
}

void thucthiBai5()
{
	char strCource[1000];
	char strCode[1000];
	char strKey[1000];
	char strCopy[1000];
	char arrVigenere[26][26];
	int iCount;
	FILE *file = fopen("CodeVigenere_2.txt", "wt");
	FILE *file_1 = fopen("Vigenere_2.txt", "wt");

	printf("Chuong trinh giai ma Vigenere.\n\n");
	printf("Cac luu y:\n");
	printf("1. Khoa chi gom cac ky tu chu cai, khong chua bat ky ky tu nao khac.\n");
	printf("2. Do dai cua khoa khong qua tong cac ky tu chu cai cua ban ro.\n");
	printf("    Vi du: Ban ma: P TVDL GVC.\n");
	printf("           Khoa: do dai khong qua 8 ky tu.\n\n");

	printf("Nhap ban ma: ");
	fflush(stdin);
	gets(strCode);
	strupr(strCode);
	iCount = countChar(strCode); // Dem cac ky tu chu cai cua ban ro

	printf("\nNhap khoa (Do dai <= %d): ", iCount);
	gets(strKey);
	strupr(strKey);
	strcpy(strCopy, strKey);

	establishKey(strCode, strKey);
	createVigenere_2(arrVigenere);
	encryption(strCode, strKey, strCource, arrVigenere);

	printf("\nBan ro: ");
	puts(strCource);

	writeFile(file, arrVigenere);
	fprintf(file_1, "Ban ma: ");
	fputs(strCode, file_1);
	fprintf(file_1, "\nKhoa: ");
	fputs(strCopy, file_1);
	fprintf(file_1, "\nBan ro: ");
	fputs(strCource, file_1);

	fclose(file);
	fclose(file_1);

	getch();
}