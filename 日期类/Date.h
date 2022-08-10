#pragma once

#include<iostream>
#include <assert.h>
using namespace std;

class Date
{
	// ��Ԫ���� -- ��������ڲ�����ʹ��Date�������˽�б�����Ա
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
public:
	// ��ȡĳ��ĳ�µ�����
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

	// ��������Ƿ�Ϸ�
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

	// �����Ƶ�����ã�����ֱ�ӷ��������涨����Ϊinline
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

	Date operator+(int day) const;//���� + ����
	Date& operator+=(int day);
	Date& operator++(); // ǰ��
	Date operator++(int); // ����

	Date operator-(int day) const;//���� - ����
	Date& operator-=(int day);
	Date& operator--(); // ǰ��
	Date operator--(int); // ����

private:
	int _year;
	int _month;
	int _day;
};

// ��������������������������������������Ա����
// ����ʱ���������ǵ�ϰ�ߣ����Զ����ȫ�ֵ����أ�
// ����������
inline ostream& operator<<(ostream&  out, const Date& d)
{
	out << d._year << "��" << d._month << "��" << d._day << "��" << endl;
	return out;
}

// ����ȡ����
inline istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	assert(d.CheckDate());
	return in;
}