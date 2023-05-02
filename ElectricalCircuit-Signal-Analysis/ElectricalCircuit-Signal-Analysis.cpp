#include <iostream>
#include "Functions.h"
using namespace std;
# define N 1000
#define _CRT_SECURE_NO_DEPRECATE

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    int exit = 0;
    zast_read();
    while (exit == 0) {
        double t[N], Uvx[N], Uvix[N], dt;
        int n;
        cout << "Введите кол - во точек  для контрольного расчета : ";
        cin >> n;
        form_t(n, t, dt);
        form_Uvx(n, t, Uvx);
        form_Uvix(n, t, Uvx, Uvix);
        form_tabl(n, t, Uvx, Uvix);
        parametr();
        cout << "\n\nВыйти? 1-Да 0-Нет ";
        cin >> exit;
    }
    return 0;
}
