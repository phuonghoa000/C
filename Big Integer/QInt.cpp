#include "QInt.h"

// Hàm tìm số bù 2 của một số
// Mở rộng: hàm tìm số đối của một số
// Mặc định số đối của 0 là 0
// Cách thức: tìm bit 1 đầu tiên tính từ phải sang,
// từ vị trí kế tiếp bit 1 vừa tìm được (chiều từ phải sang), đảo tất cả các bit
QInt QInt::findTwo_Comp() const
{
	QInt big2_Comp = *this; // Khởi gán số bù 2 bằng chính số cần tìm bù 2
	__int64 mask = 1; // Biến mặt nạ dùng để tìm bit 1 đầu tiên (tính từ phải sang)
	__int64 result = 0; // Biến kết quả dùng để kết thúc vòng lặp tìm bit 1 đầu tiên
	int pos = 0; // Biến lưu vị trí bit
	bool check = 0; // Biến kiểm tra chỉ số phần tử của mảng arrBits (kiểu QInt), khởi gán ban đầu là 0

	// Nếu số cần tìm bù 2 là 0 thì trả về chính nó
	if (big2_Comp.arrBits[0] == 0 && big2_Comp.arrBits[1] == 0)
		return big2_Comp;
	// Nếu phần tử thứ 2 của mảng arrBits khác 0
	// (tức là 64 bit đầu của số kiểu QInt tồn tại ít nhất 1 bit khác 0)
	if (big2_Comp.arrBits[1] != 0)
	{
		big2_Comp.arrBits[0] = ~big2_Comp.arrBits[0]; // Đảo tất cả các bit của phần tử thứ nhất của mảng arrBits
		check = 1; // Gán biến kiểm tra chỉ số phần tử mảng arrBits cho 1 (tức là chỉ đến phần tử thứ hai)
	}

	// Tìm vị trí bit 1 đầu tiên tính từ phải sang
	while (result == 0)
	{
		result = big2_Comp.arrBits[check] & mask;
		mask = mask << 1;
		pos	++;
	}
	// Từ phải sang trái, bắt đầu tại vị trí kế tiếp bit 1 tìm được,
	// đảo tất cả các bit
	while (pos < 64)
	{
		big2_Comp.arrBits[check] = big2_Comp.arrBits[check] ^ mask;
		mask = mask << 1;
		pos ++;
	}
	
	// Trả về kết quả tìm được
	return big2_Comp;
}

// Hàm đặt bit
// VD: q = 10 (kiểu QInt)
// biểu diễn nhị phân: 1010
// nếu thêm bit 1, hàm setBit sẽ đặt bit 1 vào phía trước dãy bit trên (11010)
// khi đó q = 26
QInt QInt::setBit(int bit, int pos) const
{
	QInt q = *this; // Khởi gán q bằng số cần đặt bit
	__int64 mask = 1; // Biến mặt nạ dùng để đưa bit 1 tới vị trí cần đặt bit
	bool check = 1; // Biến kiểm tra chỉ số phần tử mảng arrBits

	// Nếu bit là 0 thì không cần làm gì nữa
	// trả về chính nó
	if (bit == 0)
		return *this;
	// Nếu vị trí đặt bit từ 64 -> 127
	// tức là nằm ở phần tử thứ nhất của mảng arrBits
	if (pos > 63)
	{
		check = 0; // Gán biến kiểm tra cho chỉ số 0
		pos = pos - 64; // Giảm vị trí đặt bit đi 64 đơn vị
	}
	// Dịch trái biến mặt nạ để bit 1 của biến này
	// nằm cùng vị trí cần đặt bit vào số kiểu QInt
	mask = mask << pos;
	// Gọi phép xor để đặt bit 1 vào vị trí đã xác định
	q.arrBits[check] = q.arrBits[check] ^ mask;
	// Trả về kết quả tìm được
	return q;
}

