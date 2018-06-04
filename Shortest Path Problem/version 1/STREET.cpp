# include "STREET.h"

// Hàm đọc từng thông tin của con đường
// Thông tin gồm: tên đường (strName), chiều dài (fLength), thời gian đi hết con đường (fTime)
void CSTREET::readFile(int check)
{
	// Dựa vào check để kiểm tra thông tin đọc vào có đang ở cuối dòng trong file hay không
	if (check)
		getline(cin, strName, '/');
	else
		getline(cin, strName);
	// Nếu hai địa điểm không nối nhau thì không có tên đường (gán chuỗi strName rỗng)
	if (strName[0] == '-')
		strName = "";
	// Ngược lại
	else
	{
		int i = 0;
		int carry;
		while (strName[i] != ',')
			i++;
		fLength = (float)atof(&strName[i + 1]); // Lấy chiều dài con đường
		carry = i;
		i++;
		while (strName[i] != ',')
			i++;
		fTime = (float)atof(&strName[i + 1]);
		fTime = fLength / fTime; // Lấy thời gian chạy hết con đường
		strName.erase(carry);
	}
}

// Phương thức khởi tạo mặc định
CSTREET::CSTREET()
{
	strName = "";
	fLength = 0;
	fTime = 0;
}

// Phương thức hủy
CSTREET::~CSTREET()
{
}
