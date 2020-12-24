#include <iostream>
#include <locale>
#include <vector>
#include <math.h>
using namespace std;

struct Student {
	string name = "None";
	int group = 0;
	int mathematics; int physics; int history; int programming;
};

bool operator< (Student& a, Student& b) {
	return a.name < b.name;
}
bool operator> (Student& a, Student& b) {
	return a.name > b.name;
}

ostream& operator<< (ostream& out, Student student) {
	out << "| ";
	out << student.group << "\t| ";
	out << student.mathematics << "\t| ";
	out << student.physics << "\t| ";
	out << student.history << "\t| ";
	out << student.programming << "\t| ";
	return out;
}

auto BozoSort(vector<Student>& vec, bool d = true) {
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




int main() {
	setlocale(LC_ALL, "");

	cout << "+-----------+-------+------+------+------+------+" << endl;
	cout << "| Name      | Group | Math | Phys | Hist | Prog |" << endl;
	cout << "+-----------+-------+------+------+------+------+" << endl;

	vector<Student> students;


	return 0;
}

