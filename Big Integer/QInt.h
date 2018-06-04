# ifndef _QINT_H
# define _QINT_H

# include <iostream>
# include <string>
# pragma once
using namespace std;

class QInt // Kiểu số nguyên lớn QInt (16 bytes)
{
private:
	__int64 arrBits[2]; // dùng mảng 2 phần tử kiểu __int64 (8 bytes) để biểu diễn
public:
	friend class CalculateQInt;
	QInt findTwo_Comp() const; // Hàm tìm bù 2 của một số
	QInt setBit(int, int) const; // Hàm đặt bit cho số kiểu QInt
	friend void div2(string&); // Hàm chia 2 của chuỗi số thập phân
	QInt convertDecToQInt(string) const; // Hàm chuyển chuỗi số thập phân sang kiểu QInt
	QInt convertBinToQInt(string) const; // Hàm chuyển chuỗi số nhị phân sang kiểu QInt
	QInt convertHexToQInt(string) const; // Hàm chuyển chuỗi số thập lục phân sang kiểu QInt
	QInt& operator = (const QInt&); // Hàm định nghĩa toán tử gán '='
	const QInt operator + (const QInt&) const; // Hàm định nghĩa toán tử cộng "+"
	const QInt operator - (const QInt&) const; // Hàm định nghĩa toán tử trừ "-"
	const QInt operator * (const QInt&) const; // Hàm định nghĩa toán tử nhân "*"
	const QInt operator / (const QInt&) const; // Hàm định nghĩa toán tử chia "/"
	const QInt operator & (const QInt&) const; // Hàm định nghĩa toán tử và (and) "&"
	const QInt operator | (const QInt&) const; // Hàm định nghĩa toán từ hoặc (or) "|"
	const QInt operator ^ (const QInt&) const; // Hàm định nghĩa toán tử xor "^"
	const QInt operator ~ () const; // Hàm định nghĩa toán tử not "~"
	const QInt operator << (int) const; // Hàm định nghĩa toán tử dịch trái "<<"
	const QInt operator >> (int) const; // Hàm định nghĩa toán tử dịch phải ">>"
	QInt rotateLeft() const; // Hàm xoay trái
	QInt rotateRight() const; // Hàm xoay phải
	friend string add(string, string); // Hàm tìm tổng hai số nguyên dương (dạng chuỗi)
	friend string sub(string, string); // Hàm tìm hiệu hai số nguyên dương (hiệu số lớn trừ số bé) (dạng chuỗi)
	friend void coutDec(const QInt&); // Hàm xuất số kiểu QInt dưới dạng thập phân
	friend void coutBin(const QInt&); // Hàm xuất số kiểu QInt dưới dạng nhị phân
	friend void coutHex(const QInt&); // Hàm xuất số kiểu QInt dưới dạng thập lục phân
	QInt();
	~QInt(void);
};

# endif