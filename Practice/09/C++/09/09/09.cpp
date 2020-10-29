#include <iostream>
using namespace std;

int main() 
{
	setlocale(LC_ALL, "RГ");
	int h1, h2, m1, m2, x1, x2, t;
	char a;
	cin >> h1 >> a >> m1;
	cin >> h2 >> a >> m2;
	if ((0 < h1) & (h1 < 23)) {
		if ((0 < h2) & (h2 < 59)) {
			if ((0 < m1) & (m1 < 59)) {
				if ((0 < m2) & (m2 < 59)) {
					x1 = 60 * h1 + m1;
					x2 = 60 * h2 + m2;
					t = x1 - x2;
					if (t > 15) {
						cout << "К сожалению, встреча не состоится\n";
					}
					else if (t < -15) { cout << "К сожалению, встреча не состоится\n"; }
					else { cout << "Встреча состоится\n"; }
				}
				else { cout << "Введено неверное время\n"; }
			}
			else { cout << "Введено неверное время\n"; }
		}
		else { cout << "Введено неверное время\n"; }
	}
	else { cout << "Введено неверное время\n"; }
}