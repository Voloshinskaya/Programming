#include <iostream>
using namespace std;
int main()
{
    int x;
    int y;
    cout << "int, int" << '\n';
    cin >> x >> y;
    cout << x + y << '\n'; 
    cout << x - y << '\n';
    cout << x * y << '\n';
    cout << x / y << '\n';
    double c;
    double f;
    cout << "double, double" << '\n';
    cin >> c >> f;
    cout << c + f << '\n';
    cout << c - f << '\n';
    cout << c * f << '\n';
    cout << c / f << '\n';
    cout << "int, double" << '\n';
    cout << x + f << '\n';
    cout << x - f << '\n';
    cout << x * f << '\n';
    cout << x / f << '\n';
    cout << "double, int" << '\n';
    cout << c + y << '\n';
    cout << c - y << '\n';
    cout << c * y << '\n';
    cout << c / y << '\n';
}
