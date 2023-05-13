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
		int ch;

		cout << "Выберите задание: \n1 - контрольный расчет для n точек \n2 – расчет параметра с заданной точностью \n3 – запись данных в файл \n=>";
		cin >> ch;
		switch (ch) {
		case 1: {
			int n;
			cout << "Введите кол - во точек  для контрольного расчета : ";
			cin >> n;
			form_t(n, t, dt);
			form_Uvx(n, t, Uvx);
			form_Uvix(n, t, Uvx, Uvix);
			form_tabl(n, t, Uvx, Uvix);
			pogr(n, t, dt, Uvx, Uvix);
			//parametr(n);
			break;
		}
		case 2: {
			int n;
			cout << "Введите кол - во точек  для контрольного расчета : ";
			cin >> n;
			form_t(n, t, dt);
			form_Uvx(n, t, Uvx);
			form_Uvix(n, t, Uvx, Uvix);
			cout << "Максимальное время для Uvx: " << time_max(n, t, Uvx) <<endl;
			cout << "Максимальное время для Uvix: " << time_max(n, t, Uvix) << endl;
			cout << "Минимальное время для Uvx: " << time_min(n, t, Uvx) << endl;
			cout << "Минимальное время для Uvix: " << time_min(n, t, Uvix) << endl;
			break;
		}
		case 3: {
			int n;
			cout << "Введите кол - во точек  для контрольного расчета : ";
			cin >> n;
			form_t(n, t, dt);
			form_Uvx(n, t, Uvx);
			form_Uvix(n, t, Uvx, Uvix);
			write_file(n, t, Uvx, Uvix);
			break;
		}
		default: {
			cout << "Такого задания нет! ";
			break;
		}
		}
		cout << "\n\nВыйти? 1-Да 0-Нет ";
		cin >> exit;
	}
	return 0;
}
