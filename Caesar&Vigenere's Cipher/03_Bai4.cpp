# include <stdio.h>
# include <conio.h>
# include <string.h>
# include "03_Bai4.h"

// Hàm tạo mảng Vigenere
// Định nghĩa: Mảng Vigenere gồm 26 hàng 
// Mỗi hàng dịch về bên trái một bước so với hàng phía trên,
// tạo thành 26 bảng mã Ceasar
// Input: arr[][26]
// Output: arr[][26]
void createVigenere_1(char arr[][26])
{
	int iRow, iColumn;   // Khai báo các biến iRow (dòng), iColumn (cột) tương ứng với mảng Vigenere
	char cChar, ch = 64; // Khai báo ký tự ch và gán ch = 64, tức là ch tương ứng với ký tự đứng trước ký tự A

	// Thực hiện vòng lặp từ dòng đầu tiên đến dòng thứ 26 của mảng (iRow sẽ chạy từ 0 đến 25)
	for (iRow = 0; iRow < 26; iRow ++)
	{
		cChar = ++ ch ; // Tang ch len 1 don vi, sau do gan cChar cho ch
		// Thuc hien vong lap tu cot thu nhat den cot thu 26 cua mang (iColumn se chay tu 0 den 25)
		for (iColumn = 0; iColumn < 26; iColumn ++)
			// Gan phan tu dang xet cua mang cho ky tu chu cai tuong ung
			// Ky tu nay la cChar neu cChar nam trong khoang tu A den Z
			// Ky tu nay la cChar - 26 neu cChar nam ngoai va lon hon Z (cChar > 90)
			// Trong phep gan duoi day, o ve ben phai,
			// thu tu thuc hien phep tinh: (cChar > 90) => tra ve 1 hoac 0,
			// tiep theo: 26 * (cChar > 90) => ket qua la 0 hoac 26,
			// sau do: cChar - 26 * (cChar > 90) => ket qua tra ve tu 65 den 90, tuong ung voi chu cai can tim
			// cuoi cung: cChar ++ => tang cChar len mot don vi
			arr[iRow][iColumn] = cChar ++ - 26 * (cChar > 90);
	}
}

void writeFile(FILE *file, char arr[][26])
{
	for (int i = 0; i < 26; i ++)
	{
		for (int j = 0; j < 26; j ++)
			fprintf(file, "%c ", arr[i][j]);
		fprintf(file, "\n");
	}
}

// Ham dem cac ky tu chu cai cua mot chuoi
// Input: *str: chuoi can dem ky tu
// Output: iCount: so luong ky tu cua chuoi
int countChar(char *str)
{
	int i, iCount = 0; // Ban dau, gan bien dem ky tu iCount = 0

	// Thuc hien vong lap tu 0 den vi tri cua ky tu cuoi cung cua chuoi
	// Neu ky tu nam trong khoang tu A den Z, tang bien dem iCount len mot don vi
	for (i = 0; i < strlen(str); i ++)
		if (str[i] > 64 && str[i] < 91)
			iCount ++;

	return iCount;
}

// Ham chen ky tu ' ' (khoang trang) vao vi tri xac dinh (iLocation) cua chuoi
// Input: *str, iLocation
// Output: *str
void insert(char *str, int iLocation)
{
	int i, iLength = strlen(str); // Khai bao va gan bien iLength cho do dai chuoi str

	// Thuc hien vong lap nguoc tu vi tri cuoi cung cua chuoi den vi tri dung truoc vi tri can chen,
	// gan phan tu tai vi tri dang xet cho phan tu dung truoc no trong chuoi
	for (i = iLength; i > iLocation; i --)
		str[i] = str[i - 1];
	// Gan ky tu ' ' (khoang trang) cho phan tu tai vi tri iLocation cua chuoi
	str[iLocation] = ' ';
	// Dat ky tu '\0' ngay sau ky tu cuoi cung cua chuoi
	str[iLength + 1] = '\0';
}

// Ham kiem tra tinh hop le chuoi khoa (strKey)
// Input: *strCource, *strKey
// Output: 1 hoac 0
bool checkKey(char *strCource, char *strKey)
{
	int i;

	// Neu do dai chuoi khoa lon hon do dai chuoi nguon (ban ro)
	// tra ve 0
	if (strlen(strKey) > countChar(strCource))
		return 0;
	// Neu cau lenh tren tra ve 1,
	// thi thuc hien hien vong lap tu ky tu dau tien den ky tu cuoi cung cua chuoi
	// Neu ton tai mot ky tu khong thuoc A den Z (tuc la tu 65 den 90), lap tuc tra ve 0
	for (i = 0; i < strlen(strKey); i ++)
		if (strKey[i] < 65 || strKey[i] > 90)
			return 0;
	// Neu chuoi khong chua ky tu khac ky tu chu cai, tra ve 1
	return 1;
}

