#include <cstdlib>
#include <fstream>
#include <windows.h>
int main() {
SetConsoleOutputCP(1251);
std::ofstream gp("plot.gp");
gp << "set terminal wxt size 800,600\n"
   << "set title 'Пересечение прямых'\n"
   << "set xrange[-10:10]\nset yrange[-10:10]\nset grid\n"
   << "f1(x)=(-2*x - -5)/3\n"
   << "f2(x)=(-1*x - 1)/-1\n"
   << "plot f1(x) title 'Прямая 1' lw 2, f2(x) title 'Прямая 2' lw 2, '-' pt 7 ps 2 title 'Точка (-0.4,-1.4)'\n"
   << -0.4 << " " << -1.4 << "\ne\n";
gp.close();
system(\"gnuplot -persist plot.gp\");
return 0;
}
