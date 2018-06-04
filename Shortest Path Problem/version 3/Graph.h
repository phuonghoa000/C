#include "STREET.h"
#include "POINT.h"
#ifndef _GRAPH_H
#define _GRAPH_H
#define INF -1
#include <stack>
#pragma once

class CGRAPH
{
private:
	string* place; // Danh sách các địa điểm
	CPOINT* pointPlace; // Tọa độ các địa điểm
	CSTREET** L; // Ma trận thể hiện mối liên kết giữa các địa điểm
	int n; // Số địa điểm
public:
	friend class CUndirectedGraph;
	// Hàm đọc thông tin các con đường
	void readFileStreet();
	// Hàm đọc tên các địa điểm
	void readFilePlace();
	// Hàm đọc tọa độ các địa điểm
	void readFileGPSS();
	// Hàm đọc các địa điểm có trong file
	void readFileStreetToVisit(int* &a, int &num);
	// Hàm ghi đường đi tìm được vào file
	void writeFile(stack<int>);
	// Hàm khởi tạo các giá trị ban đầu chuẩn bị cho thuật toán Dijkstra
	void init(int, int* &, float* &, int* &);
	// Thuật toán Dijkstra tìm đường đi ngắn nhất
	bool Dijkstra(int, int, int* &, float* &, int* &);
	// Hàm lưu đường đi ngắn nhất vào stack
	void savePath(int, int, int*, stack<int> &);
	// Hàm khởi tạo mặc định
	CGRAPH();
	// Hàm hủy
	~CGRAPH();
};

#endif

