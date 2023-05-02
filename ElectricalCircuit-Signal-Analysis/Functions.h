#pragma once

void form_t(int n, double* t, double& dt);  //Заголовок функции со списком формальных параметров

void form_Uvx(int n, double* t, double* Uvx);  //Заголовок функции со списком формальных параметров

void form_Uvix(int n, double* t, double* Uvx, double* Uvix);  //Заголовок функции со списком формальных параметров

void form_tabl(int n, double* t, double* Uvx, double* Uvix);  //Заголовок функции со списком формальных параметров

void parametr();  //Заголовок функции со списком формальных параметров

void write_file(int n, double* t, double* Uvx, double* Uvix);

void zast_read();