// Hàm chia 2 của chuỗi số thập phân
void div2(string& s)
{
	unsigned int i = 0; // Biến lưu vị trí phần tử chuỗi, khởi gán bằng 0
	int carry = 0; // Biến nhớ, khởi gán bằng 0
	int temp; // Biến tạm

	while (i < s.length())
	{
		temp = (s[i] - 48) % 2; // Lấy số dư của phép chia chữ số hàng đơn vị của chuỗi số cho 2, lưu vào biến tạm
		s[i] = ((s[i] - 48 + 10 * carry)/2 + 48); // Gán ký tự tại vị trí i bằng một nửa của nó
		carry = temp; // Gán giá trị lưu tại biến tạm cho biến nhớ
		i ++; // Tăng biến lưu vị trí thêm 1 đơn vị
	}
	// Nếu ký tự đầu của chuỗi là ký tự '0', xóa ký tự này đi
	if (s[0] == '0')
		s.erase(0, 1);
}

// Hàm chuyển chuỗi số thập phân sang số kiểu QInt
QInt QInt::convertDecToQInt(string s) const
{
	QInt q;
	int bit;
	int sign = 0; // Biến lưu bit dấu, khởi gán bằng 0
	int pos = 0; // Biến lưu vị trí đặt bit, khởi gán bằng 0
	
	// Nếu ký tự đầu chuỗi là '-', tức số âm
	if (s[0] == '-')
	{
		sign = 1; // Gán biến lưu bit dấu bằng 1
		s.erase(0, 1); // Xóa ký tự '-' khỏi chuỗi
	}

	while (s != "")
	{
		bit = (s[s.length() - 1] - 48) % 2; // Tìm số dư của phép chia chữ số hàng đơn vị của chuỗi số cho 2
		q = q.setBit(bit, pos); // Đặt bit (số dư tìm được) vào biến q (kiểu QInt)
		div2(s); // Chia chuỗi thập phân cho 2
		pos ++; // Vị trí đặt bit tăng thêm 1 đơn vị
	}
	// Nếu số âm (bit dấu bằng 1)
	if (sign)
		q = q.findTwo_Comp(); // Gọi hàm bù 2 để tìm số đối của số q hiện tại
	// Trả về kết quả tìm được
	return q;
}

// Hàm chuyển chuỗi số nhị phân sang số kiểu QInt
QInt QInt::convertBinToQInt(string s) const
{
	QInt q;
	int bit;
	int pos = 0; // Biến lưu vị trí đặt bit
	int len = s.length(); // Biến lưu chiều dài chuỗi số

	// Chạy vòng lặp từ cuối chuỗi về đầu chuỗi
	for (int i = len - 1; i >= 0; i --)
	{
		bit = (s[i] - 48); // Lấy bit từ chuỗi
		q = q.setBit(bit, pos); // Đặt bit vào số q
		pos ++; // Vị trí đặt bít tăng thêm 1 đơn vị
	}
	// Trả về kết quả tìm được
	return q;
}

// Hàm chuyển chuỗi số thập lục phân sang số kiểu QInt
QInt QInt::convertHexToQInt(string s) const
{
	QInt q;
	int temp; // Biến tạm
	int pos = 0; // Biến lưu vị trí đặt bit
	int len = s.length(); // Biến lưu chiều dài chuỗi số
	int bit;

	// Chạy vòng lặp từ cuối chuỗi về đầu chuỗi
	for (int i = len - 1; i >= 0; i --)
	{
		temp = (s[i] - 48); // Lấy ký tự số (hoặc chữ) từ chuỗi, chuyển về dạng số

		// Kiểm tra số vừa lấy lớn hơn 9,
		// tức ký tự từ chuỗi là chữ từ 'A' -> 'F'
		if (temp > 9)
			temp = s[i] - 55; // chuyển về dạng số tương ứng (10 -> 15)
		
		// Số vừa lấy được biểu diễn bằng 4 bit
		// Chạy vòng lặp 4 lần,
		for (int j = 0; j < 4; j ++)
		{
			bit = temp & 1; // Lấy bit ngoài cùng bên phải
			temp = temp >> 1; // Dịch biến tạm sang phải 1 bit
			q = q.setBit(bit, pos ++); // Đặt bit vào số q
		}
	}
	// Trả về kết quả tìm được
	return q;
}

