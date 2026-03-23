#include <iostream>
#include <vector>
using namespace std;

int n1;                          
vector<vector<char>> board;      
vector<int> pos;                 
int s= 0;              


bool Safe(int str, int stl) {

    for (int i = 0; i < str; i++) {
        if (board[i][stl] == 'Q') return false;
    }

    // диагональ (вверх-влево)
    for (int i = str - 1, j = stl - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') return false;
    }

    // диагональ (вверх-вправо)
    for (int i = str - 1, j = stl + 1; i >= 0 && j < n1; i--, j++) {
        if (board[i][j] == 'Q') return false;
    }

    return true;
}


void mat(int str) {
    if (str == n1) {  
        s++;

        
        cout << s << ": ";
        cout << endl;


        if (n1 <= 15) {
            for (int i = 0; i < n1; i++) {
                for (int j = 0; j < n1; j++) {
                    if (pos[i] == j)
                        cout << "Q ";
                    else
                        cout << ". ";
                }
                cout << endl;
            }
            cout << endl;
        }
        return;
    }


    for (int stl = 0; stl < n1; stl++) {
        if (Safe(str, stl)) {
            board[str][stl] = 'Q';   
            pos[str] = stl;           
            mat(str + 1);       
            board[str][stl] = '.';    
        }
    }
}

void mat1(int n) {
    n1 = n;
    s = 0;
    board = vector<vector<char>>(n, vector<char>(n, '.'));
    pos = vector<int>(n);

    mat(0);

    cout << "\n all " << s << endl;
}

int n2;                          
int P[21];                       // позиции ферзей P[строка] 
int H[21];                       // столбцы
int R[41];                       // правые диагонали (\)
int L[41];                       // левые диагонали (/)
int s2 = 0;              

void queen(int k) {
    int i, j;

    for (i = 1; i <= n2; i++) {
        if (H[i] == 0 && R[i - k + 21] == 0 && L[i + k] == 0) {
            // Ставим ферзя
            P[k] = i;
            H[i] = 1;
            R[i - k + 21] = 1;
            L[i + k] = 1;

            if (k == n2) {  // нашли решение
                s2++;
                cout << s2 << ": ";
                cout << endl;

                // Визуализация 
                if (n2 <= 15) {
                    for (int row = 1; row <= n2; row++) {
                        for (int col = 1; col <= n2; col++) {
                            if (P[row] == col)
                                cout << "Q ";
                            else
                                cout << ". ";
                        }
                        cout << endl;
                    }
                    cout << endl;
                }
            }
            else {
                queen(k + 1); 
            }

            // Возврат 
            H[i] = 0;
            R[i - k + 21] = 0;
            L[i + k] = 0;
        }
    }
}void kos(int n) {
    n2 = n;
    s2 = 0;

  
    for (int i = 1; i <= n; i++) {
        H[i] = 0;
    }
    for (int i = 2; i <= n + n; i++) {
        R[i] = 0;
        L[i] = 0;
    }

    queen(1);  // начинаем с первой строки

    cout << "\n all " << s2 << endl;
}

int main() {
    int n;

    cout << "K: ";
    cin >> n;

    cout << endl;
    cout << "var 1" << endl;
    mat1(n);
    cout << endl;
    cout << endl;
    cout << "var 2" << endl;
    kos(n);

    return 0;
}