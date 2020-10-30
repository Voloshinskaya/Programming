#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	double x;
	cout << "Введите любое число"<<'\n';
	cin >> x;
	int y, i;
	cout << "Введите целое значение степени"<<'\n';
	cin >> y;
	double z = x;
	for (i = 1; i < y; i++)
	{
		z = z * x;
	}
	cout << z;
}
