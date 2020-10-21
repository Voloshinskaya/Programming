#include <iostream>
using namespace std;
int main()
{
    double a = 9.8;
    double x0, v0, t0, xt;
    cout << "x0 = ";
    cin >> x0;
    cout << "v0 = ";
    cin >> v0;
    cout << "t0 = ";
    cin >> t0;
    cout << "1 sposob" << '\n';
    xt = a * t0 * t0 / 2;
    cout << "x(t) = " << xt << '\n';
    cout << "2 sposob" << '\n';
    xt = 1 / 2 * a * t0 * t0;//второй способ не подходит т.к. в начале выполняется деление 1 на 2 (1/2) получаем 0,5
                             //далее числа после запятой отбрасываются и все произведение становится равно 0
    cout << "x(t) = " << xt; 
}
