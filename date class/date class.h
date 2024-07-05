#include <iostream>

class date
{
public:
	date(int year, int month, int day);

	date(const date& d);

	int GetMonthDay(int year, int month);

	int GetDay(int year, int month, int day);

	void print() const;

	bool operator==(const date& d) const;

	bool operator<(const date& d) const;

	bool operator<=(const date& d) const;

	bool operator>(const date& d) const;

	bool operator>=(const date& d) const;

	date& operator=(const date d) ;

	date operator+( int day);

	date operator-( int day);

	date& operator+=(int day);

	date& operator-=(int day);

	int operator-(const date& d); //日期-日期 输出天数
	
	date& operator--();//前置减减
	
	date operator--(int);//后置减减
	
	date& operator++();//前置++
	
	date operator++(int);//后置++
	

private:
	int _year;
	int _month;
	int _day;
};