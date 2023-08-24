#include "integral.h"
#define NULL 0

double root(afunc* f, afunc* g, afunc* df, afunc* dg, double a, double b, double eps1, int* iters)
{
	while (fabs(b - a) > eps1)
	{
		a = a - (f(a) - g(a)) / (df(a) - dg(a));
		b = a - (a - b) * (f(a) - g(a)) / ((f(a) - g(a)) - (f(b) - g(b)));
		if (iters)
			(*iters)++;
	}
	return b;
}

double integral_n(afunc* f, double a, double b, int n)
{
	double h = (b - a) / n;
	double ans = f(a) + f(a + n * h);
	for (int i = 1; i < n; i++)
		ans += f(a + i * h) * (i % 2 * 2 + 2);
	ans *= h / 3.0;
	return ans;
}

double integral(afunc* f, double a, double b, double eps2)
{
	int n = 10;
	double p = 1.0 / 15.0;
	double prev;
	double curr = integral_n(f, a, b, n);
	do
	{
		prev = curr;
		n *= 2;
		curr = integral_n(f, a, b, n);
	} while (fabs(curr - prev) * p > eps2);
	return curr;
}

int test_root(void)
{
	double x1 = 1.3436506756042787;
	double x2 = 0.8262178094574632;
	double x3 = -1.3078610729163484;
	double eps1 = 0.000001;
	double a, b, temp;
	//
	a = 1.0;
	b = 2.0;
	temp = root(f1, f2, df1, df2, a, b, eps1, NULL);
	if (fabs(x1 - temp) > eps1 || isnan(temp))
		return 1;

	a = 0.1;
	b = 2.0;
	temp = root(f1, f2, df1, df2, a, b, eps1, NULL);
	if (fabs(x1 - temp) > eps1 || isnan(temp))
		return 1;

	a = 0.8;
	b = 1.4;
	temp = root(f1, f2, df1, df2, a, b, eps1, NULL);
	if (fabs(x1 - temp) > eps1 || isnan(temp))
		return 1;
	//
	a = 0.0;
	b = 1.0;
	temp = root(f3, f2, df3, df2, a, b, eps1, NULL);
	if (fabs(x2 - temp) > eps1 || isnan(temp))
		return 1;

	a = -1.0;
	b = 2.0;
	temp = root(f3, f2, df3, df2, a, b, eps1, NULL);
	if (fabs(x2 - temp) > eps1 || isnan(temp))
		return 1;
	
	a = 0.5;
	b = 10.0;
	temp = root(f3, f2, df3, df2, a, b, eps1, NULL);
	if (fabs(x2 - temp) > eps1 || isnan(temp))
		return 1;
	//
	a = -2.0;
	b = -1.0;
	temp = root(f1, f3, df1, df3, a, b, eps1, NULL);
	if (fabs(x3 - temp) > eps1 || isnan(temp))
		return 1;
	
	a = -3.3;
	b = -1.29;
	temp = root(f1, f3, df1, df3, a, b, eps1, NULL);
	if (fabs(x3 - temp) > eps1 || isnan(temp))
		return 1;
	
	a = -1.31;
	b = 0;
	temp = root(f1, f3, df1, df3, a, b, eps1, NULL);
	if (fabs(x3 - temp) > eps1 || isnan(temp))
		return 1;
	//
	return 0;
}

double f1_i(double a, double b)
{
	double t1 = a + 4 * atan(a);
	double t2 = b + 4 * atan(b);
	return t2 - t1;
}

double f2_i(double a, double b)
{
	double t1 = pow(a, 4) / 4;
	double t2 = pow(b, 4) / 4;
	return t2 - t1;
}

double f3_i(double a, double b)
{
	double t1 = -1.0 / (log(2) * pow(2, a));
	double t2 = -1.0 / (log(2) * pow(2, b));
	return t2 - t1;
}

int test_integral(void)
{
	double eps2 = 0.000001;
	double a, b, temp;
	//
	a = -1.0;
	b = 1.0;
	temp = integral(f1, a, b, eps2);
	if (fabs(f1_i(a, b) - temp) > eps2 || isnan(temp))
		return 1;
	
	a = -3.0;
	b = 1.5;
	temp = integral(f1, a, b, eps2);
	if (fabs(f1_i(a, b) - temp) > eps2 || isnan(temp))
		return 1;
	
	a = -3.33;
	b = 3.33;
	temp = integral(f1, a, b, eps2);
	if (fabs(f1_i(a, b) - temp) > eps2 || isnan(temp))
		return 1;
	//
	a = 0.0;
	b = 1.0;
	temp = integral(f2, a, b, eps2);
	if (fabs(f2_i(a, b) - temp) > eps2 || isnan(temp))
		return 1;
	
	a = -1.0;
	b = 1.0;
	temp = integral(f2, a, b, eps2);
	if (fabs(f2_i(a, b) - temp) > eps2 || isnan(temp))
		return 1;
	
	a = 0.5;
	b = 2.5;
	temp = integral(f2, a, b, eps2);
	if (fabs(f2_i(a, b) - temp) > eps2 || isnan(temp))
		return 1;
	//
	a = -3.2;
	b = 1.0;
	temp = integral(f3, a, b, eps2);
	if (fabs(f3_i(a, b) - temp) > eps2 || isnan(temp))
		return 1;
	
	a = -0.7;
	b = 0.2;
	temp = integral(f3, a, b, eps2);
	if (fabs(f3_i(a, b) - temp) > eps2 || isnan(temp))
		return 1;
	
	a = -2.0;
	b = 6.0;
	temp = integral(f3, a, b, eps2);
	if (fabs(f3_i(a, b) - temp) > eps2 || isnan(temp))
		return 1;
	//
	return 0;
}
