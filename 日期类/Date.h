#pragma once

#include<iostream>
#include <assert.h>
using namespace std;

class Date
{
	// 友元函数 -- 这个函数内部可以使用Date对象访问私有保护成员
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
public:
	// 获取某年某月的天数
	int GetMonthDay(int year, int month)
	{
		static int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = days[month];
		if (month == 2
			&& ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
		{
			day += 1;
		}

		return day;
	}

	// 检查日期是否合法
	bool CheckDate()
	{
		if (_year >= 1
			&& _month > 0 && _month < 13
			&& _day > 0 && _day <= GetMonthDay(_year, _month))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// 构造会频繁调用，所以直接放在类里面定义作为inline
	Date(int year = 1, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
		assert(CheckDate());
	}

	void Print() const;

	bool operator==(const Date& d) const;
	bool operator!=(const Date& d) const;
	bool operator>(const Date& d) const;
	bool operator>=(const Date& d) const;
	bool operator<(const Date& d) const;
	bool operator<=(const Date& d) const;

	Date operator+(int day) const;//日期 + 天数
	Date& operator+=(int day);
	Date& operator++(); // 前置
	Date operator++(int); // 后置

	Date operator-(int day) const;//日期 - 天数
	Date& operator-=(int day);
	Date& operator--(); // 前置
	Date operator--(int); // 后置

private:
	int _year;
	int _month;
	int _day;
};

// 这两个重载如果定义在类里，左操作数必须是类成员对象
// 调用时不符合我们的习惯，所以定义成全局的重载，
// 流插入重载
inline ostream& operator<<(ostream&  out, const Date& d)
{
	out << d._year << "年" << d._month << "月" << d._day << "日" << endl;
	return out;
}

// 流提取重载
inline istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	assert(d.CheckDate());
	return in;
}