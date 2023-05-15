#include <iostream>
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning (disable : 4996)
using namespace std;
const double T = 0.00001;

void form_t(int n, double* t, double& dt)
{
	double  tn = 0, tk = T;
	dt = (tk - tn) / (n - 1);
	for (int i = 0; i < n; i++)
		t[i] = tn + i * dt;
}


void form_Uvx(int n, double* t, double* Uvx) {
	int U = 4;
	for (int i = 0; i < n; i++) // Формирование массива Uvx
		if (0 <= t[i] and t[i] < T / 2) Uvx[i] = 2 * U * (t[i] / T);
		else Uvx[i] = 0;
}

void form_Uvix(int n, double* t, double* Uvx, double* Uvix) {
	int a = 2, b = 4, c = -1;
	for (int i = 0; i < n; i++) // Формирование массива Uvix
		Uvix[i] = a * Uvx[i] * Uvx[i] + b * Uvx[i] + c;
}

void form_tabl(int n, double* t, double* Uvx, double* Uvix) {
	cout << "\n №     t        Uvx      Uvix     ";
	for (int i = 0; i < n; i++) // Вывод данных в виде таблицы
		printf("\n % 3d % 6.6lf % 6.6lf % 6.6lf", i + 1, t[i], Uvx[i], Uvix[i]);
}


void write_file(int n, double* t, double* Uvx, double* Uvix) {
	FILE* f1, * f2, * f3; 		 //Объявление указателя на файловую переменную
	f1 = fopen("massiv_t.txt", "w");
	f2 = fopen("massiv_Uvx.txt", "w");  //Открытие файлов на запись
	f3 = fopen("massiv_Uvix.txt", "w");
	for (int i = 0; i < n; i++)
	{
		fprintf(f1, "\n %6.6lf", t[i]);
		fprintf(f2, "\n %6.6lf", Uvx[i]);         //Запись данных в файл
		fprintf(f3, "\n%6.6lf", Uvix[i]);
	}
	fclose(f1);
	fclose(f2);                                       //Закрытие файлов
	fclose(f3);
	printf("Запись прошла успешно!\n");
}

void zast_read() {
	FILE* f = fopen("zast.txt", "r");// Открытие файла для чтения
	if (f == NULL)
	{
		printf("Ошибка при открытии файла!\n");
		return;
	}
	char ch;
	while (!feof(f))                        // Считывание данных из файла до тех пор, 
	{
		fscanf_s(f, "%c", &ch);             // пока не найдено значение конца файла
		printf("%c", ch);
	}
	fclose(f);
}

double time_min(int n, double* t, double* U) {
	double min = U[0];
	int min_index = 0;
	int vvod = 0;
	for (int i = 0; i < n; i++)
	{
		if (min > U[i])
		{
			min = U[i];
			min_index = i;
		}
	}
	//printf("Минимальное значение принимает при времени t = %f\n", t[min_index]);
	return t[min_index];
}

double time_max(int n, double* t, double* U) {
	double max = U[0];
	int max_index = 0;
	int vvod = 0;
	for (int i = 0; i < n; i++)
	{
		if (max < U[i])
		{
			max = U[i];
			max_index = i;
		}
	}
	//printf("Максимальное значение принимает при времени t = %f\n", t[max_index]);

	return t[max_index];
}

double Umax(int n, double* t, double* U) {
	double max = U[0];
	int max_index = 0;
	for (int i = 0; i < n; i++)
	{
		if (max < U[i])
		{
			max = U[i];
			max_index = i;
		}
	}
	return U[max_index];
}


void pogr(int n, double* t, double& dt, double* Uvx, double* Uvix, bool isUvx) {
	double p = 1;		 // текущая погрешность
	float eps = 0.001;	// заданная погрешность 
	double par = 1000; // начальное значение параметра (очень большое число)
	double par1 = 0;
	string text = "";
	while (p > eps) {
		form_t(n, t, dt);
		form_Uvx(n, t, Uvx);
		form_Uvix(n, t, Uvx, Uvix);
		if (isUvx) {
			par1 = Umax(n, t, Uvx);
			text = "  Uvx[max] = ";
		}
		else {
			par1 = Umax(n, t, Uvix);
			text = "  Uvix[max] = ";
		}
		p = fabs(par - par1) / par1;
		cout << "n = " << n << text << par1 << "  Погрешность = " << p << endl;
		par = par1;
		n = 2 * n;
	}
	cout << endl;
	int vvod;
	cout << "Записать в файл " << n/2 << " точек " << "(1-Да,2-Нет): ";
	cin >> vvod;

	if (vvod == 1)
	{
		write_file(n/2, t, Uvx, Uvix);
	}
}