// Hàm định nghĩa toán tử "="
QInt& QInt::operator = (const QInt& q)
{
	arrBits[0] = q.arrBits[0];
	arrBits[1] = q.arrBits[1];

	return *this;
}

// Hàm định nghĩa toán tử "+"
const QInt QInt::operator + (const QInt& q) const
{
	QInt bigSum; // Biến lưu tổng hai số hạng

	// Cộng từng phần tử có chỉ số tương ứng
	bigSum.arrBits[1] = arrBits[1] + q.arrBits[1];
	bigSum.arrBits[0] = arrBits[0] + q.arrBits[0];
	
	// Kiểm tra các trường hợp tràn bit
	// Nếu nằm trong các trường hợp dưới đây,
	// cộng thêm 1 (kiểu nguyên) vào phần tử thứ nhất của mảng arrBits của biến tổng 
	if (arrBits[1] < 0 && q.arrBits[1] < 0)
		bigSum.arrBits[0] ++;

	if (arrBits[1] < 0 && q.arrBits[1] >= 0 && bigSum.arrBits[1] >= 0)
		bigSum.arrBits[0] ++;

	if (arrBits[1] >= 0 && q.arrBits[1] < 0 && bigSum.arrBits[1] >= 0)
		bigSum.arrBits[0] ++;
	// Trả về kết quả tìm được
	return bigSum;
}

// Hàm định nghĩa toán tử "-"
const QInt QInt::operator - (const QInt& q) const
{
	QInt bigSub = q; // Biến lưu hiệu hai số

	bigSub = bigSub.findTwo_Comp(); // Tìm số đối của số hạng thứ 2
	bigSub = *this + bigSub; // Cộng số hạng thứ nhất với số đối vừa tìm được
	// Trả về kết quả tìm được
	return bigSub;
}

// Hàm định nghĩa toán tử "*"
// Dùng thuật toán nhân cải tiến
const QInt QInt::operator * (const QInt& q) const
{
	QInt bigMul = q; // Biến lưu tích hai thừa số, khởi gán bằng thừa số thứ 2
	QInt bigTemp; // Biến tạm
	__int64 mask = 0x8000000000000000; // Biến mặt nạ, khởi gán bằng số âm nhỏ nhất mà kiểu __int64 biểu diễn được
	int check = 0; // Biến kiểm tra
	int bit;

	// Vòng lặp gồm 128 lần lặp, tương đương số bit của kiểu QInt là 128
	for (int i = 0; i < 128; i ++)
	{
		// Nếu bit cuối của biến tích là 1 và biến check là 0
		if ((bigMul.arrBits[1] & 1) && (check == 0))
			bigTemp = bigTemp - *this; // Gán biến tạm cho hiệu của nó với thừa số thứ nhất
		// Nếu bit cuối của biến tích là 0 và biến check là 1
		if (((bigMul.arrBits[1] & 1) == 0) && check)
			bigTemp = bigTemp + *this; // Gán biến tạm cho tổng của nó với thừa số thứ nhất

		// Dịch phải cụm [bigTemp, bigMul, check]
		check = bigMul.arrBits[1] & 1;
		
		bigMul = bigMul >> 1;
		bit = bigTemp.arrBits[1] & 1;
		if (((bit == 0) && (bigMul.arrBits[0] < 0)) || (bit && (bigMul.arrBits[0] >= 0)))
			bigMul.arrBits[0] = bigMul.arrBits[0] ^ mask;

		bigTemp = bigTemp >> 1;
	}
	// Trả về kết quả tìm được
	return bigMul;
}

