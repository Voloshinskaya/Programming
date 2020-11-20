#include <iostream>
#include <iomanip>      // std::setprecision
#include <locale>
#include "fac.h"
#include "sin.h"
#include "comb.h"
using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");

    std::cout << "n\tn!\n";
    for (int i = 1; i <= 10; i++)
    {
        std::cout << std::setprecision(10) << i << "\t" << fac(i) << endl;
    }

    std::cout << "\nx\tsin(x)" << endl;
    for (double i = 0; i <= 3.14159 / 4; i += 3.14159 / 180) {
        std::cout << std::setprecision(4) << i << "\t" << sin(i, 5) << endl;
    }

    std::cout << "\nk\tC(k, 10)" << endl;
    for (int k = 1; k <= 10; k++) {
        std::cout << std::setprecision(4) << k << "\t" << comb(10, k) << endl;
    }

    return 0;
}