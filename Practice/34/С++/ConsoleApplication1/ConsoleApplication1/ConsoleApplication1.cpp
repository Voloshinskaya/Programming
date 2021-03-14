#include <iostream>
using namespace std;

void create(int** arr, int arr_size, int arr_start = 0, int arr_step = 0) {
    *arr = new int[arr_size];
    for (int i = 0; i < arr_size; i++) {
        (*arr)[i] = arr_start;
        arr_start = arr_start + arr_step;
    }
}

void sort(int* arr, int arr_size) {
    int i = 1;
    while (i < arr_size) {
        int j = i;
        while (j > 0 and arr[j - 1] > arr[j]) {
            swap(arr[j - 1], arr[j]);
            j -= 1;
        }
        i += 1;
    }
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

void destroy(int* arr) {
    if (arr != nullptr) {
        delete[] arr;
        int* arr = nullptr;
    }
}

int main()
{
    int arr_size, arr_start, arr_step;
    int* arr;

    cin >> arr_size;
    cin >> arr_start;
    cin >> arr_step;

    create(&arr, arr_size, arr_start, arr_step);
    sort(arr, arr_size);
    print(arr, arr_size);

    destroy(arr);

    return 0;
}
