#include <iostream>
#include "Functions.h"
#include <Windows.h>
using namespace std;
# define N 10000
#define _CRT_SECURE_NO_DEPRECATE

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int exit = 0;
	zast_read();
	while (exit == 0) {
		double t[N], Uvx[N], Uvix[N], dt;
		int ch;

		cout << "\nВыберите задание: \n1 - контрольный расчет для n точек \n2 - расчет погрешности для Uvx \n3 - расчет погрешности для Uvix \n4 – расчет параметра с заданной точностью \n5 - открыть график Uvx \n6 - открыть график Uvix \n=> ";
		cin >> ch;

		int n;
		if (ch < 5) {
			cout << "\nВведите кол - во точек  для контрольного расчета: ";
			cin >> n;
		}

		switch (ch) {
		case 1: {
			form_t(n, t, dt);
			form_Uvx(n, t, Uvx);
			form_Uvix(n, t, Uvx, Uvix);
			form_tabl(n, t, Uvx, Uvix);

			int vvod;
			cout << "\n\nЗаписать в файл " << n << " точек " << "(1-Да,2-Нет): ";
			cin >> vvod;

			if (vvod == 1)
			{
				write_file(n, t, Uvx, Uvix);
			}
			break;
		}
		case 2: {
			form_t(n, t, dt);
			form_Uvx(n, t, Uvx);
			form_Uvix(n, t, Uvx, Uvix);
			form_tabl(n, t, Uvx, Uvix);
			cout << endl << endl;
			pogr(n, t, dt, Uvx, Uvix, true);
			break;
		}
		case 3: {
			form_t(n, t, dt);
			form_Uvx(n, t, Uvx);
			form_Uvix(n, t, Uvx, Uvix);
			form_tabl(n, t, Uvx, Uvix);
			cout << endl << endl;
			pogr(n, t, dt, Uvx, Uvix, false);
			break;
		}
		case 4: {
			form_t(n, t, dt);
			form_Uvx(n, t, Uvx);
			parametr(n, Uvx);
			break;
		}
		case 5: {
			ShellExecuteA(NULL, "open", "Uvx1.png", NULL, NULL, SW_SHOWNORMAL);
			break;
		}
		case 6: {
			ShellExecuteA(NULL, "open", "Uvix1.png", NULL, NULL, SW_SHOWNORMAL);
			break;
		}
		default: {
			cout << "Такого задания нет! ";
			break;
		}
		}
		cout << "\nВыйти? 1-Да 0-Нет ";
		cin >> exit;
	}
	return 0;
}
