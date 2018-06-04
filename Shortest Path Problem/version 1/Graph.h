# include "STREET.h"
# ifndef _GRAPH_H
# define _GRAPH_H
# include <stack>
# define INF -1
# pragma once

class CGRAPH
{
private:
	string* place;
	CSTREET** L;
	int n;
public:
	// Hàm đọc file chứa ma trận mô tả đường đi kết nối các địa điểm
	void readFileStreet();
	// Hàm đọc file tên các địa điểm
	void readFilePlace();
	// Hàm làm tròn tới chữ số thập phân thứ 5
	friend float roundNum(float);
	// Hàm viết đường đi tìm được vào file
	void writeFile(stack<int>, float);
	// Hàm lấy giá trị tương ứng với prior
	float getterValue(int, int, int);
	// Hàm khởi tạo các giá trị chuẩn bị cho thuật toán Dijkstra
	void init(int, int* &, float* &, int* &);
	// Thuật toán tìm đường đi ngắn nhất (nhanh nhất)
	bool Dijkstra(int, int, int, int* &, float* &, int* &);
	// Hàm lưu đường đi vào stack
	void savePath(int, int, int*, stack<int> &);
	// Hàm khởi tạo mặc định
	CGRAPH();
	// Hàm hủy
	~CGRAPH();
};

# endif

