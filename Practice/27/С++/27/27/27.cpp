#include <locale>
#include <iostream>
#include <vector>
using namespace std;

void VectorSortDescendant(vector<int>& v) {
    if (v.size() < 2) return;
    bool NeedSort = true;
    int tmp;
    while (NeedSort) {
        NeedSort = false;
        for (int i = 0; i < v.size() - 1; i++) {
            if (v[i + 1] > v[i]) {
                tmp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = tmp;
                NeedSort = true;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int n, t;
    vector<int> v;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> t;
        v.push_back(t);
        VectorSortDescendant(v);
        if (v.size() > 5) v.erase(v.begin());

        for (int j = 0; j < v.size(); j++)
            cout << v[j] << " ";
        cout << "\n";
    }
    return 0;
}
