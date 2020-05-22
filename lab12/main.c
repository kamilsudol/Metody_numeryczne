#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double funkcja(int m, int k, double x){
    return pow(x,m)*sin(k*x);
}

double factorial(double x){
    if(x == 0){
        return 1;
    }else{
        return x*factorial(x-1);
    }
}

double calka(int k, int m, int i, double x){
    return (pow(-1,i)*(pow(k*x,2*i+m+2)))/(pow(k,m+1)*factorial(2*i+1)*(2*i+m+2));
}

void licz_calke1(int k, int m, const char *plik){
    FILE *file_ptr = fopen(plik, "w");
    int i;
    double suma = 0;
    for(i = 0; i < 31; i++){
        suma += calka(k, m, i, M_PI);
        fprintf(file_ptr, "%d %f\n", i, suma);
        //printf("%d %f\n", i, suma);
    }
    fclose(file_ptr);
}

void licz_calke2(int k, int m, const char *plik){
    FILE *file_ptr = fopen(plik, "w");
    int n[]={11, 21, 51, 101, 201};
    int i,j;
    double suma = 0, h, N, sum_tmp1, sum_tmp2;
    for(i = 0; i < 5; i++){
        sum_tmp1 = 0;
        sum_tmp2 = 0;
        N = n[i] - 1;
        h = M_PI / N;
        for(j = 1; j < N + 1; j++){
            if(j % 2){
                sum_tmp1 += funkcja(m, k, h*j);
            }else{
                sum_tmp2 += funkcja(m, k, h*j);
            }
        }
        suma = (h / 3)*(funkcja(m, k, 0) + funkcja(m, k, M_PI) + 2 * sum_tmp2 + 4 * sum_tmp1);
        fprintf(file_ptr, "%d %f\n", n[i], suma);
        //printf("%d %f\n", n[i], suma);
    }
    fclose(file_ptr);
}

int main(){

    licz_calke1(1, 0, "1.out");
    licz_calke1(1, 1, "2.out");
    licz_calke1(5, 5, "3.out");

    licz_calke2(1, 0, "4.out");
    licz_calke2(1, 1, "5.out");
    licz_calke2(5, 5, "6.out");

    return 0;
}