// Hàm định nghĩa toán tử "/"
const QInt QInt::operator / (const QInt& q) const
{
	QInt bigQuo = *this; // Biến lưu thương, khởi gán bằng số bị chia
	QInt bigM = q; // Biến lưu số chia
	QInt bigTemp; // Biến tạm
	int sign = 0; // Biến dấu, khởi gán bằng 0

	// Nếu số bị chia và số chia cùng âm, tìm số đối của mỗi số,
	// bit dấu không thay đổi, do kết quả chắc chắn là một số không âm
	if (bigQuo.arrBits[0] < 0 && bigM.arrBits[0] < 0)
	{
		bigQuo = bigQuo.findTwo_Comp();
		bigM = bigM.findTwo_Comp();
	}
	// Nếu số bị chia âm (ngầm hiểu số chia dương),
	// gán số bị chia cho số đối của nó, bit dấu bằng 1
	if (bigQuo.arrBits[0] < 0)
	{
		bigQuo = bigQuo.findTwo_Comp();
		sign = 1;
	}
	// Nếu số chia âm (ngầm hiểu số bị chia không âm),
	// gán số chia cho số đối của nó, bit dấu bằng 1
	if (bigM.arrBits[0] < 0)
	{
		bigM = bigM.findTwo_Comp();
		sign = 1;
	}
	// Vòng lặp gồm 128 lần lặp, tương đương số bit của kiểu QInt là 128
	for (int i = 0; i < 128; i ++)
	{
		// Dịch trái cụm [bigTemp, bigQuo]
		bigTemp = bigTemp << 1;
		bigTemp.arrBits[1] = bigTemp.arrBits[1] ^ (bigQuo.arrBits[0] < 0);
		bigQuo = bigQuo << 1;
		// Gán biến tạm bigTemp cho hiệu chính nó với số chia
		bigTemp = bigTemp - bigM;
		// Nếu biến tạm âm, 
		if (bigTemp.arrBits[0] < 0)
		{
			// Gán bit đầu của thương Quo cho 0
			if (bigQuo.arrBits[1] % 2 != 0)
				bigQuo.arrBits[1] = bigQuo.arrBits[1] ^ 1;
			// Gán biến tạm cho tổng của nó với số chia
			bigTemp = bigTemp + bigM;
		}
		// Ngược lại
		else
			// Gán bit đầu của thương bigQuo cho 1
			if (bigQuo.arrBits[1] % 2 == 0)
				bigQuo.arrBits[1] = bigQuo.arrBits[1] ^ 1;

	}
	// Nếu bit dấu là 1, thì kết quả trả về phải là số âm
	if (sign)
		bigQuo = bigQuo.findTwo_Comp(); // Gán kết quả hiện tại cho số đối của nó
	// Trả về kết quả tìm được
	return bigQuo;
}

// Hàm định nghĩa toán tử "&"
const QInt QInt::operator & (const QInt& q) const
{
	QInt bigAnd;

	bigAnd.arrBits[0] = arrBits[0] & q.arrBits[0];
	bigAnd.arrBits[1] = arrBits[1] & q.arrBits[1];

	return bigAnd;
}

// Hàm định nghĩa toán tử "|"
const QInt QInt::operator | (const QInt& q) const
{
	QInt bigOr;

	bigOr.arrBits[0] = arrBits[0] | q.arrBits[0];
	bigOr.arrBits[1] = arrBits[1] | q.arrBits[1];

	return bigOr;
}

// Hàm định nghĩa toán tử "^"
const QInt QInt::operator ^ (const QInt& q) const
{
	QInt bigXor;

	bigXor.arrBits[0] = arrBits[0] ^ q.arrBits[0];
	bigXor.arrBits[1] = arrBits[1] ^ q.arrBits[1];

	return bigXor;
}

// Hàm định nghĩa toán tử "~"
const QInt QInt::operator ~ () const
{
	QInt bigNot;

	bigNot.arrBits[0] = ~arrBits[0];
	bigNot.arrBits[1] = ~arrBits[1];

	return bigNot;
}

