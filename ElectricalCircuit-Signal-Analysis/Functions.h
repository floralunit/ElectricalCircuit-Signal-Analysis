#pragma once

void form_t(int n, double* t, double& dt);  //��������� ������� �� ������� ���������� ����������

void form_Uvx(int n, double* t, double* Uvx);  //��������� ������� �� ������� ���������� ����������

void form_Uvix(int n, double* t, double* Uvx, double* Uvix);  //��������� ������� �� ������� ���������� ����������

void form_tabl(int n, double* t, double* Uvx, double* Uvix);  //��������� ������� �� ������� ���������� ����������

void parametr();  //��������� ������� �� ������� ���������� ����������

void write_file(int n, double* t, double* Uvx, double* Uvix);

void zast_read();