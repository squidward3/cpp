#include "date class.h"

date::date(int year = 0, int month = 1, int day = 1)
{
	if (!(year >= 0 && month > 0 && month <= 12 && day <= GetMonthDay(year, month)))
	{
		std::cout << "日期不合法已经替换成默认日期" << std::endl;
		year = 0;
		month = 1;
		day = 1;
	}
	_year = year;
	_month = month;
	_day = day;
}

date::date(const date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

int date:: GetMonthDay(const int year, const int month)
{
	int PreMonthDay[13] = { 0,30,28,31,30,31,30,31,31,30,31,30,31 };
	if (year % 100 != 0 && year % 4 == 0 && month == 2)
	{
		return 29;
	}
	return PreMonthDay[month];
}

int date::GetDay(int year, int month,int day)
{
	int yearday = 0;
	int monthday = 0;
	int totalday = 0;

	for (month -= 1; month >= 1; month--)
	{
		monthday = monthday + GetMonthDay(year, month);
	}
	for (year -= 1; year >= 0; year--)
	{
		if (year % 100 != 0 && year % 4 == 0)
		{
			yearday = yearday + 366;
			continue;
		}
		yearday = yearday + 365;
		continue;
	}
	totalday = yearday + monthday + day;
	return totalday;
}

void date::print()const
{
	std::cout << _year << "-" << _month << "-" << _day << std::endl;
}

bool date::operator==(const date& d)const
{
	if (this->_year == d._year && this->_month == d._month && this->_day == d._day)
	{
		return true;
	}
	return false;
}

bool date::operator<(const date& d)const
{
	if (_year < d._year)
	{
		return true;
	}
	else if (_month < d._month)
	{
		return true;
	}
	else if (_day < d._day)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool date::operator<=(const date& d)const
{
	return *this < d || *this == d;
}

bool date::operator>(const date& d)const
{
	return!(*this < d || *this == d);
}

bool date::operator>=(const date& d)const
{
	return *this > d || *this == d;
}

date& date::operator=(const date d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
	return *this;
}

date date::operator+(int day)//日期+天数
{
	if (day < 0)
	{
		return *this - (-day);
	}
	date ret(*this);
	ret._day = ret._day + day;
	while (ret._day > GetMonthDay(ret._year, ret._month))
	{
		ret._day = ret._day - GetMonthDay(ret._year, ret._month);
		ret._month++;
		if (ret._month > 12)
		{
			ret._year++;
			ret._month = 1;
		}
	}
	return ret;
}

date date::operator-(int day)//日期-天数
{
	if (day < 0)
	{
		return *this + (-day);
	}
	date ret(*this);
	ret._day = ret._day - day;
	while (ret._day <= 0)
	{
		ret._month--;
		if (ret._month <= 0)
		{
			ret._year--;
			ret._month = 12;
		}
		ret._day = ret._day + GetMonthDay(ret._year, ret._month);
	}
	return ret;
}

date& date::operator+=(int day)
{
	*this = *this + day;
	return *this;
}

date& date::operator-=(int day)
{
	*this = *this - day;
	return *this;
}

int date::operator-(const date& d)//日期-日期 输出天数
{
	int day1 = GetDay(_year, _month, _day);
	int day2 = GetDay(d._year, d._month, d._day);
	return day1 - day2;
}
date& date::operator--()//前置减减
{
	*this -= 1;
	return *this;
}

date date::operator--(int)//后置减减
{
	date tmp(*this);
	*this -= 1;
	return tmp;
}

date& date::operator++()//前置++
{
	*this += 1;
	return *this;
}

date date::operator++(int)//后置++
{
	date tmp(*this);
	*this += 1;
	return tmp;
}