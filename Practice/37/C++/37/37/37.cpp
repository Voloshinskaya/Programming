#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath> 

bool equal(double a, double b, double e = 1E-10);
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

class Vector {

	Point begin;
	Point end;
	double delta = pow(10, -10);

public:
	Vector() {
		begin = Point(0, 0);
		end = Point(1, 0);
	}
	Vector(Point end) : end(end) { begin = Point(0, 0); }
	Vector(Point begin, Point end) : begin(begin), end(end) {}
	Point get_begin() const { return begin; }
	Point get_end() const { return end; }
	bool operator == (const Vector& d) {
		return ((end.get_x() - begin.get_x()) - (d.end.get_x() - d.begin.get_x()) < delta and (end.get_y() - begin.get_y()) - (d.end.get_y() - d.begin.get_y()) < delta);
	}
	Vector operator- () {
		Vector pnt;
		pnt.begin = end;
		pnt.end = begin;
		return pnt;
	}
	Vector operator+ (const Vector& d) {
		Vector pnt;
		pnt.begin = begin;
		pnt.end = Point(end.get_x() + d.end.get_x() - d.begin.get_x(), end.get_y() + d.end.get_y() - d.begin.get_y());
		return pnt;
	}
	Vector operator- (const Vector& d) {
		Vector pnt;
		pnt.begin = begin;
		pnt.end = Point(end.get_x() - d.end.get_x() - d.begin.get_x(), end.get_y() - d.end.get_y() - d.begin.get_y());
		return pnt;
	}
	Vector operator* (double d) {
		Vector pnt;
		pnt.begin = begin;
		pnt.end = Point(begin.get_x() + (end.get_x() - begin.get_x()) * d, begin.get_y() + (end.get_y() - begin.get_y()) * d);
		return pnt;
	}
	double length() {
		return hypot(end.get_x() - begin.get_x(), end.get_y() - begin.get_y());
	}
	double operator* (const Vector& d) {
		double dlen = hypot(d.end.get_x() - d.begin.get_x(), d.end.get_y() - d.begin.get_y());
		double mult_scalar = (length()) * dlen * cos(atan2((end.get_y() - begin.get_y()), (end.get_x() - begin.get_x())) - atan2((d.end.get_y() - d.begin.get_y()), (d.end.get_x() - d.begin.get_x())));
		return mult_scalar;
	}
};


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

double sqr(double a) {
	return a * a;
}

int main()
{
	Vector a(Point(1, 2)), b(Point(-2, 0), Point(-1, 2));


	if (a == b && b == a) cout << "Equality test passed\n";
	else cout << "Equality test failed\n";

	Vector na(Point(-1, -2)), ox(Point(1, 0)), nox(Point(-1, 0)), oy(Point(0, 1)), noy(Point(0, -1));
	if (a == -na && na == -a && -ox == nox && -oy == noy) cout << "Invert test passed\n";
	else cout << "Invert test failed\n";

	if (ox + oy + oy == a && -ox == -a + oy + oy) cout << "Summation test passed\n";
	else cout << "Summation test failed\n";

	if (-ox + oy == oy - ox && -oy + ox == ox - oy) cout << "Subtraction test passed\n";
	else cout << "Subtraction test failed\n";

	if (ox * 3 == ox + ox + ox &&
		oy * 3 == oy + oy + oy &&
		ox * (-3) == -ox - ox - ox &&
		oy * (-3) == -oy - oy - oy) cout << "Multiplication by number test passed\n";
	else cout << "Multiplication by number test failed\n";

	if (equal(ox.length(), 1) &&
		equal(oy.length(), 1) &&
		equal((ox * 3 + oy * 4).length(), 5)) cout << "Length test passed\n";
	else cout << "Length test failed\n";

	if (equal(ox * ox, sqr(ox.length())) &&
		equal(oy * oy, sqr(oy.length())) &&
		equal((ox * 3 + oy * 4) * (ox * 3 + oy * 4), sqr((ox * 3 + oy * 4).length()))) cout << "Multiplication by Vector test passed\n";
	else cout << "Multiplication by Vector test failed\n";
}

bool equal(double a, double b, double e) {
	if (-e < a - b && a - b < e) return true;
	else return false;
}

