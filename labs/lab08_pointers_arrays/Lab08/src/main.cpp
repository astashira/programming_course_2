#include <iostream>
using namespace std;
struct Node

    //Для 4 задания
{
    int data;
    Node* prev;
    Node* next;
};

Node* Create(int value)
{
    Node* NewNode = new Node;
    NewNode->data = value;
    NewNode->prev = nullptr;
    NewNode->next = nullptr;
    return NewNode;
}
void Append(Node*& Head, Node*& Tail, int value)
{
    Node* NewNode = Create(value);
    if (Head == nullptr) { Head = Tail = NewNode; }
    else
    {
        Tail->next = NewNode;
        NewNode->prev = Tail;
        Tail = NewNode;
    }
}
void Print(Node* Head)
{
    cout << endl;
    Node* here = Head;
    while (here != nullptr)
    {
        cout << here->data << " ";
        here = here->next;
    };
}
void Delete(Node*& Head) {
    Node* current = Head;
    while (current != nullptr) {
        Node* next = current->next;  // запоминаем следующий
        delete current;               // удаляем текущий
        current = next;                // следующий
    }
    Head = nullptr;
}

// Задания 3-4

int main() {
    setlocale(LC_ALL, "Russian");

    // Статический массив с индексами
    const int STATIC_SIZE = 10;
    int staticArray1[STATIC_SIZE];

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
    cout << endl;

    // Освобождение памяти
    delete[] dynamicArray1;
    delete[] dynamicArray2;

   //Часть 2 с объединением массивов 
    const int m1 = 11;
    const int m2 = 13;
    const int m3 = m1 + m2;

    int mas1 [m1] = {1, 4, 12, 15, 16, 18, 19, 21, 24, 29, 31};
    int mas2 [m2] = {5, 7, 10, 17, 23, 27, 30, 35, 36, 39, 40, 41, 43};
    int* ar1 = new int[m1];
    int* ar2 = new int[m2];
    int* ar3 = new int[m3];

    for (int i = 0; i < m1; i++) {
        ar1[i] = mas1[i];
    }
    for (int i = 0; i < m2; i++) {
        ar2[i] = mas2[i];

    }

    int a = 0, s = 0, d = 0;

    while (a < m1 && s < m2) {
        if (ar1[a] < ar2[s]) {
            *(ar3 + d) = ar1[a];
            a++;
        }
        else {
            *(ar3 + d) = ar2[s];
            s++;
        }
        d++;
    }
    while (a < m1) {
        *(ar3 + d) = ar1[a];
        a++;
        d++;
    }
    while (s < m2) {
        *(ar3 + d) = ar2[s];
        s++;
        d++;
    }
    for (int i = 0; i < m3; i++) {
        cout << ar3[i] << " ";
    }

    delete[] ar1;
    delete[] ar2;
    delete[] ar3;


    Node* Head = nullptr;             
    Node* Tail = nullptr;              

    for (int i = 0; i < 10; i++) {
        Append(Head, Tail, i);         
    }
    cout << endl;
    Print(Head);                       

    Delete(Head);
}