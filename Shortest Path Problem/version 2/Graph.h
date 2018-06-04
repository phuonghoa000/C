# include "STREET.h"
# ifndef _GRAPH_H
# define _GRAPH_H
# include <stack>
# define INF -1
# pragma once

class CGRAPH
{
private:
	string* place; // Danh sách tên các địa điểm
	CSTREET** L; // Ma trận đường đi
	int n; // Số địa điểm
public:
	// Hàm đọc file biểu diễn ma trận mô tả mối liên kết giữa các địa điểm
	void readFileStreet();
	// Hàm đọc file biểu diễn tên các địa điểm
	void readFilePlace();
	// Hàm làm tròn số thực đến chữ số thập phân thứ 5
	friend float roundNum(float);
	// Hàm ghi đường đi tìm được vào file
	void writeFile(stack<int>, float);
	// Hàm lấy giá trị tương ứng với prior
	float getterValue(int, int, int);
	// Hàm khởi tạo các giá trị chuẩn bị cho thuật toán Dijkstra
	void init(int, int* &, float* &, int* &);
	// Thuật toán tìm đường đi ngắn nhất (nhanh nhất) Dijstra
	bool Dijkstra(int, int, int, int* &, float* &, int* &);
	// Hàm lưu đường đi tìm được vào stack
	void savePath(int, int, int*, stack<int> &);
	// Hàm khởi tạo mặc định
	CGRAPH();
	// Hàm hủy
	~CGRAPH();
};

# endif