// Hàm định nghĩa toán tử dịch trái "<<"
const QInt QInt::operator << (int num) const
{
	QInt bigSHL = *this; // Khởi gán biến lưu kết quả phép dịch trái cho số cần dịch trái

	// Điều kiện vòng lặp
	// Nếu kết quả dịch trái là biến khác 0 và số lần dịch trái chưa đủ
	// (trường hợp kết quả dịch trái bằng 0 thì không cần dịch nữa)
	while ((bigSHL.arrBits[0] || bigSHL.arrBits[1]) && (num > 0))
	{
		// Dịch trái phần tử thứ nhất của mảng arrBits 1 bit
		bigSHL.arrBits[0] = bigSHL.arrBits[0] << 1;
		// Gán bit đầu của phần tử thứ nhất bằng bit dấu của phần tử thứ 2
		bigSHL.arrBits[0] = bigSHL.arrBits[0] ^ (bigSHL.arrBits[1] < 0);
		// Dịch trái phần tử thứ hai của mảng arrBits 1 bit
		bigSHL.arrBits[1] = bigSHL.arrBits[1] << 1;
		num --; // Giảm số lần dịch 1 đơn vị
	}
	// Trả về kết quả tìm được
	return bigSHL;
}

// Hàm định nghĩa toán tử dịch phải ">>"
const QInt QInt::operator >> (int num) const
{
	QInt bigSHR = *this; // Khởi gán biến lưu kết quả phép dịch phải cho số cần dịch phải
	__int64 mask = 0x8000000000000000; // Biến mặt nạ, khởi gán bằng số âm nhỏ nhất mà kiểu __int64 biểu diễn được
	int bit;

	while (num > 0)
	{
		// Dịch phải phần tử thứ hai của mảng arrBits
		bigSHR.arrBits[1] = bigSHR.arrBits[1] >> 1;
		// Lấy bit đầu của phần tử thứ nhất của mảng arrBits
		bit = bigSHR.arrBits[0] & 1;
		// Gán bit vừa lấy cho bit dấu của phần tử thứ hai của mảng arrBits
		if (((bit == 0) && (bigSHR.arrBits[1] < 0)) || (bit && (bigSHR.arrBits[1] >= 0)))
			bigSHR.arrBits[1] = bigSHR.arrBits[1] ^ mask;
		// Dịch phải phần tử thứ nhất của mảng arrBits
		bigSHR.arrBits[0] = bigSHR.arrBits[0] >> 1;
		// Nếu số sau khi dịch phải bằng 0 hoặc -1 thì dừng vòng lặp
		if (((bigSHR.arrBits[0] == 0) && (bigSHR.arrBits[1] == 0)) || ((bigSHR.arrBits[0] == -1) && (bigSHR.arrBits[1] == -1)))
			break;
		// Giảm số lần dịch phải đi 1 đơn vị
		num --;
	}
	// Trả về kết quả tìm được
	return bigSHR;
}

// Hàm xoay trái
QInt QInt::rotateLeft() const
{
	QInt bigROL = *this; // Biến lưu kết quả phép xoay trái, khởi gán bằng số cần xoay trái
	int sign = 0; // Bit dấu, khởi gán bằng 0

	// Nếu số âm, bit dấu bằng 1
	if (bigROL.arrBits[0] < 0)
		sign = 1;
	// Dịch trái phần tử thứ nhất của mảng arrBits
	bigROL.arrBits[0] = bigROL.arrBits[0] << 1;
	// Gán bit dấu của phần tử thứ hai cho bit đầu của phần tử thứ nhất
	if (bigROL.arrBits[1] < 0)
		bigROL.arrBits[0] = bigROL.arrBits[0] ^ 1;
	// Dịch trái phần tử thứ hai của mảng arrBits
	bigROL.arrBits[1] = bigROL.arrBits[1] << 1;
	// Nếu bit dấu là 1
	if (sign)
		bigROL.arrBits[1] = bigROL.arrBits[1] ^ 1; // Gán bit đầu của phần tử thứ hai của mảng arrBits bằng 1
	// Trả về kết quả tìm được
	return bigROL;
}

