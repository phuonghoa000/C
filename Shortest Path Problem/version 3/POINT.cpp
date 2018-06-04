#include "POINT.h"

// Hàm đọc thông tin điểm
void CPOINT::input()
{
	char c;

	cin >> fLong;
	cin >> c;
	cin >> fLat;
}

// Hàm tìm khoảng cách giữa hai điểm
float CPOINT::findDistance(CPOINT p)
{
	float fDis;

	fDis = sqrt(((fLong - p.fLong) * (fLong - p.fLong)) + ((fLat - p.fLat) * (fLat - p.fLat)));
	return fDis;
}

// Hàm khởi tạo mặc định
CPOINT::CPOINT(void)
{
}

// Hàm hủy
CPOINT::~CPOINT(void)
{
}
