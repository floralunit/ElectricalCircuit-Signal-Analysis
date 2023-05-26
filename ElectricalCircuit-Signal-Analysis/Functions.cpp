#include <iostream>
#include <fstream>
#include <locale>
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning (disable : 4996)
using namespace std;
const int tn = 10, tk = 90;

void form_t(int n, double* t, double& dt)
{
	dt = (tk - tn) / (n - 1);
	for (int i = 0; i < n; i++)
		t[i] = tn + i * dt;
}


void form_Uvx(int n, double* t, double* Uvx) {
	int U1 = 100, U2 = 80, t1 = 22, t2 = 70;
	for (int i = 0; i < n; i++) // Формирование массива Uvx
		if (t[i] <= t1) Uvx[i] = ((t[i] - tn) * (U1 - 0)) / (t1 - tn);
		else if (t[i] <= t2) Uvx[i] = (((t[i] - t1) * (U2 - U1)) / (t2 - t1)) + U1;
		else if (t[i] > t2) Uvx[i] = (((t[i] - t2) * (0 - U2)) / (tk - t2)) + U2;
}

void form_Uvix(int n, double* t, double* Uvx, double* Uvix) {
	int a = 2, b = 4, c = -1;
	for (int i = 0; i < n; i++) // Формирование массива Uvix
		Uvix[i] = a * Uvx[i] * Uvx[i] + b * Uvx[i] + c;
}

void form_tabl(int n, double* t, double* Uvx, double* Uvix) {
	cout << " №      t      Uvx      Uvix      " << endl;
	for (int i = 0; i < n; i++) // Вывод данных в виде таблицы
		printf("\n % 3d % 6.3f % 6.3f % 7.3f", i, t[i], Uvx[i], Uvix[i]);
}


void write_file(int n, double* t, double* Uvx, double* Uvix) {

	std::ofstream file1("massiv_t.txt");
	std::ofstream file2("massiv_Uvx.txt");
	std::ofstream file3("massiv_Uvix.txt");
	std::locale loc(std::locale::classic(), new std::numpunct<char>('.'));
	file1.imbue(loc); // установка локали для файла
	file2.imbue(loc); // установка локали для файла
	file3.imbue(loc); // установка локали для файла

	for (int i = 0; i < n; i++)
	{
		file1 << t[i] << std::endl;
		file2 << Uvx[i] << std::endl;
		file3 << Uvix[i] << std::endl;
	}

	file1.close();
	file2.close();
	file3.close();


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

double Umin(int n, double* Ui) {
	double min = Ui[0];
	int min_index = 0;
	int vvod = 0;
	for (int i = 0; i < n; i++)
	{
		if (min > Ui[i])
		{
			min = Ui[i];
			min_index = i;
		}
	}

	return Ui[min_index];
}

double Umax(int n, double* Ui) {
	double max = Ui[0];
	int max_index = 0;
	for (int i = 0; i < n; i++)
	{
		if (max < Ui[i])
		{
			max = Ui[i];
			max_index = i;
		}
	}
	return Ui[max_index];
}

void parametr(int n, double* Ui) {

	cout << "\n\nРасчет длительности переднего импульса...";

	double umax = Umax(n, Ui);
	double umin = Umin(n, Ui);

	double dt = (tk - tn) / (n - 1);

	double dlit = 0;
	for (int i = 0; i < n; i++)
		if (Ui[i] >= umin + 0.5 * (umax - umin)) dlit += dt;

	double U1 = umin + 0.9f * (umax - umin);
	double U2 = umin + 0.1f * (umax - umin);
	for (int i = 0; i < n; i++)
		if (Ui[i] > U1 && Ui[i] < U2 && Ui[i + 1]>Ui[i]) dlit += dt;

	cout << "\n\nДлительность переднего импульса равна:  " << dlit;
	cout << endl;
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
			par1 = Umax(n, Uvx);
			text = "  Uvx[max] = ";
		}
		else {
			par1 = Umax(n, Uvix);
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
