// 03_DoAn3_1412140_1412188_1412192

// Khai báo lần lượt các thư viện cần sử dụng
# include <stdio.h>
# include <conio.h>
# include <windows.h>
# include "03_Bai1.h"
# include "03_Bai2.h"
# include "03_Bai3.h"
# include "03_Bai4.h"
# include "03_Bai5.h"

void main(void)
{
	char cTraLoi;
	int iChon;

	do
	{
		system("cls"); // Hàm xóa màn hình
		// Xuất đoạn giới thiệu chương trình mã hóa Ceasar và Vigenere dưới đây ra màn hình
		printf("***************DO AN 3 - 1412140 - 1412188 - 1412192***************\n");
		printf("**********           DE TAI 3: MA HOA CO DIEN            **********\n");
		printf("***** I.MA HOA CEASAR:                                        *****\n");
		printf("*****   Bai 1. Ma hoa ban ro cua ma hoa Ceasar.               *****\n");
		printf("*****   Bai 2. Giai ma ban ma cua ma hoa Ceasar.              *****\n");
		printf("*****   Bai 3. Tan cong ban ma Ceasar de tim ra khoa.         *****\n");
		printf("***** II.MA HOA VIGENERE:                                     *****\n");
		printf("*****   Bai 4. Ma hoa ban ro cua ma hoa Vigenere.             *****\n");
		printf("*****   Bai 5. Giai ma ban ma cua ma hoa Vigenere.            *****\n");
		printf("*******************************************************************\n\n");

		// Cho phép người dùng lựa chọn chương trình để thực hiện
		// Sau khi người dùng chọn xong, tiến hành xóa màn hình
		printf("Ban chon 1 trong cac chuong trinh tren de thuc hien.\n");
		printf("Nhan phim so tuong ung voi tung bai.\n");
		printf("   Vi du: nhan phim 1: chuong trinh se thuc thi Bai 1.\n");
		printf("Lua chon cua ban: ");
		scanf("%d", &iChon);
		system("cls");

		// Dựa vào lựa chọn của người dùng qua biến iChon
		// Thực hiện lệnh tương ứng
		// Nếu lựa chọn của người dùng không nằm trong các nội dung sẵn có của chương trình
		// Xuất dòng "Ban chon khong hop le!" ra man hinh
		switch(iChon)
		{
		case 1: thucthiBai1(); break;
		case 2: thucthiBai2(); break;
		case 3: thucthiBai3(); break;
		case 4: thucthiBai4(); break;
		case 5: thucthiBai5(); break;
		default : printf("Ban chon khong hop le!");
		}

		// Cho người dùng lựa chọn có tiếp tục sử dụng chương trình hay ngừng lại
		// bằng cách nhấn phím Y (yes) hoặc N (no)
		printf("\nBan muon thuc hien cac chuong trinh khac khong?-(Y/N)");
		fflush(stdin);
		scanf("%c", &cTraLoi);
	}
	while((cTraLoi != 'n') && (cTraLoi != 'N'));

	_getch();
}