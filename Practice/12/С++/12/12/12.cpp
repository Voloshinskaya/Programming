#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	int x;
	int z= 1;
	cout <<"Введите число" << "\n";
	cin >> x;
	int i = 2;
	while (i <= x)
	{
		z = z * i;
		++i;
	}
	cout <<"Факкториал данного числа равен :" <<  z;
	return 0;
}