// Hàm xoay phải
QInt QInt::rotateRight() const
{
	QInt bigROR = *this; // Biến lưu kết quả phép xoay phải, khởi gán bằng số cần xoay phải
	__int64 mask = 0x8000000000000000;
	int bit;

	// Gán bit bằng bit đầu của phần tử thứ hai của mảng arrBits
	bit = bigROR.arrBits[1] & 1;
	// Dịch phải phần tử thứ hai của mảng arrBits
	bigROR.arrBits[1] = bigROR.arrBits[1] >> 1;

	// Gán bit dấu của phần tử thứ hai của bằng bit đầu của phần tử thứ nhất của mảng arrBits
	if ((bigROR.arrBits[0] & 1) && (bigROR.arrBits[1] >= 0))
		bigROR.arrBits[1] = bigROR.arrBits[1] ^ mask;
	if (((bigROR.arrBits[0] & 1) == 0) && (bigROR.arrBits[1] < 0))
		bigROR.arrBits[1] = bigROR.arrBits[1] ^ mask;
	
	// Dịch phải phần tử thứ nhất của mảng arrBits
	bigROR.arrBits[0] = bigROR.arrBits[0] >> 1;
	
	// Gán bit dấu của phần tử thứ nhất của mảng arrBits bằng bit đầu của phần tử thứ hai tìm được ở trên
	if ((bit && (bigROR.arrBits[0] >= 0)) || ((bit == 0) && (bigROR.arrBits[0] < 0)))
		bigROR.arrBits[0] = bigROR.arrBits[0] ^ mask;
	
	// Trả về kết quả tìm được
	return bigROR;
}

// Hàm cộng hai số thập phân nguyên dương (dạng chuỗi)
// (chuỗi thứ nhất dài hơn hoặc bằng chuỗi thứ hai)
string add(string s1, string s2)
{
	string s = ""; // Chuỗi tổng, khởi gán bằng rỗng
	int len;
	int carry = 0; // Biến nhớ, khởi gán bằng 0
	int sum;

	// Tìm hiệu chiều dài chuỗi 1 với chuỗi 2
	len = s1.length() - s2.length();
	// Thêm ký tự '0' vào đầu chuỗi 2 cho đến khi nào độ dài hai chuỗi bằng nhau
	for (int i = 0; i < len; i ++)
		s2 = '0' + s2;
	// Gán len bằng chiều dài chuỗi 1
	len = s1.length();
	
	for (int i = len - 1; i >= 0; i --)
	{	
		sum = s1[i] - 48 + s2[i] - 48  + carry; // sum bằng tổng của hai ký tự số tại chỉ số i của hai chuỗi s1 và s2
		carry = sum / 10; // Gán carry cho thương của phép chia sum cho 10
		sum = sum % 10; // Gán sum cho dư của phép chia sum cho 10
		s = (char)(sum + 48) + s; // Thêm ký tự số (chuyển số mà sum đang lưu sang dạng ký tự char) vào đầu chuỗi s
	}
	// Nếu biến nhớ bằng 1
	if (carry)
		s = '1' + s; // thì thêm ký tự '1' vào đầu chuỗi s
	// Trả về kết quả tìm được
	return s;
}

// Hàm tìm hiệu hai chuỗi số thập phân nguyên dương
// (số bị trừ lớn hơn số trừ)
string sub(string s1, string s2)
{
	string s = ""; // Chuỗi hiệu, khởi gán bằng rỗng
	int len;
	int carry = 0; // Biến nhớ, khởi gán bằng 0
	int sub;

	// Tìm hiệu độ dài của chuỗi s1 với chuỗi s2
	len = s1.length() - s2.length();
	// Thêm ký tự '0' vào đầu chuỗi s2 cho đến khi độ dài hai chuỗi bằng nhau
	for (int i = 0; i < len; i ++)
			s2 = '0' + s2;
	// Gán len bằng độ dài chuỗi s1
	len = s1.length();

	for (int i = len - 1; i >= 0; i --)
	{	
		sub = s1[i] - s2[i] - carry; // Tìm hiệu của hai ký tự số tại chỉ số i của hai chuỗi

		// Nếu hiệu âm
		if (sub < 0)
		{
			sub = sub + 10; // Tăng hiệu thêm 10 đơn vị
			carry = 1; // Gán biến nhớ bằng 1
		}
		// Ngược lại
		else
			carry = 0; // Gán biến nhớ bằng 0
		// Chuyển sub sang dạng ký tự rồi cộng vào đầu chuỗi s
		s = (char)(sub + '0') + s;
	}
	// Nếu ký tự đầu chuỗi s bằng 0
	// thì xóa ký tự đó cho đến khi ký tự đầu chuỗi s khác ký tự '0'
	while (s[0] == '0')
		s.erase(0, 1);
	// Trả về kết quả tìm được
	return s;
}

