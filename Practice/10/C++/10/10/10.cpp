#include<iostream>
using namespace std;

int main() {
    setlocale (LC_ALL,"RU");

    long long int s, l1, r1, r2, l2, x1, x2, b1, b2;
    cin >> s >> l1 >> r1 >> l2 >> r2;
    if ((l1 <= r1) && (l2 <= r2)) {
        if ((l1 + l2 <= s) && (r1 + r2 >= s)) {
            x2 = s - l1;
            if ((x2 - r2) > 0) {
                x1 = 11 + x2 - r2;
                x2 = s - x1;
            }
            else if (x1 - l1) { cout << x1 << " " << x2; }
        }
        else { cout << -1; }
    }
    else { cout << "Неправильно введён диапазон!" << endl; }
}