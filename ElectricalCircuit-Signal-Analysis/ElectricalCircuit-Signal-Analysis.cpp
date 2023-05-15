#include <iostream>
#include "Functions.h"
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

		cout << "\nВыберите задание: \n1 - контрольный расчет для n точек \n2 - расчет погрешности для Uvx \n3 - расчет погрешности для Uvix \n4 – расчет параметра с заданной точностью\n=> ";
		cin >> ch;

		int n;
		cout << "\nВведите кол - во точек  для контрольного расчета: ";
		cin >> n;

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
			form_Uvix(n, t, Uvx, Uvix);
			cout << "Максимальное время для Uvx: " << time_max(n, t, Uvx) << endl;
			cout << "Максимальное время для Uvix: " << time_max(n, t, Uvix) << endl;
			cout << "Минимальное время для Uvx: " << time_min(n, t, Uvx) << endl;
			cout << "Минимальное время для Uvix: " << time_min(n, t, Uvix) << endl;
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
