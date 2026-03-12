//1 задание (10_10.../10_9_...) 


#include <iostream>
#include <cstdlib>
using namespace std;

// упаковка
void pack(int arr[], int N, unsigned char packed[]) {
    for (int i = 0; i < N; i++) {
        packed[i] = arr[i]; // значение в байт
    }
}

// распаковка
void unpack(unsigned char packed[], int N, int restored[]) {
    for (int i = 0; i < N; i++) {
        restored[i] = packed[i]; // из байта в int
    }
}

void fillRandom(int arr[], int N) {
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 18; 
    }
}

int main() {
    srand(time(NULL)); 
    const int N = 12; 
    int arr[N];
    int restored[N] = { 0 };
    unsigned char packed[N];

    fillRandom(arr, N);

    pack(arr, N, packed);

    unpack(packed, N, restored);

    cout << "1.0: ";
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "1.1:  ";
    for (int i = 0; i < N; i++) {
        cout << restored[i] << " ";
    }
    cout << endl;
    cout << endl;
    cout << N * sizeof(int) << " " << N * sizeof(unsigned char) << endl;
    
    

    return 0;
}