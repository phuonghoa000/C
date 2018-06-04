# ifndef _STREET_H
# define _STREET_H
# include <iostream>
# include <string>
# include <cstdlib>
# pragma once
using namespace std;

class CSTREET
{
private:
	string strName; // Tên đường đi
	float fLength; // Chiều dài đường đi
	float fTime; // Thời gian di chuyển trên đoạn đường đi
public:
	friend class CGRAPH;
	// Hàm đọc thông tin đường đi
	void readFile(int);
	// Hàm khởi tạo mặc định
	CSTREET();
	// Hàm hủy
	~CSTREET();
};

# endif