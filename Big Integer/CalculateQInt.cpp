#include "CalculateQInt.h"

// Hàm đọc từng thành phần của phép toán trên một dòng của file
void CalculateQInt::input()
{
	// Khai báo và khởi gán rỗng cho hai chuỗi tạm
	// phục vụ cho việc đọc file
	string s1 = "";
	string s2 = "";
	
	__int64 pos; // Biến lưu vị trí đọc của con trỏ trỏ đến phần tử có thể đọc dữ liệu

	cin >> num1; // Đọc hệ số 1
	cin >> s1; // Đọc chuỗi

	// Nếu chuỗi s1 lưu các toán tử 1 ngôi (~ (not), ror (xoay phải), rol (xoay trái)
	if (s1 == "~" || s1 == "ror" || s1 == "rol")
	{
		sOper = s1; // thì chuỗi s1 chính là toán tử của phép toán, thực hiện phép gán để lưu toán tử vào chuỗi sOper
		cin >> s1; // Đọc chuỗi tiếp theo từ file, chuỗi này lưu toán hạng của phép toán
	}
	// Các trường hợp khác
	else
	{
		// Đọc toán tử từ file
		cin >> sOper;
		// Nếu chuỗi sOper không phải là toán tử mà là toán hạng
		// thì đây là phép toán chuyển toán hạng từ hệ số a (2, 10, 16) sang hệ số khác
		if ((sOper[0] >= '0' && sOper[0] <= '9') || (sOper[0] >= 'A' && sOper[0] <= 'F') || (sOper[0] == '-' && sOper.length() > 1))
		{
			// Khi đó, chuỗi s1 lúc đầu lưu hệ số thứ 2
			// Chuyển đổi ký tự sang kiểu nguyên bằng hàm atoi và lưu vào biến num2
			num2 = atoi(&s1[0]);
			s1 = sOper;
			sOper = "";
		}
		// Nếu chuỗi sOper là toán tử dịch trái (<<) hoặc dịch phải (>>)
		else
			if ((sOper == ">>") || (sOper == "<<"))
				cin >> num2; // Đọc số hạng (kiểu int)
			// Nếu chuỗi sOper là toán tử hai ngôi (+, -, *, /,...)
			else
				cin >> s2; // Đọc chuỗi toán hạng thứ 2
	}

	// Dựa vào hệ số thứ 1, xác định chuỗi s1 biểu diễn số ở hệ số nào
	// gọi hàm thích hợp để chuyển chuỗi số s1 sang kiểu QInt và lưu ở toán hạng thứ 1 (q1)
	switch (num1)
	{
	case 2: q1 = q1.convertBinToQInt(s1); break;
	case 10: q1 = q1.convertDecToQInt(s1); break;
	case 16: q1 = q1.convertHexToQInt(s1);
	}

	// Nếu phép toán tính toán đối với toán tử hai ngôi,
	// tức là chuỗi s1 khác rỗng,
	// dựa vào hệ số thứ 1, xác định hệ số của chuỗi số s2
	// và gọi hàm thích hợp để chuyển sang kiểu QInt và lưu ở toán hạng thức 2 (q2)
	if (s2 != "")
	{
		switch (num1)
		{
		case 2: q2 = q2.convertBinToQInt(s2); break;
		case 10: q2 = q2.convertDecToQInt(s2); break;
		case 16: q2 = q2.convertHexToQInt(s2);
		}
	}

	pos = cin.tellg();  // Cung cấp vị trí hiện tại của con trỏ trong file
	cin.seekg(pos + 1); // Di chuyển con trỏ tới vị trí kế tiếp trong file
}

