#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath> 
using namespace std;

enum Cords { Cartesian, Polar };
const double PI = 3.141592653589793;

class Point {

private:
	static const double delta;
	double x, y, r, phi;

	void CaltulatePolar() {
		this->r = hypot(this->x, this->y);
		this->phi = atan2(this->y, this->x);
	}

	void CaltulateCartesian() {
		this->x = this->r * cos(this->phi);
		this->y = this->r * sin(this->phi);
	}

public:
	Point(double a1 = 0, double a2 = 0, Cords coord_system = Cartesian) {
		if (coord_system == Cartesian) {	// Cartesian
			this->x = a1;
			set_y(a2);
		}
		else {								// Polar
			this->r = a1;
			set_phi(a2);
		}
	}

	bool operator == (Point& Other) { // const 
		return (abs(this->x - Other.get_x()) < delta and
			abs(this->y - Other.get_y()) < delta);
	}

	bool operator != (Point& Other) { // const 
		return not (abs(this->x - Other.get_x()) < delta and
			abs(this->y - Other.get_y()) < delta);
	}

	double get_x()   const { return x; }

	double get_y()   const { return y; }

	void set_x(double x_) {
		this->x = x_;
		CaltulatePolar();
	}

	void set_y(double y_) {
		this->y = y_;
		CaltulatePolar();
	}

	double get_r()   const { return r; }

	double get_phi() const { return phi; }

	void set_r(double r_) {
		this->r = r_;
		CaltulateCartesian();
	}

	void set_phi(double phi) {
		this->phi = phi;
		CaltulateCartesian();
	}


};
const double Point::delta = pow(10, -10);

std::ostream& operator<< (ostream& out, Point& point) { //const 
	return out << "(" << point.get_x() << "," << point.get_y() << ")";
}

std::istream& operator>> (istream& st, Point& point) {
	string input;
	st >> input;
	std::size_t pos1 = input.find('(') + 1;
	std::size_t pos2 = input.find(',');
	std::size_t pos3 = input.find(')') - 1;

	if ((pos1 == string::npos) || (pos2 == string::npos) || (pos3 == string::npos)) {
		return st;
	}

	point.set_x(stod(input.substr(pos1, pos2 - pos1)));
	point.set_y(stod(input.substr(pos2 + 1, pos3 - pos2)));

	return st;
}


int main() {
	std::vector<Point> original;
	std::ifstream fin("data.txt");
	if (!fin.is_open()) {
		std::cout << "Can't open file" << std::endl;
		return 1;
	}
	else {
		while (!fin.eof()) {
			Point p;
			fin >> p;
			fin.ignore(2); // Точки разделены двумя символами ", "
			original.push_back(p);
		}
		fin.close();
	}

	std::vector<Point> simulacrum(original);
	for (auto& p : simulacrum) {
		std::cout << p;
		p.set_x(p.get_x() + 10);
		p.set_phi(p.get_phi() + 180 * PI / 180);
		p.set_y(-p.get_y());
		p.set_x(-p.get_x() - 10);
		std::cout << p << std::endl;
	}

	if (std::equal(original.begin(), original.end(), simulacrum.begin()))
		std::cout << "\nIt works!\n";
	else
		std::cout << "\nIt not works!\n";
}