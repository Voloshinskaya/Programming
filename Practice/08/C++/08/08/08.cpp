#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	cout << "Введите первое число :" << "\n";
	double k;
	cin >> k;
	cout << "Выберите необходимую вам операцию :" << "\n";
	int z;
	cout << "1. Сложение" << "\n";
	cout << "2. Вычитание" << "\n";
	cout << "3. Умножение" << "\n";
	cout << "4. Деление" << "\n";
	cin >> z; 
	double l;
	cout << "Введите второе число :" << "\n";
	double h;
	cin >> h;
	
	
	if (z == 1)
	{
		cout << "Результат выражения: ";
		l = k + h;
		cout << l << endl;
	}
	if (z == 2) 
	{
		cout << "Резуьтат выражения: ";
		l = k - h;
		cout << l << endl;
	}
	if (z == 3) 
	{
		cout << "Результат выражения: ";
		l = k * h;
		cout << l << endl;
	}
	if (z == 4)
	{
		cout << "Результат выражения: ";
		l = k / h;
		cout << l << endl;
	}

}