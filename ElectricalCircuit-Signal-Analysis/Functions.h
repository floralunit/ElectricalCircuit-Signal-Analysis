#pragma once

void form_t(int n, double* t, double& dt);  //Заголовок функции со списком формальных параметров

void form_Uvx(int n, double* t, double* Uvx);  //Заголовок функции со списком формальных параметров

void form_Uvix(int n, double* t, double* Uvx, double* Uvix);  //Заголовок функции со списком формальных параметров

void form_tabl(int n, double* t, double* Uvx, double* Uvix);  //Заголовок функции со списком формальных параметров

void pogr(int n, double* t, double& dt, double* Uvx, double* Uvix, bool isUvx);

void write_file(int n, double* t, double* Uvx, double* Uvix);

void zast_read();

double Umax(int n, double* Ui);

double Umin(int n, double* Ui);

void parametr(int n, double* Ui);