// Hàm xuất số kiểu QInt dưới dạng thập phân
void coutDec(const QInt& q)
{
	string sResult = "0"; // Chuỗi kết quả, khởi gán bằng "0"
	string sTemp; // Chuỗi tạm
	__int64 mask = 1;

	// Tìm biểu diễn thập phân của 64 bit đầu (phần tử thứ hai trong mảng arrBits)
	for (int i = 0; i <= 63; i++)
	{
		// Kiểm tra bit thứ i của phần tử thứ hai
		// Nếu bit là 1, gán chuỗi tạm cho "1"
		if (q.arrBits[1] & mask)
		{
			sTemp = "1";
			// Dựa vào vị trí của bit, xác định biểu diễn thập phân của số có bit 1 tại vị trí đó, lưu vào chuỗi tạm
			for (int j = 0; j < i; j++)
				sTemp = add(sTemp, sTemp);
			// Gán chuỗi kết quả cho tổng của nó với chuỗi tạm vừa tìm được ở trên
			sResult = add(sTemp, sResult);
		}
		// Dịch trái biến mặt nạ mask 1 bit
		mask = mask << 1;
	}

	mask = 1; // Gán lại biến mặt nạ mask = 1
	// Thực hiện vòng lặp for tương tự vòng lặp trên
	// i chạy từ bit thứ 64 tới 126
	for (int i = 64; i < 127; i++)
	{
		// Kiểm tra bit thứ i của phần tử thứ nhất
		// Nếu bit là 1, gán chuỗi tạm cho "1"
		if (q.arrBits[0] & mask)
		{
			sTemp = "1";
			// Dựa vào vị trí của bit, xác định biểu diễn thập phân của số có bit 1 tại vị trí đó, lưu vào chuỗi tạm
			for (int j = 0; j < i; j++)
				sTemp = add(sTemp, sTemp);
			// Gán chuỗi kết quả cho tổng của nó với chuỗi tạm vừa tìm được ở trên
			sResult = add(sTemp, sResult);
		}
		// Dịch trái biến mặt nạ mask 1 bit
		mask = mask << 1;
	}
	// Nếu số cần xuất dạng thập phân là số âm
	if (q.arrBits[0] < 0)
	{
		sTemp = "1";
		// Tìm kết quả của phép toán 2^127, gán vào chuỗi tạm
		for (int i = 0; i < 127; i++)
			sTemp = add(sTemp, sTemp);
		// Gán chuỗi kết quả bằng hiệu chuỗi tạm với chuỗi kết quả
		sResult = sub(sTemp, sResult);
		// Thêm ký tứ '-' vào đầu chuỗi kết quả
		sResult = '-' + sResult;
	}
	// Xuất kết quả tìm được
	cout << sResult << endl;
}

