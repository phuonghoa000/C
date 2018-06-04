# pragma warning (disable: 4996)
# ifndef _CALCULATEQINT_H
# define _CALCULATEQINT_H

# include "QInt.h"
# include <vector>
# pragma once

class CalculateQInt
{
private:
	QInt q1; // Toán hạng 1
	QInt q2; // Toán hạng 2
	QInt qResult; // Biến lưu kết quả phép toán
	int num1; // Hệ số 1
	int num2; // Hệ số 2
	string sOper; // Toán tử
public:
	void input(); // Hàm đọc phép toán (của một dòng) trên file
	friend void readFile(vector <CalculateQInt> &); // Hàm đọc file
	friend void writeFile(vector <CalculateQInt>);  // Hàm ghi file
	friend void calculate(vector <CalculateQInt> &); // Hàm tính toán phép toán
	CalculateQInt();
	~CalculateQInt(void);
};

# endif