// Ham thiet lap khoa
// Chuoi khoa hien tai co do dai <= do dai chuoi nguon (ban ro)
// Thiet lap khoa bang cach viet lai no nhieu lan tren mot dong
// den khi so chu cai tren khoa bang so chu cai tren ban ro.
// Dong thoi, cac vi tri tren ban ro khong phai la ky tu chu cai
// thi tuong ung tren khoa la ky tu ' ' (khoang trang)
// VD: Ban ro: I love you
//     Khoa: html
//     Khoa sau khi thiet lap: H TMLH TML
// Input: *strCource, *strKey
// Output: *strKey
void establishKey(char *strCource, char *strKey)
{
	char str[1000];
	int iLength, iCount;
	int iDiv, i;

	iCount = countChar(strCource); // Dem so ky tu chu cai cua chuoi nguon strCource
	iLength = strlen(strKey); // Tim do dai chuoi khoa strKey

	strcpy(str, strKey); // Sao chep chuoi khoa (hien tai) vao chuoi str
	iDiv = iCount / iLength; // Lay so ky tu chu cai cua chuoi nguon chia cho do dai chuoi khoa, lay nguyen, gan vao iDiv
	// Thuc hien vong lap tu 1 den iDiv
	// Cong chuoi str vao chuoi khoa voi tung vong lap
	for (i = 1; i <= iDiv; i ++)
		strcat(strKey, str);
	strKey[iCount] = '\0'; // Dat ky tu '\0' vao sau ky tu cuoi cung cua chuoi khoa

	// Thuc hien vong lap tu 0 den vi tri cua ky tu cuoi cung cua chuoi nguon
	for (i = 0; i < strlen(strCource); i ++)
		// Neu ky tu dang xet cua chuoi nguon khong nam trong khoang tu A den Z
		// goi ham insert de chen ky tu ' ' (khoang trang) vao chuoi khoa
		// ngay tai vi tri dang xet cua chuoi nguon
		if (strCource[i] < 65 || strCource[i] > 90)
			insert(strKey, i);
}

// Ham ma hoa chuoi nguon (ban ro)
// Input: *strCource, * strKey, *strCode, arr[][26]
// Output: *strCode (ban ma)
void encryption(char *strCource, char *strKey, char *strCode, char arr[][26])
{
	// Thuc hien vong lap tu vi tri dau tien den vi tri cuoi cung cua chuoi nguon (ban ro)
	for (int i = 0; i < strlen(strCource); i ++)
		// Neu ky tu tai vi tri dang xet nam trong khoang tu A den z thi tien hanh ma hoa
		if (strCource[i] > 64 && strCource[i] < 91)
			strCode[i] = arr[strKey[i] - 65][strCource[i] - 65];
	    // Neu ky tu tai vi tri dang xet nam ngoai khoang tu A den Z,
	    // gan ky tu tai vi tri do cua chuoi strCode (ban ma) cho ky tu cung tai vi tri do cua chuoi strCource (ban ro)
		else
			strCode[i] = strCource[i];
	// Dat ky tu '\0' ngay sau ky tu cuoi cung cua chuoi strCode (ban ma)
	strCode[strlen(strCource)] = '\0';
}

void thucthiBai4()
{
	char strCource[1000];     // Khai báo chuỗi nguồn (bản rõ) 
	char strKey[1000];        // Khai báo chuỗi khóa
	char strCode[1000];       // Khai báo chuỗi bản mã
	char strCopy[1000];
	char arrVigenere[26][26]; // Khai báo mảng Vigenere
	int iCount;
	FILE *file = fopen("CodeVigenere_1.txt", "wt");
	FILE *file_1 = fopen("Vigenere_1.txt", "wt");
		
	printf("Chuong trinh ma hoa Vigenere.\n\n");
	printf("Cac luu y khi nhap ban ro va khoa:");
	printf("\n1. Khoa chi gom cac ky tu chu cai, khong chua bat ky ky tu nao khac.");
	printf("\n2. Do dai cua khoa khong qua tong cac ky tu chu cai cua ban ro.");
	printf("\n    Vi du: Ban ro: I love you.\n");
	printf("           Khoa: do dai khong qua 8 ky tu.\n\n");

	// Nhập bản rõ
	printf("Nhap ban ro: ");
	fflush(stdin);
	gets(strCource);
	strupr(strCource); // In hoa các ký tự chữ cái của bản rõ
	iCount = countChar(strCource); // Đếm các ký tự chữ cái của bản rõ

	// Nhập khóa
	printf("\nNhap khoa (Do dai <= %d): ", iCount);
	gets(strKey);
	strupr(strKey); // In hoa các ký tự của khóa
	// Kiểm tra tính hợp lệ của khóa	// Nếu khóa chứa các ký tự khác chữ cái, nhập lại khóa
	while (checkKey(strCource, strKey) == 0)
	{
		printf("Nhap lai khoa (Do dai <= %d): ", iCount);
		gets(strKey);
		strupr(strKey);
	}
	strcpy(strCopy, strKey);

	// Gọi lần lượt các hàm phục vụ cho việc mã hóa bản rõ
	establishKey(strCource, strKey); // Hàm thiết lập khóa
	createVigenere_1(arrVigenere); // Hàm tạo mảng Vigenere
	encryption(strCource, strKey, strCode, arrVigenere); // Hàm mã hóa bản rõ
	// Xuất bản mã ra màn hình
	printf("\nBan ma: ");
	puts(strCode);

	writeFile(file, arrVigenere);
	fprintf(file_1, "Ban ro: ");
	fputs(strCource, file_1);
	fprintf(file_1, "\nKhoa: ");
	fputs(strCopy, file_1);
	fprintf(file_1, "\nBan ma: ");
	fputs(strCode, file_1);

	fclose(file);
	fclose(file_1);

	getch();
}