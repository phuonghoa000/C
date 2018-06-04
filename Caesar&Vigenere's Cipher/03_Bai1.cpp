// Hàm thucthiBai1() có nhiệm vụ mã hóa mật mã Ceasar
// Input: Bản rõ và khóa 
// Output: Bản mã

// Các dòng khai báo thư viện
# include <stdio.h>  // Thư viện chứa các hàm xuất nhập chuẩn như printf, scanf
# include <conio.h>  // Thư viện chứa hàm getch();
# include <string.h> // Thư viện chứa các hàm xử lý chuỗi
# include <ctype.h>  // Thư viện chứa các hàm in hoa, in thường kí tự như toupper, tolower

# define MAX_LEN 256 // MAX_LEN là độ dài chuỗi

void thucthiBai1()
{
	FILE *inFile;    //Khai báo file
	inFile = fopen("CEASAR.TXT", "wt");  //Mở file để ghi

	// Nếu mở file thất bại thì thông báo cho người dùng biết
	if(inFile == NULL)
		printf("\nLoi mo file CEASAR.TXT");  //Thông báo lỗi mở file
	// Nếu không
	else
	{
		char strBanRo[MAX_LEN]; // Khai báo chuỗi (bản rõ của mật mã Ceasar)
		char strBanMa[MAX_LEN]; // Khai báo chuỗi (bản mã của mật mã Ceasar)
		int iKhoa;   // Khai báo khóa thuộc kiểu nguyên
		
		printf("Bai 1. Ma hoa ban ro cua ma hoa Ceasar.\n\n");
		printf("Cac luu y:\n");
		printf("  1. Ban ro la mot chuoi ky tu.\n");
		printf("  2. Khoa la mot so nguyen.\n\n");

		// Nhập vào bản rõ
		printf("Nhap vao ban ro can ma hoa: ");
		fflush(stdin);
		gets(strBanRo);

		fputs(strBanRo, inFile); // Ghi bản rõ vào trong file CEASAR.TXT
		fprintf(inFile, "\n");   // Ghi kí tự xuống dòng vào trong file CEASAR.TXT

		strlwr(strBanRo); // Chuyển các kí tự trong bản rõ thành kí tự thường
		strcpy(strBanMa, strBanRo);
	
		// Nhập khóa
		printf("\nNhap vao khoa: ");
		scanf("%d", &iKhoa);
		iKhoa %= 26; // Câu lệnh dùng để giới hạn khóa 0 <= iKhoa <= 25

		// Vòng lặp dùng để thay thế từng kí tự trong bản rõ thành những kí tự đã được mã hóa Ceasar
		for(int i = 0; i < strlen(strBanMa); i ++)
		{
			if(strBanMa[i] < 97 || strBanMa[i] > 102) // Nếu gặp các ký tự khác ký tự chữ cái thường thì bỏ qua
				continue;
			strBanMa[i] += iKhoa;   // Cộng khóa vào giá trị của các kí tự trong mã ASCII
			// 2 trường hợp ngoại lệ 
			if(strBanMa[i] > 122)   // Mã ASCII của kí tự sau khi cộng lớn hơn 122
				strBanMa[i] -= 26;  // thì trừ đi cho 26
			if(strBanMa[i] < 0)     // Mã ASCII của kí tự sau khi cộng bé hơn 0
				strBanMa[i] += 230; // thì cộng thêm cho 230
		}

		printf("\n\nBan ma (Cipher) thu duoc sau khi ma hoa ban ro la: \n");
		puts(strBanMa);  // In bản mã sau khi mã hóa ra màn hình cho người dùng xem
		fputs(strBanMa, inFile); // Ghi bản mã sau khi mã hóa vào trong file
	}
}