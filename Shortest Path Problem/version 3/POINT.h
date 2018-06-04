#include <iostream>
#pragma once
using namespace std;

class CPOINT
{
private:
	float fLong; // Kinh độ
	float fLat; // Vĩ độ
public:
	friend class CGRAPH;
	friend class CUndirectedGraph;
	// Đọc thông tin điểm
	void input();
	// Tìm khoảng cách giữa hai điểm
	float findDistance(CPOINT p);
	// Hàm khởi tạo mặc định
	CPOINT(void);
	// Hàm hủy
	~CPOINT(void);
};

