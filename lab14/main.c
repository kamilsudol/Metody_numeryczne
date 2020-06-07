#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define K 10

double gen_1() {
	static long int x  = 10;
	int a = 17;
	long int m = pow(2, 13) - 1;
	x = (a * x) % m;
	return x /(m + 1.0);
}

double gen_2() {
	static long int x  = 10;
	int a = 85;
	long int m = pow(2, 13) - 1;
	x = (a * x) % m;
	return x /(m + 1.0);
}

double gen_3() {
	static long int x0  = 10;
	static long int x1  = 10;
	static long int x2  = 10;	
	int a0 = 1176;
	int a1 = 1476;
	int a2 = 1776;
	long int m = pow(2, 32) - 5;
	long int tmp = (a0 * x0 + a1 * x1 + a2 * x2) % m;
	x2 = x1;
	x1 = x0;
	x0 = tmp;
	return x0 /(m+1.0);
}

void generatory(const char *plik, double (*gen)(), int N){
    FILE * file_ptr = fopen(plik, "w");
    double x[N];
    for(int i = 0; i < N; i++) {
		x[i] = gen();
	}

    for (int i = 0; i < N - 3; i++) {
		fprintf(file_ptr, "%g %g %g %g\n", x[i], x[i+1], x[i+2], x[i+3]);
	}
	fprintf(file_ptr, "%g %g %g\n", x[N-3], x[N-2], x[N-1]);
	fprintf(file_ptr, "%g %g\n", x[N-2], x[N-1]);
	fclose(file_ptr);
}

void kula(const char *plik1, const char * plik2, int N){
    FILE * file_ptr1 = fopen(plik1, "w");
	FILE * file_ptr2 = fopen(plik2, "w");

	double sfera[N][3];
	double kula[N][3];

	for (int i = 0; i < N; i++) {
		double u1 = gen_3();
		double u2 = gen_3();
		double u3 = gen_3();
		double u4 = gen_3();

		sfera[i][0] = sqrt(-2 * log(1 - u1)) * cos(2 * M_PI * u2);
		sfera[i][1] = sqrt(-2 * log(1 - u1)) * sin(2 * M_PI * u2);
		sfera[i][2] = sqrt(-2 * log(1 - u3)) * cos(2 * M_PI * u4);

		double norm = sqrt(pow(sfera[i][0], 2) + pow(sfera[i][1], 2) + pow(sfera[i][2], 2));

		sfera[i][0] /= norm; 
		sfera[i][1] /= norm; 
		sfera[i][2] /= norm; 

		fprintf(file_ptr1, "%g %g %g\n", sfera[i][0],  sfera[i][1],  sfera[i][2]);

		double ui = gen_3();
		double si = pow(ui, 1.0/3.0);
		kula[i][0] = sfera[i][0] * si;
		kula[i][1] = sfera[i][1] * si;
		kula[i][2] = sfera[i][2] * si;	
		fprintf(file_ptr2, "%g %g %g\n", kula[i][0],  kula[i][1],  kula[i][2]);
	}
	fclose(file_ptr1);
	fclose(file_ptr2);
}

void hist(const char * plik1, const char * plik2, int n) {
	FILE * file_ptr1 = fopen(plik1, "w"); 
	FILE * file_ptr2 = fopen(plik2, "w"); 

	double delta = 1.0 / K;
    double nj[K] = {0};

    double kula_x, kula_y, kula_z;

    for (int i = 0; i < n; i++) {
    	double u1 = gen_3();
		double u2 = gen_3();
		double u3 = gen_3();
		double u4 = gen_3();

		double x = sqrt(-2 * log(1 - u1)) * cos(2 * M_PI * u2);
		double y = sqrt(-2 * log(1 - u1)) * sin(2 * M_PI * u2);
		double z = sqrt(-2 * log(1 - u3)) * cos(2 * M_PI * u4);

		double norm = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

		x /= norm; 
		y /= norm; 
		z /= norm;

		double ui = gen_3();
		double si = pow(ui, 1.0/3.0);
		kula_x = x * si;
		kula_y = y * si;
		kula_z = z * si;	

		norm = sqrt(pow(kula_x, 2) + pow(kula_y, 2) + pow(kula_z, 2));

		int j = (int)(norm / delta);
		nj[j]++;
    }

    for(int i = 0; i < K; i++) {
    	double Rj = delta * (i+1);
        double Rj1 = delta * (i);
        double Vj = (4.0 / 3.0) * M_PI * pow(Rj, 3);
        double Vj1 = (4.0 / 3.0) * M_PI * pow(Rj1, 3);
        double gj = nj[i] / (Vj - Vj1);
        fprintf(file_ptr1, "%d %g\n", i, nj[i]);
        fprintf(file_ptr2, "%d %g\n", i, gj);
    }
    fclose(file_ptr1);
    fclose(file_ptr2);
}

int main() {
	
	generatory("gen1.dat", gen_1, 2000);
    generatory("gen2.out", gen_2, 2000);
    generatory("gen3.out", gen_3, 2000);

	kula("sfera.out", "kula.out", 2000);

    hist("nj1.out", "gj1.out", 2000);
	hist("nj2.out", "gj2.out", pow(10, 4));
	hist("nj3.out", "gj3.out", pow(10, 7));

	return 0;
}