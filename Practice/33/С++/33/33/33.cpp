#include <iostream>
using namespace std;

int* create(int arr_size, int arr_start = 0, int arr_step = 0) {

    int* arr_new = new int[arr_size];

    for (int i = 0; i < arr_size; i++) {
        arr_new[i] = arr_start;
        arr_start += arr_step;
    }
    return arr_new;
}

int* sort(int* arr, int arr_size) {
    int i = 1;
    while (i < arr_size) {
        int j = i;
        while (j > 0 and arr[j - 1] > arr[j]) {
            swap(arr[j - 1], arr[j]);
            j -= 1;
        }
        i += 1;
    }
    return arr;
}

int* print(int* arr, int arr_size) {
    cout << "[";
    for (int i = 0; i < arr_size; i++) {
        cout << arr[i];
        if (i < arr_size - 1) {
            cout << ", ";
        }
    }
    cout << "]";
    return arr;
}

int main()
{
    int arr_size, arr_start, arr_step;

    cin >> arr_size;
    cin >> arr_start;
    cin >> arr_step;

    int* arr = create(arr_size, arr_start, arr_step);
    print(sort(arr, arr_size), arr_size);

    delete[] arr;
    return 0;
}