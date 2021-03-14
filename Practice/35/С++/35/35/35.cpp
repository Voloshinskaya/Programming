#include <iostream>
using namespace std;
struct IntArray {
    int* data;
    int size;
} arr;

void create(IntArray* arr, int arr_size) {
    int* array = new int[arr_size];
    arr->data = array;
    arr->size = arr_size;
}

void create(IntArray& arr, int arr_size) {
    int* array = new int[arr_size];
    arr.data = array;
    arr.size = arr_size;
}

int get(IntArray* arr, int index) {
    if ((index < 0) || (index >= (*arr).size)) {
        cout << "Index error";
        exit(1);
    }
    return (*arr).data[index];
}

int get(IntArray& arr, int index) {
    if ((index < 0) || (index >= arr.size)) {
        cout << "Index error";
        exit(1);
    }
    return arr.data[index];
}

void set(IntArray* arr, int index, int value) {
    if ((index < 0) || (index >= (*arr).size)) {
        cout << "Index error";
        exit(1);
    }
    (*arr).data[index] = value;
}

void set(IntArray& arr, int index, int value) {
    if ((index < 0) || (index >= arr.size)) {
        cout << "Index error ";
        exit(1);
    }
    set(&arr, index, value);
}

void print(IntArray* arr) {
    cout << "[";
    for (int i = 0; i < (*arr).size; i++)
    {
        cout << (*arr).data[i];
        if (i != (*arr).size - 1)
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void print(IntArray& arr) {
    cout << "[";
    for (int i = 0; i < arr.size; i++)
    {
        cout << arr.data[i];
        if (i != arr.size - 1)
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void resize(IntArray* arr, int newSize) {
    int* ald_arr = (*arr).data;
    int  ald_size = (*arr).size;
    create(arr, newSize);

    if (newSize > ald_size) {
        for (int i = 0; i < ald_size; i++) {
            set(arr, i, ald_arr[i]);
        }
        for (int i = ald_size; i < newSize; i++) {
            set(arr, i, 0);
        }
    }
    else {
        for (int i = 0; i < newSize; i++) {
            set(arr, i, ald_arr[i]);
        }
    }
    delete[]ald_arr;
}

void resize(IntArray& arr, int newSize) {
    int* ald_arr = arr.data;
    int  ald_size = arr.size;
    create(arr, newSize);

    if (newSize > ald_size) {
        for (int i = 0; i < ald_size; i++) {
            set(arr, i, ald_arr[i]);
        }
        for (int i = ald_size; i < newSize; i++) {
            set(arr, i, 0);
        }
    }
    else {
        for (int i = 0; i < newSize; i++) {
            set(arr, i, ald_arr[i]);
        }
    }
    delete[]ald_arr;
}

void destroy(IntArray* arr) {
    if ((*arr).data != nullptr) {
        delete[](*arr).data;
        (*arr).data = nullptr;
        (*arr).size = 0;
    }
}

void destroy(IntArray& arr) {
    if (arr.data != nullptr) {
        delete[] arr.data;
        arr.data = nullptr;
        arr.size = 0;
    }
}

int main()
{
    create(arr, 30);
    for (int i = 1; i <= 30; i++)
    {
        set(arr, i - 1, i);
    }
    print(arr);
    resize(arr, 50);
    print(arr);
    resize(arr, 10);
    print(arr);
    destroy(arr);
    return 0;
}