// Hàm đọc file
void readFile(vector <CalculateQInt> &list)
{
	char check[10]; // Khai báo biến kiểm tra việc đọc file
	list.resize(0); // Khởi tạo số phần tử ban đầu của list là 0
	
	// Đọc file
	
	do
	{
		CalculateQInt temp; // Khai báo một biến tạm để lưu các thành phần của phép toán
		temp.input(); // Đọc dữ liệu trên dòng mà con trỏ để đọc file đang trỏ tới, lưu vào biến tạm
		list.push_back(temp); // Thêm biến tạm vào list (danh sách các phép toán)
		__int64 pos = cin.tellg(); // Cho biết vị trí hiện tại của con trỏ để đọc file
		cin.seekg(pos - 1); // Di chuyển con trỏ về vị trí liền trước		
	}
	// Điều kiện đọc file (chưa tới cuối file, tức con trỏ khác NULL)
	while (gets(check) != NULL);
}

// Hàm ghi kết quả vào file
void writeFile(vector <CalculateQInt> list)
{
	int check; // Khai báo biến kiểm tra, dùng để lưu hệ số của kết quả sẽ ghi vào file

	for (unsigned int i = 0; i < list.size() ; i ++)
	{
		check = list[i].num1; // Gán check cho hệ số thứ 1 của phép toán
		// Nếu phép toán là chuyển đổi hệ số thì gán check cho hệ số thứ 2
		// Điều kiện kiểm tra là hệ số thứ 2 (num2) khác 0 và toán tử không phải là dịch trái hoặc dịch phải
		// (do biến num2 ở các phép dịch trái, dịch phải dùng để lưu số lần dịch bit
		if (list[i].num2 != 0 && list[i].sOper != "<<" && list[i].sOper != ">>")
			check = list[i].num2;
		
		// Dựa vào biến check, xuất kết quả với hệ số tương ứng
		switch (check)
		{
		case 2: coutBin(list[i].qResult); break;
		case 10: coutDec(list[i].qResult); break;
		case 16: coutHex(list[i].qResult);
		}
	}
}

// Hàm tính toán kết quả của phép toán
void calculate(vector <CalculateQInt> &list)
{
	for (unsigned int i = 0; i < list.size(); i ++)
		// Nếu chuỗi toán tử khác rỗng
		if (list[i].sOper != "")
		{
			// Lấy ký tự cuối của chuỗi toán tử
			char c = list[i].sOper[list[i].sOper.length() - 1];
			// Dựa vào ký tự vừa lấy, thực hiện phép toán tương ứng
			switch (c)
			{
			case '+': list[i].qResult = list[i].q1 + list[i].q2; break;
			case '-': list[i].qResult = list[i].q1 - list[i].q2; break;
			case '*': list[i].qResult = list[i].q1 * list[i].q2; break;
			case '/': list[i].qResult = list[i].q1 / list[i].q2; break;
			case '&': list[i].qResult = list[i].q1 & list[i].q2; break;
			case '|': list[i].qResult = list[i].q1 | list[i].q2; break;
			case '^': list[i].qResult = list[i].q1 ^ list[i].q2; break;
			case '~': list[i].qResult = ~list[i].q1; break;
			case '<': list[i].qResult = list[i].q1 << list[i].num2; break; // Phép dịch trái
			case '>': list[i].qResult = list[i].q1 >> list[i].num2; break; // Phép dịch phải
			case 'r': list[i].qResult = list[i].q1.rotateRight(); break; // Phép xoay phải
			case 'l': list[i].qResult = list[i].q1.rotateLeft(); // Phép xoay trái
			}
		}
		// Nếu là phép toán chuyển đổi hệ số
		else
			list[i].qResult = list[i].q1; // Gán kết quả bằng toán hạng thứ 1
}

// Phương thức khởi tạo mặc định
// Mặc định các giá trị ban đầu trong lớp Calculate
// bằng 0 (kiểu nguyên), bằng rỗng (kiểu chuỗi)
CalculateQInt::CalculateQInt()
{
	num1 = 0;
	num2 = 0;
	sOper = "";
}


CalculateQInt::~CalculateQInt(void)
{
}