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
	for (int i = 0; i < n; i++) // ������������ ������� Uvx
		if (0 <= t[i] and t[i] < T / 2) Uvx[i] = 2 * U * (t[i] / T);
		else Uvx[i] = 0;
}

void form_Uvix(int n, double* t, double* Uvx, double* Uvix) {
	int a = 2, b = 4, c = -1;
	for (int i = 0; i < n; i++) // ������������ ������� Uvix
		Uvix[i] = a * Uvx[i] * Uvx[i] + b * Uvx[i] + c;
}

void form_tabl(int n, double* t, double* Uvx, double* Uvix) {
	cout << " �     t        Uvx      Uvix     " << endl;
	for (int i = 0; i < n; i++) // ����� ������ � ���� �������
		printf("\n % 3d % 6.6lf % 6.6lf % 6.6lf", i, t[i], Uvx[i], Uvix[i]);
}
void parametr() {

}

void write_file(int n, double* t, double* Uvx, double* Uvix) {
	FILE* f1, * f2, * f3; 		 //���������� ��������� �� �������� ����������
	f1 = fopen("massiv_t.txt", "w");
	f2 = fopen("massiv_Uvx.txt", "w");  //�������� ������ �� ������
	f3 = fopen("massiv_Uvix.txt", "w");
	for (int i = 0; i < n; i++)
	{
		fprintf(f1, "\n %6.6lf", t[i]);
		fprintf(f2, "\n %6.6lf", Uvx[i]);         //������ ������ � ����
		fprintf(f3, "\n%6.6lf", Uvix[i]);
	}
	fclose(f1);
	fclose(f2);                                       //�������� ������
	fclose(f3);
}

void zast_read() {
	FILE* f = fopen("zast.txt", "r");// �������� ����� ��� ������
	if (f == NULL)
	{
		printf("������ ��� �������� �����!\n");
		return;
	}
	char ch;
	while (!feof(f))                        // ���������� ������ �� ����� �� ��� ���, 
	{
		fscanf_s(f, "%c", &ch);             // ���� �� ������� �������� ����� �����
		printf("%c", ch);
	}
	fclose(f);
}