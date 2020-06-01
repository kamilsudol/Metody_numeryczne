#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nr.h"
#include "nrutil.h"

float fun1(float x){
    return 1.0/(x*pow(pow(x,2)-1,0.5));
}

float fun2(float x){
    return log(x)*exp(-pow(x,2));
}

float fun3(float x){
    return sin(2*x)*exp(-3*x);
}

void calka_1(const char * plik){

    FILE *file_ptr = fopen(plik, "w");
    float wartosc = M_PI/3.0;

    int n, i;	

	for(n = 2; n <= 100; n++){
		float w[n+1], x[n+1];
		float suma = 0;

		gauleg(1.0, 2.0, x, w, n);
		
		for(i = 1; i <= n; i++){
			suma += w[i] * fun1(x[i]);
		}
        //print("%d %g\n", n, fabs(suma - wartosc));
		fprintf (file_ptr, "%d %g\n", n, fabs(suma - wartosc));
	}

    fclose(file_ptr);
}

void calka_2(const char * plik1, const char * plik2){

    FILE *file_ptr1 = fopen(plik1, "w");
    FILE *file_ptr2 = fopen(plik2, "w");
    float wartosc = -0.8700577;

    int n, i;	

	for(n = 2; n <= 100; n += 2){
		float w[n+1], x[n+1];
		float suma = 0;

		gauher(x, w, n);
		
		for(i = 1; i <= n; i++){
			suma += w[i] * fun2(fabs(x[i]));
		}
		suma = suma/2.;
        //print("%d %g\n", n, fabs(suma - wartosc));
		fprintf (file_ptr1, "%d %g\n", n, fabs(suma - wartosc));
	}

	for(n = 2; n <= 100; n++){
		float w[n+1], x[n+1];
		float suma = 0;

		gauleg(0.0, 5.0, x, w, n);
		
		for(i = 1; i <= n; i++){
			suma += w[i] * fun2(x[i]);
		}
        //print("%d %g\n", n, fabs(suma - wartosc));
		fprintf (file_ptr2, "%d %g\n", n, fabs(suma - wartosc));
	}

    fclose(file_ptr1);
    fclose(file_ptr2);
}

void calka_3(const char * plik){

    FILE *file_ptr = fopen(plik, "w");
    float wartosc = 2.0/13.0;

    int n, i;	

	for(n = 2; n <= 10; n++){
		float w[n+1], x[n+1];
		float suma = 0;

		gaulag(x, w, n, 0);
		
		for(i = 1; i <= n; i++){
			suma += w[i] * fun3(x[i]);
		}
        //print("%d %g\n", n, fabs(suma - wartosc));
		fprintf (file_ptr, "%d %g\n", n, fabs(suma - wartosc));
	}

    fclose(file_ptr);
}

int main(){
    calka_1("1.out");
    calka_2("2a.out", "2b.out");
    calka_3("3.out");
    return 0;
}