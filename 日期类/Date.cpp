#include "Date.h"

// void Date::Print(const Date* const this)
void Date::Print() const
{
	cout << _year << "/" << _month << "/" << _day << endl;
}

bool Date::operator== (const Date& d) const
{
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}

bool Date::operator!=(const Date& d) const
{
	return !(*this == d);
}

bool Date::operator>(const Date& d) const
{
	if (_year > d._year){
		return true;
	}
	else if (_year == d._year && _month > d._month){
		return true;
	}
	else if (_year == d._year && _month == d._month && _day > d._day) {
		return true;
	}
	else{
		return false;
	}
}

bool Date::operator>=(const Date& d) const
{
	return (*this > d) || (*this == d);
}

bool Date::operator<(const Date& d) const
{
	return !(*this >= d);
}

bool Date::operator<=(const Date& d) const
{
	return !(*this > d);
}

Date Date::operator+(int day) const
{
	Date ret(*this);
	ret += day;
	return ret;
}

Date& Date::operator+=(int day)
{
	// 处理特殊情况
	if (day < 0)
	{
		return *this -= -day;
	}

	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		// 修正日期
		_day -= GetMonthDay(_year, _month);
		++_month;
		if (_month == 13)
		{
			_year++;
			_month = 1;
		}
	}

	return *this;
}

Date& Date::operator++() // 前置
{
	return *this += 1;
}

Date Date::operator++(int) // 后置
{
	Date tmp(*this);
	*this += 1;

	return tmp;
}

Date Date::operator-(int day) const
{
	Date ret = *this;
	ret -= day;
	return ret;
}

Date& Date::operator-=(int day)
{
	if (day < 0)
	{
		return *this += -day;
	}

	_day -= day;
	while (_day <= 0)
	{
		--_month;
		if (_month == 0)
		{
			--_year;
			_month = 12;
		}
		// 少了一个月，就给它增加一个月的天数
		_day += GetMonthDay(_year, _month);
	}

	return *this;
}

Date& Date::operator--() // 前置
{
	return *this -= 1;
}

Date Date::operator--(int) // 后置
{
	Date tmp(*this);
	*this -= 1;
	return tmp;
}