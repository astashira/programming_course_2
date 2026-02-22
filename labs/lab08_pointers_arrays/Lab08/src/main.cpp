#include <iostream>
#include <ctime>
using namespace std;

// Функция для генерации упорядоченных массивов
void generateOrderedArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i * 5;  // Создаем упорядоченный массив с шагом 5
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Статический массив с индексами
    const int STATIC_SIZE = 10;
    int staticArray1[STATIC_SIZE];

    // Заполнение и вывод
    for (int i = 0; i < STATIC_SIZE; i++) {
        staticArray1[i] = i * i;
        cout << staticArray1[i] << " ";
    }
    cout << endl;

    // Статический массив с указателями
    int staticArray2[STATIC_SIZE];
    int* ptr = staticArray2;

    for (int i = 0; i < STATIC_SIZE; i++) {
        *ptr = i * i;
        cout << *ptr << " ";
        ptr++;
    }
    cout << endl;

    // Динамический массив с индексами
    int* dynamicArray1 = new int[STATIC_SIZE];

    for (int i = 0; i < STATIC_SIZE; i++) {
        dynamicArray1[i] = i * i;
        cout << dynamicArray1[i] << " ";
    }
    cout << endl;

    // Динамический массив с указателями
    int* dynamicArray2 = new int[STATIC_SIZE];
    int* ptr2 = dynamicArray2;

    for (int i = 0; i < STATIC_SIZE; i++) {
        *ptr2 = i * i;
        cout << *ptr2 << " ";
        ptr2++;
    }
    cout << endl;

    // Освобождение памяти
    delete[] dynamicArray1;
    delete[] dynamicArray2;

   
}