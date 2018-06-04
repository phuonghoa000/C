#include "STREET.h"

// Hàm đọc thông tin của con đường
// Thông tin bao gồm: tên đường (strName), chiều dài (fLength), thời gian đi hết con đường (fTime)
void CSTREET::readFile(int check)
{
	// Dựa vào biến check để kiểm tra thông tin hiện tại có ở cuối dòng hay không
	if (check)
		getline(cin, strName, '/');
	else
		getline(cin, strName);
	// Nếu giữa hai địa điểm không nối với nhau, tức là không tồn tại con đường nào
	if (strName[0] == '-')
		strName = "";
	else
	{
		int i = 0;
		int carry;
		while (strName[i] != ',')
			i ++;
		fLength = (float)atof(&strName[i + 1]); // Lấy độ dài con đường
		carry = i;
		i ++;
		while (strName[i] != ',')
			i ++;
		fTime = (float)atof(&strName[i + 1]);
		fTime = fLength / fTime; // Lấy thời gian đi hết con đường
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
