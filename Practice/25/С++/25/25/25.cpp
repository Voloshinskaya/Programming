#include <iostream>
#include <locale>
#include <vector>
#include <math.h>
using namespace std;

auto BozoSort(int& a, int& b, int& c, bool d = true) {
	srand(time(NULL));
	int rand_num, tmp;

	if (d) {
		while (true) {
			rand_num = rand() % 3;
			if (rand_num == 0) {
				tmp = a; a = b; b = tmp;
			}
			else if (rand_num == 1) {
				tmp = a; a = c; c = tmp;
			}
			else {
				tmp = b; b = c; c = tmp;
			}
			if ((a <= b) && (b <= c)) break;
		}
	}
	else
	{
		while (true) {
			rand_num = rand() % 3;

			if (rand_num == 0) {
				tmp = a; a = b; b = tmp;
			}
			else if (rand_num == 1) {
				tmp = a; a = c; c = tmp;
			}
			else {
				tmp = b; b = c; c = tmp;
			}

			if ((a >= b) && (b >= c)) break;
		}

	}
}

auto BozoSort(vector<int>& vec, bool d = true) {
	srand(time(NULL));
	bool sorted = false;
	int change1, change2, tmp;

	while (!sorted) {
		change1 = rand() % vec.size();
		change2 = rand() % vec.size();
		while (change1 == change2) {
			change1 = rand() % vec.size();
			change2 = rand() % vec.size();
		}
		tmp = vec[change1];
		vec[change1] = vec[change2];
		vec[change2] = tmp;

		sorted = true;
		for (int i = 0; i < vec.size() - 1; i++) {
			if (d) { if (vec[i] > vec[i + 1]) { sorted = false; break; } }
			else { if (vec[i] < vec[i + 1]) { sorted = false; break; } }
		}
	}
}

auto BozoSort(vector<vector<int>>& vec, bool d = true) {
	srand(time(NULL));
	bool sorted = false;
	int x1, y1, x2, y2, x_ald, y_ald, tmp;

	while (!sorted) {
		x1 = rand() % vec.size();
		y1 = rand() % vec.size();
		x2 = rand() % vec.size();
		y2 = rand() % vec.size();

		while ((x1 == x2) && (y1 == y2)) {
			x1 = rand() % vec.size();
			y1 = rand() % vec.size();
			x2 = rand() % vec.size();
			y2 = rand() % vec.size();
		}

		tmp = vec[y1][x1];
		vec[y1][x1] = vec[y2][x2];
		vec[y2][x2] = tmp;

		sorted = true;
		tmp = vec[0][0];
		for (int i = 0; i < vec.size(); i++) {

			for (int j = 0; j < vec[i].size(); j++) {
				if (d) { if (tmp > vec[i][j]) { sorted = false; break; } }
				else { if (tmp < vec[i][j]) { sorted = false; break; } }
				tmp = vec[i][j];
			}
			if (!sorted) break;
		}
	}
}


void main() {
	setlocale(LC_ALL, "Russian");

	int n;
	vector<int> raw_vector;

	while (true) {
		cin >> n;
		if (n < 4) {
			cout << "ошибка ввода 1.\n";
			cin.clear();
			cin.ignore(32767, '\n');
			continue;
		}

		int tmp;
		for (int i = 0; i < n; i++) {
			cin >> tmp;
			raw_vector.push_back(tmp);
		}

		if (cin.fail()) {
			cout << "ошибка ввода 1.\n";
			cin.clear();
			cin.ignore(32767, '\n');
			continue;
		}
		break;
	}

	// 1d по возрастанию
	vector<int> a1(raw_vector); // копия 1d вектора, чтоб не менять исходняе данные
	BozoSort(a1);
	for (int i = 0; i < a1.size(); i++) { cout << a1[i] << " "; } cout << "\n";

	// 1d по убыванию
	a1 = raw_vector;
	//vector<int> a1(raw_vector);
	BozoSort(a1, false);
	for (int i = 0; i < a1.size(); i++) { cout << a1[i] << " "; } cout << "\n";

	// 2d по возрастанию
	vector<vector<int>> a2;    // создаём 2d вектор
	int q = sqrt(raw_vector.size());
	int z = 0;
	for (int i = 0; i < q; i++) {
		vector<int> v;
		for (int j = 0; j < q; j++) {
			v.push_back(raw_vector[z]);
			z += 1;
		}
		a2.push_back(v);
	}
	BozoSort(a2);

	// 2d по убыванию
	for (int i = 0; i < a2.size(); i++) {
		for (int j = 0; j < a2[i].size(); j++)
			cout << a2[i][j] << " ";
	}
	cout << "\n";

	a2.clear();
	z = 0;
	for (int i = 0; i < q; i++) {
		vector<int> v;
		for (int j = 0; j < q; j++) {
			v.push_back(raw_vector[z]);
			z += 1;
		}
		a2.push_back(v);
	}
	BozoSort(a2, false);
	for (int i = 0; i < a2.size(); i++) {
		for (int j = 0; j < a2[i].size(); j++)
			cout << a2[i][j] << " ";
	}
	cout << "\n";

	// 3 ints по возрастанию
	int a = raw_vector[0], b = raw_vector[1], c = raw_vector[2];
	BozoSort(a, b, c);
	cout << a << " " << b << " " << c << "\n";

	// 3 ints по убыванию
	a = raw_vector[0], b = raw_vector[1], c = raw_vector[2];
	BozoSort(a, b, c, false);
	cout << a << " " << b << " " << c << "\n";
}
