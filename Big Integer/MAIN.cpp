# include "CalculateQInt.h"

void main(int argc, char* argv[])
{
	freopen(argv[1], "rt", stdin); // Mở file để đọc
	freopen(argv[2], "wt", stdout); // Mở file để ghi
	
	vector <CalculateQInt> c; // Mảng lưu danh sách các phép tính toán trên kiểu QInt đọc từ file
	
	readFile(c); // Đọc file, lưu dữ liệu đọc được vào mảng c
	calculate(c); // Tính toán kết quả dựa trên dữ liệu đọc được từ file
	writeFile(c); // Ghi kết quả tìm được vào file
}