#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	cout << "Введите первое число \n";
	double k;
	cin >> k;
	cout << "Введите второе число \n";
	double h;
	cin >> h;
	cout << "Выберите операцию:\n";
	int z;
	cout << "1. Сложение\n";
	cout << "2. Вычитание\n";
	cout << "3. Умножение\n";
	cout << "4. Деление\n";
	double l;
	cin >> z;
	if (z == 1) {
		cout << "Ответ: ";
		l = k + h;
		cout << l << endl;
	}
	if (z == 2) {
		cout << "Ответ: ";
		l = k - h;
		cout << l << endl;
	}
	if (z == 3) {
		cout << "Ответ: ";
		l = k * h;
		cout << l << endl;
	}
	if (z == 4) {
		cout << "Ответ: ";
		l = k / h;
		cout << l << endl;
	}

}