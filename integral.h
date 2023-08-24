#pragma once
#include <math.h>

typedef double afunc(double);

double f1(double);
double f2(double);
double f3(double);
double df1(double);
double df2(double);
double df3(double);

double root(afunc*, afunc*, afunc*, afunc*, double, double, double, int*);
double integral_n(afunc*, double, double, int);
double integral(afunc*, double, double, double);
int test_root(void);
double f1_i(double, double);
double f2_i(double, double);
double f3_i(double, double);
int test_integral(void);