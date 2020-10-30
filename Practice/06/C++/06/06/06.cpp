#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");

	double a, b, c, x, x1, x2, D;
	cout << "a = ";
	cin >> a;
	cout << "b = "; 
	cin >> b;
	cout << "c = "; 
	cin >> c;

	D = b * b - 4 * a * c;
	x1 = (-b - sqrt(D)) / (2 * a);
	x2 = (-b + sqrt(D)) / (2 * a);
	if (D > 0 && a != 0 && b != 0 && c != 0){
		cout << "x1 = " << x1 << endl;
		cout << "x2 = " << x2 << endl;
	}
	if (D == 0) // имеем только один корень
	{
		cout << "x =" << (-b) / (2 * a) << "\n";
	}
	if (a == 0) // имеем дело с линейным уравнением
	{
		cout << "x = " << -c / b << "\n";
	}
	if (b == 0) // у нас неполное крадратное уравнение
	{
		cout << "x = " << -c / a;
	}
	if (c == 0) 
	{
		cout << "x1 = 0" << "\n";
		cout << "x2 = " << -b / a;
	}
	if (D < 0 && a != 0 && b != 0 && c != 0)
	{
		cout << "Упс! Действительных корней нет...";
	}
}