// Hàm xuất số kiểu QInt dưới dạng nhị phân
void coutBin(const QInt& q)
{
	unsigned __int64 mask = 0x8000000000000000; // Biến mặt nạ, kiểu nguyên không dấu
	int i;

	// Nếu số âm hoặc biểu diễn nhị phân quá 64 bit
	if (q.arrBits[0] != 0)
	{
		// Tìm vị trí bit 1 đầu tiên tính từ trái sang
		for (i = 0;; i ++)
		{
			if ((q.arrBits[0] & mask) != 0)
				break;
			mask = mask >> 1;
		}

		// Từ vị trí bit 1 đầu tiên đó,
		// xuất từng bit ra màn hình
		
		// Dòng for dưới đây xuất các bit của phần tử thứ nhất của mảng arrBits
		for (i; i < 64; i ++)
		{
			if ((q.arrBits[0] & mask) != 0)
				cout << 1;
			else
				cout << 0;
			mask = mask >> 1;
		}
		// Gán lại mask như lúc khởi gán
		mask = 0x8000000000000000;
		// Dòng for thứ hai xuất tất cả 64 bit của phần tử thứ hai của mảng arrBits
		for (i = 0; i < 64; i ++)
		{
			if ((q.arrBits[1] & mask) != 0)
				cout << 1;
			else
				cout << 0;
			mask = mask >> 1;
		}
	}
	// Ngược lại, nếu số dương và biểu diễn nhị phân không quá 64 bit
	else
	{
		// Nếu số bằng 0, xuất kết quả là 0 và thoát khỏi hàm
		if (q.arrBits[1] == 0)
		{
			cout << 0 << endl;
			return;
		}
		// Tìm vị trí bit 1 đầu tiên tính từ trái sang tại phần tử thứ hai của mảng arrBits
		for (i = 0;; i ++)
		{
			if ((q.arrBits[1] & mask) != 0)
				break;
			mask = mask >> 1;
		}
		// Tại vị trí tìm được bit 1 đầu tiên,
		// từ trái sang, xuất tất cả các bit
		for (i; i < 64; i ++)
		{
			if ((q.arrBits[1] & mask) != 0)
				cout << 1;
			else
				cout << 0;
			mask = mask >> 1;
		}
	}

	cout << endl;
}

// Hàm xuất số kiểu QInt dưới dạng thập lục phân
void coutHex(const QInt& q)
{
	unsigned __int64 mask = 0xF000000000000000; // Biến mặt nạ, kiểu nguyên không dấu
	unsigned __int64 num;
	int i;

	// Nếu số âm hoặc biểu diễn nhị phân quá 64 bit
	if (q.arrBits[0] != 0)
	{
		// Từ trái sang phải, xét từng 4 bit liên tiếp,
		// nếu biểu diễn thập phân của 4 bit đang xét khác 0 thì dừng lại
		for (i = 0;; i = i + 4)
		{
			if (q.arrBits[0] & mask)
				break;
			mask = mask >> 4;
		}
		// Tại vị trí tìm được 4 bit khác 0,
		// từ trái sang phải, xuất số hoặc ký tự tương ứng với 4 bit nhị phân
		for (i; i < 64; i = i + 4)
		{
			num = q.arrBits[0] & mask;
			num = num >> (60 - i);
			mask = mask >> 4;
			if (num > 9)
				cout << (char) (num + 55);
			else
				cout << num;
		}
		// Gán mask bằng giá trị khởi gán lúc ban đầu
		mask = 0xF000000000000000;
		// Từ trái sang phải, xuất số hoặc ký tự tương ứng với từng 4 bit nhị phân
		for (i = 0; i < 64; i = i + 4)
		{
			num = q.arrBits[1] & mask;
			num = num >> (60 - i);
			mask = mask >> 4;
			if (num > 9)
				cout << (char) (num + 55);
			else
				cout << num;
		}
	}
	// Trường hợp số dương và biểu diễn nhị phân không quá 64 bit
	else
	{
		// Nếu số bằng 0, xuất 0 rồi thoát khỏi hàm
		if (q.arrBits[1] == 0)
		{
			cout << 0 << endl;
			return;
		}
		// Từ trái sang phải, tại phần tử thứ hai của mảng arrBits, xét từng 4 bit liên tiếp,
		// nếu biểu diễn thập phân của 4 bit đang xét khác 0 thì dừng lại
		for (i = 0;; i = i + 4)
		{
			if (q.arrBits[1] & mask)
				break;
			mask = mask >> 4;
		}
		// Tại vị trí tìm được 4 bit khác 0,
		// từ trái sang phải, xuất số hoặc ký tự tương ứng với 4 bit nhị phân
		for (i; i < 64; i = i + 4)
		{
			num = q.arrBits[1] & mask;
			num = num >> (60 - i);
			mask = mask >> 4;
			if (num > 9)
				cout << (char) (num + 55);
			else
				cout << num;
		}
	}

	cout << endl;
}

// Phương thức khởi tạo mặc định
// Khởi gán biến kiểu QInt ban đầu bằng 0
QInt::QInt()
{
	arrBits[0] = 0;
	arrBits[1] = 0;
}

QInt::~QInt(void)
{
}