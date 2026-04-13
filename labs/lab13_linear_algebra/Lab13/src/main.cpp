#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <windows.h>

using namespace std;

const double EPS = 1e-9;

void gaussJordan(double** a, int m, int n) {
    int row = 0;
    for (int col = 0; col < n && row < m; col++) {
        int maxRow = row;  //ищем главное значение
        for (int i = row + 1; i < m; i++)
            if (fabs(a[i][col]) > fabs(a[maxRow][col])) maxRow = i;  //выбираем главное значение

        if (fabs(a[maxRow][col]) < EPS) continue; //пропускаем нулевые 

        swap(a[row], a[maxRow]); //фиксируем главную строку

        double div = a[row][col];
        for (int j = col; j <= n; j++) a[row][j] /= div; //начинаем делить на главное числа

        for (int i = 0; i < m; i++) {
            if (i != row && fabs(a[i][col]) > EPS) { //следим, чтобы под раздачу не попала главная строка
                double mult = a[i][col];
                for (int j = col; j <= n; j++) a[i][j] -= mult * a[row][j];
            }
        }
        row++;
    }
}

bool isConsistent(double** a, int m, int n) { // проверка совместности 
    for (int i = 0; i < m; i++) {
        bool allZero = true;
        for (int j = 0; j < n; j++)
            if (fabs(a[i][j]) > EPS) { allZero = false; break; }
        if (allZero && fabs(a[i][n]) > EPS) return false;
    }
    return true;
}

int getRank(double** a, int m, int n) { //ранг матрицы
    int rank = 0;
    for (int i = 0; i < m; i++) {
        bool zeroRow = true;
        for (int j = 0; j < n; j++)
            if (fabs(a[i][j]) > EPS) { zeroRow = false; break; }
        if (!zeroRow) rank++;
    }
    return rank;
}

void printSolution(double** a, int m, int n) {
    if (!isConsistent(a, m, n)) {
        cout << "Система НЕСОВМЕСТНА (решений нет)" << endl;
        return;
    }

    int rank = getRank(a, m, n);

    if (rank < n)
        cout << "\nОБЩЕЕ РЕШЕНИЕ (бесконечно много решений):\n" << endl;
    else
        cout << "\nЕДИНСТВЕННОЕ РЕШЕНИЕ:\n" << endl;

    for (int j = 0; j < n; j++) {
        // ищем строку, где коэффициент при xj = 1
        int pivot = -1;
        for (int i = 0; i < m; i++) {
            if (fabs(a[i][j] - 1.0) < EPS) {
                pivot = i; //нашли, назначили базисной
                break;
            }
        }

        if (pivot == -1) { // свободная переменная
            cout << "x" << j + 1 << " = t" << j + 1 << " (свободная)" << endl;
        }
        else {  // базисная переменная
            cout << "x" << j + 1 << " = " << fixed << setprecision(2) << a[pivot][n];

            for (int k = 0; k < n; k++) {
                if (k != j && fabs(a[pivot][k]) > EPS) { //поиск свободных
                    double coef = -a[pivot][k];  // переносим в правую часть
                    if (coef > 0)
                        cout << " + " << fixed << setprecision(2) << coef << "*t" << k + 1;
                    else
                        cout << " - " << fixed << setprecision(2) << -coef << "*t" << k + 1;
                }
            }
            cout << endl;
        }
    }
}

int main() {
    system("chcp 65001 > nul");

    cout << "   РЕШЕНИЕ СИСТЕМЫ ЛИНЕЙНЫХ УРАВНЕНИЙ" << endl;

    ifstream in("input.txt");

    int m, n;
    in >> m >> n;

    cout << "Размер системы: " << m << " уравнений, " << n << " неизвестных" << endl;

    double** a = new double* [m]; //выделение памяти
    for (int i = 0; i < m; i++) a[i] = new double[n + 1];

    for (int i = 0; i < m; i++)
        for (int j = 0; j <= n; j++)
            in >> a[i][j];
    in.close();

    cout << "\nРасширенная матрица:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            cout << setw(8) << setprecision(2) << a[i][j];
        cout << " | " << setw(8) << setprecision(2) << a[i][n] << endl;
    }

    gaussJordan(a, m, n);

    printSolution(a, m, n);

    ofstream out("output.txt");
    out << "=== РЕЗУЛЬТАТ РЕШЕНИЯ ===" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n; j++)
            out << a[i][j] << " ";
        out << endl;
    }
    out.close();

    //бонус АААААА

    cout << "\nПЕРЕСЕЧЕНИЕ ДВУХ ПРЯМЫХ " << endl;

    double a1, b1, c1, a2, b2, c2;
    cout << "\nВведите первую прямую (a1 b1 c1): ";
    cin >> a1 >> b1 >> c1;
    cout << "Введите вторую прямую (a2 b2 c2): ";
    cin >> a2 >> b2 >> c2;

    double det = a1 * b2 - a2 * b1;

    if (fabs(det) < EPS) {
        if (fabs(a1 * c2 - a2 * c1) < EPS && fabs(b1 * c2 - b2 * c1) < EPS)
            cout << "\nПрямые СОВПАДАЮТ" << endl;
        else
            cout << "\nПрямые ПАРАЛЛЕЛЬНЫ" << endl;
    }
    else {
        double x0 = (b1 * c2 - b2 * c1) / det;  //формулы по крамеру, дет - определитель матрицы
        double y0 = (a2 * c1 - a1 * c2) / det;

        cout << "\nТочка пересечения: (" << fixed << setprecision(2) << x0 << ", " << y0 << ")" << endl;

        double check1 = a1 * x0 + b1 * y0 + c1;
        double check2 = a2 * x0 + b2 * y0 + c2;
        cout << "Проверка: " << check1 << " = 0, " << check2 << " = 0" << endl;

        ofstream gp("plot.gp");
        gp << "set terminal wxt size 1000,800\n";  //окно 
        gp << "set xlabel 'X'\n"; //ось х
        gp << "set ylabel 'Y'\n"; //ось у
        gp << "set grid\n"; // сетка
        gp << "set xrange[-10:10]\n"; //диапазоны
        gp << "set yrange[-10:10]\n";
        gp << "set size ratio -1\n"; //пропорции 

        
        if (fabs(b1) < EPS) {
            gp << "set arrow from " << -c1 / a1 << ",-10 to " << -c1 / a1 << ",10 nohead lc rgb 'red' lw 2\n";
            gp << "f1(x) = 1/0\n";
        }
        else {
            gp << "f1(x) = (-" << a1 << "*x - " << c1 << ")/" << b1 << "\n";
        }

        if (fabs(b2) < EPS) {
            gp << "set arrow from " << -c2 / a2 << ",-10 to " << -c2 / a2 << ",10 nohead lc rgb 'blue' lw 2\n";
            gp << "f2(x) = 1/0\n";
        }
        else {
            gp << "f2(x) = (-" << a2 << "*x - " << c2 << ")/" << b2 << "\n";
        }

        gp << "plot ";
        if (fabs(b1) >= EPS) gp << "f1(x) title 'Line 1' lw 2 lc rgb 'red', \\\n";
        if (fabs(b2) >= EPS) gp << "     f2(x) title 'Line 2' lw 2 lc rgb 'blue'";
        gp << "\npause -1\n";
        gp.close();

        cout << "\nЗапуск GNUplot..." << endl;
        system("gnuplot -persist plot.gp");
    }

    for (int i = 0; i < m; i++) delete[] a[i];
    delete[] a;
    return 0;
}