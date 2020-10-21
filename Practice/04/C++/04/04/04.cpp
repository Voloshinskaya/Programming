#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL,"rus");
    double a, b;
    cin >> a >> b;
    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';
    cout << "с помощью доп. переменной" << '\n';
    double c;
    c = a;
    a = b;
    b = c;
    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';
    cout << "без доп. переменной" << '\n';
    a = a + b;
    b = a - b;
    a = a - b;
    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';
}
