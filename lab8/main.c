#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "nr.h"
#include "nrutil.h"

float fx1(float x){
	return 1/(1+pow(x,2));
}

float fx2(float x){
	return cos(2*x);
}

float fi(int i, float* wezly, float x, float h){

	if(x >= wezly[i-2] && x < wezly[i-1]){
		return pow(x-wezly[i-2], 3) / pow(h, 3);
	}else if(x >= wezly[i-1] && x < wezly[i]){
		return (pow(h, 3) + 3 * pow(h, 2) * (x - wezly[i-1]) + 3 * h * pow(x-wezly[i-1], 2) - 3 * pow(x-wezly[i-1], 3)) / pow(h, 3);
	}else if(x >= wezly[i] && x < wezly[i+1]){
		return (pow(h, 3) + 3 * pow(h, 2) * (wezly[i+1] - x) + 3 * h * pow(wezly[i+1] - x, 2) - 3 * pow(wezly[i+1] - x, 3)) / pow(h, 3);
	}else if(x >= wezly[i+1] && x <= wezly[i+2]){
		return pow(wezly[i+2] - x, 3) / pow(h, 3);
	}else{
		return 0;
	}
}

void interpolacja(int n, float (*fx)(float), const char *plik){

	FILE *file_ptr = fopen(plik, "w");
	float **A = matrix(1, n, 1, n);
	float **B = matrix(0, n+1, 1, 1);
	float xx[n+6];
	float *xw = &xx[2];
	float *yw = vector(1, n);
	float x_min = -5, x_max = 5;
	float h = (x_max - x_min)/(n-1);
	float alfa, beta;
	float wynik, dx = 0.01;

	for(int i = 1; i < n+1; i++){
		for(int j = 1; j < n+1; j++){
			A[i][j]=0;
		}
	}

	for(int i = 1; i < n+1; i++){
		for(int j = 1; j < n+1; j++){
			if(i == j){
				A[i][j]=4;
				if(i>1 && i<n){
					A[i][j+1] = 1;
					A[i][j-1] = 1;
				}
			}
		}
	}

	A[1][2] = 2;
	A[n][n-1] = 2;

	for(int i = -2; i <= (n+3); i++){
		xw[i] = x_min + h * (i-1);
	}

	for(int i = 1; i < n+1; i++){
		yw[i] = fx(xw[i]);
	}		

	alfa = (fx(xw[1]+dx)-fx(xw[1]-dx))/(2*dx);
	beta = (fx(xw[n]+dx)-fx(xw[n]-dx))/(2*dx);

	B[1][1] = yw[1] + alfa*(h/3);
	B[n][1] = yw[n] - beta*(h/3);

	for(int i = 2; i < n; i++){
		B[i][1] = yw[i];
	}

	gaussj(A, n, B, 1);

	B[0][1] = B[2][1] - alfa*(h/3);
	B[n+1][1] = B[n-1][1] + beta*(h/3);

	for(float x = x_min; x <= x_max; x += 0.01){
		wynik = 0;
		for(int i = 0; i < n+2; i++){
			wynik += B[i][1] * fi(i, xw, x, h);
		}
		fprintf(file_ptr, "%f  %f \n", x, wynik);
	}

	fclose(file_ptr);
	free_matrix(A, 1, n, 1, n);
	free_matrix(B, 0, n+1, 1, 1);
	free_vector(yw, 1, n);
}

int main(){

	interpolacja(5, fx1, "fun1.out");
	interpolacja(6, fx1, "fun2.out");
	interpolacja(10, fx1, "fun3.out");
	interpolacja(20, fx1, "fun4.out");

	interpolacja(6, fx2, "cos1.out");
	interpolacja(7, fx2, "cos2.out");
	interpolacja(14, fx2, "cos3.out");

	return 0;
}