#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <windows.h>

using namespace std;

int main() {

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    //1

    ifstream in("input.txt");
    if (!in.is_open()) {
        cerr << "Ошибка: не удалось открыть input.txt\n";
        return 1;
    }

    vector<pair<int, int>> edges;
    int u, v, n = 0;
    while (in >> u >> v) {
        edges.push_back({ u, v });
        n = max(n, max(u, v));
    }
    in.close();

    int m = edges.size();
    vector<vector<int>> M(n + 1, vector<int>(n + 1, 0));

    for (auto& e : edges) {
        M[e.first][e.second] = M[e.second][e.first] = 1;
    }

    ofstream fmat("matrix.txt");
    for (int i = 1; i <= n; i++) { //по строкам
        for (int j = 1; j <= n; j++) // по столбцам
            fmat << M[i][j] << (j < n ? " " : "");
        fmat << "\n"; //переход
    }
    fmat.close();
    cout << "1) matrix.txt\n";


    //2

    vector<int> L(n + 1, 0);  // длины - количество смежных вершин для одной
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (M[i][j]) L[i]++;

    vector<int> S(n + 2, 0); // индексы-указатели
    for (int i = 2; i <= n + 1; i++)
        S[i] = S[i - 1] + L[i - 1];

    vector<int> D(2 * m), U = S;  //смежные вершины
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (M[i][j]) D[U[i]++] = j;

    ofstream fcsr("array.txt");
    fcsr << "S: "; for (int i = 1; i <= n + 1; i++) fcsr << S[i] << " "; fcsr << "\n";
    fcsr << "L: "; for (int i = 1; i <= n; i++) fcsr << L[i] << " "; fcsr << "\n";
    fcsr << "D: "; for (int x : D) fcsr << x << " "; fcsr << "\n";
    fcsr.close();
    cout << "2) array.txt\n";

 
    // 3

    ifstream fcsr_in("array.txt");
    ofstream fedge("edges.txt");

    string line;
    string tag;

    // Читаем строку с S
    getline(fcsr_in, line);
    stringstream ssS(line);
    ssS >> tag;  // прочитали "S:"
    vector<int> S2(n + 2);
    for (int i = 1; i <= n + 1; i++) ssS >> S2[i];

    // Читаем строку с L
    getline(fcsr_in, line);
    stringstream ssL(line);
    ssL >> tag;  // прочитали "L:"
    vector<int> L2(n + 1);
    for (int i = 1; i <= n; i++) ssL >> L2[i];

    // Читаем строку с D
    getline(fcsr_in, line);
    stringstream ssD(line);
    ssD >> tag;  // прочитали "D:"
    vector<int> D2(2 * m);
    for (int i = 0; i < 2 * m; i++) ssD >> D2[i];

    fcsr_in.close();

    for (int i = 1; i <= n; i++)
        for (int j = S2[i]; j < S2[i + 1]; j++)
            if (i < D2[j])
                fedge << i << " " << D2[j] << "\n";
    fedge.close();

    cout << "3) edges.txt\n";
    cout << "\nГотово!\n";
    return 0;
}