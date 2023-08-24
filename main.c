#include <stdio.h>
#include <string.h>
#include "integral.h"

const char* HM = "--help -h\n--root -r\n--iterations -i\n--test-root -R\n--test-integral -I\n--test -t\n";

int main(int argc, char* argv[])
{
	int flags[6] = { 0 };
	for (int i = 1; i < argc; i++)
	{
		char* temp = argv[i];
		if (!strcmp("-h", temp) || !strcmp("--help", temp))
			flags[0] = 1;
		if (!strcmp("-r", temp) || !strcmp("--root", temp))
			flags[1] = 1;
		if (!strcmp("-i", temp) || !strcmp("--iterations", temp))
			flags[2] = 1;
		if (!strcmp("-R", temp) || !strcmp("--test-root", temp))
			flags[3] = 1;
		if (!strcmp("-I", temp) || !strcmp("--test-integral", temp))
			flags[4] = 1;
		if (!strcmp("-t", temp) || !strcmp("--test", temp))
			flags[5] = 1;
	}
	if (flags[0])
		printf("%s", HM);
	int iters = 0;
	double x1 = root(f1, f3, df1, df3, -2.0, 1.5, 0.000001, &iters);
	double x2 = root(f2, f3, df2, df3, -2.0, 1.5, 0.000001, &iters);
	double x3 = root(f1, f2, df1, df2, -2.0, 1.5, 0.000001, &iters);
	if (flags[1])
		printf("x1: %lf x2: %lf x3: %lf\n", x1, x2, x3);
	if (flags[2] && !flags[3])
		printf("iterations: %d\n", iters);
	if (flags[3])
	{
		double(*f_arr[3])(double) = { f1, f2, f3 };
		double(*df_arr[3])(double) = { df1, df2, df3 };
		int F1, F2;
		double A, B, E, R;
		if (!scanf("%d:%d:%lf:%lf:%lf:%lf", &F1, &F2, &A, &B, &E, &R))
			return -1;
		int iters_R = 0;
		double ans = root(f_arr[F1 - 1], f_arr[F2 - 1], df_arr[F1 - 1], df_arr[F2 - 1], A, B, E, &iters_R);
		double abs_m = fabs(ans - R);
		double rel_m = abs_m / fabs(R);
		printf("%lf %lf %lf\n", ans, abs_m, rel_m);
		if (flags[2])
			printf("iterations: %d\n", iters_R);
	}
	if (flags[4])
	{
		double(*f_arr[3])(double) = { f1, f2, f3 };
		int F;
		double A, B, E, R;
		if (!scanf("%d:%lf:%lf:%lf:%lf", &F, &A, &B, &E, &R))
			return -1;
		double ans = integral(f_arr[F - 1], A, B, E);
		double abs_m = fabs(ans - R);
		double rel_m = abs_m / fabs(R);
		printf("%lf %lf %lf\n", ans, abs_m, rel_m);
	}
	if (flags[5])
	{
		printf("Root test: ");
		if (!test_root())
			printf("successful\n");
		else
			printf("failed\n");
		printf("Integral test: ");
		if (!test_integral())
			printf("successful\n");
		else
			printf("failed\n");
	}
	if (!(flags[0] || flags[1] || flags[2] || flags[3] || flags[4] || flags[5]))
	{
		double ans = 0;
		ans += integral(f1, x1, x2, 0.00001) - integral(f3, x1, x2, 0.00001);
		ans += integral(f1, x2, x3, 0.00001) - integral(f2, x2, x3, 0.00001);
		printf("Square area = %lf\n", ans);
	}
	return 0;
}
