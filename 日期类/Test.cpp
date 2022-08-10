#include "Date.h"

void TestDate1()
{
	Date d1(2022, 7, 24);
	Date d2(2022, 7, 25);
	Date d3(2021, 7, 25);

	cout << (d1 < d2) << endl;
	cout << (d1 < d3) << endl;
	cout << (d1 == d3) << endl;
	cout << (d1 > d3) << endl;
}

void TestDate2()
{
	Date d1(2022, 7, 24);
	(d1 + 4).Print();
	(d1 + 40).Print();// 跨月
	(d1 + 400).Print();// 跨年
	(d1 + 4000).Print(); // 跨闰年
	(d1 + 40000).Print();

	Date ret1 = ++d1; // d1.operator++(&d1)
	Date ret2 = d1++; // d1.operator++(&d2, 0)
}

void TestDate3()
{
	Date d1(2022, 7, 25);
	Date d2(2022, 7, 26);

	// 因为已经把cout和cin重载成全局
	cout << d1 << d2;
	cin >> d1 >> d2;
	cout << d1 << d2;

}

void TestDate4()
{
	Date d1(2022, 7, 25);
	const Date d2(2022, 7, 25);
	d1.Print();
	d2.Print();

	d1 < d2;
	d2 < d1;
}

int main()
{
	TestDate4();
	return 0;
}