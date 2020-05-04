#include <stdlib.h>
#include <stdio.h>
#include "nrutil.h"
#include "nr.h"
#include <time.h>
#include <math.h>

float value_x(){
    //srand(time(NULL));
    return rand()/(RAND_MAX + 1.0);
}

float sig(){
    float alfa = 0.1;
    return alfa*(value_x()-0.5);
}

float value_g(int sigma, int x0, float x){
    float a0, a1, a2;
    a0 = -pow(x0,2)/(2*pow(sigma,2));
    a1 = x0/pow(sigma,2);
    a2 = -1/(2*pow(sigma,2));
    return exp(a0+a1*x+a2*pow(x,2));
}

float value_f(int sigma, int x0, float x){
    return log(value_g(sigma, x0, x));
}

float value_g2(int sigma, int x0, float x){
    return value_g(sigma,x0,x)*(1+sig());
}

float value_f2(int sigma, int x0, float x){
    return log(value_g2(sigma, x0, x));
}

float value_F(float **R, float x){
    return R[1][1] + R[2][1]*x + R[3][1]*pow(x,2) + R[4][1]*pow(x,3);
}

float value_G(float x){
    return exp(x);
}

void aproksymacja(int n, float (*fun)(int, int, float),float (*fun2)(int, int, float), const char* plik1, const char* plik2, const char* plik3){

    FILE *file_ptr1=fopen(plik1, "w");
    FILE *file_ptr2=fopen(plik2, "w");
    FILE *file_ptr3=fopen(plik3, "w");

    int sigma = 4;
    int m = 4;
    int x0 = 2;
    int x_min = -3*sigma + x0, x_max = 3*sigma + x0;
    float h = (x_max - x_min)/(float)(n-1);
    //printf("%f\n", h);

    int i,j,k;
    for(i = 0; i < n; i++){
        fprintf(file_ptr1,"%f %f\n",x_min +h*i, fun2(sigma,x0,x_min +h*i));
    }

    float **G = matrix(1,m+1,1,m+1);
    float **R = matrix(1,m+1,1,1);
    float suma, suma2;
    for(i = 1; i < m+1;i++){
        for(k = 1; k < m+1;k++){
            suma = 0;
            suma2=0;
            for(j = 1; j < n+1;j++){
                suma += pow(x_min +h*(j-1),i+k-2);
                suma2 += fun(sigma, x0, x_min +h*(j-1)) * pow(x_min +h*(j-1),k-1);
            }
            G[i][k] = suma;
            R[k][1]=suma2;
            //printf("%f        ", G[i][k]);
            
        }
        //printf("%f        ", R[i][1]);
        //printf("\n");
    }

    gaussj(G,m, R, 1);

    for(i = 1; i < m+1;i++){
        fprintf(file_ptr3,"%f \n", R[i][1]);
        //printf("\n");
    }
    int val;
    for(i=1;i<n+1;i++){
        fprintf(file_ptr2,"%f %f\n",x_min +h*(i-1),value_G(value_F(R,x_min +h*(i-1))));
    }

    fclose(file_ptr1);
    fclose(file_ptr2);
    fclose(file_ptr3);
    free_matrix(G, 1, m+1, 1, m+1);
	free_matrix(R, 1, m+1, 1, 1);

}

int main(){
    aproksymacja(11, value_f, value_g, "g_1_1.out", "G_1_1.out","g_1_n11");
    aproksymacja(21, value_f, value_g,"g_1_2.out", "G_1_2.out","g_1_n21");
    aproksymacja(101, value_f,value_g, "g_1_3.out", "G_1_3.out","g_1_n101");

    aproksymacja(11, value_f2, value_g2,"g_2_1.out", "G_2_1.out","g_2_n11");
    aproksymacja(21, value_f2, value_g2,"g_2_2.out", "G_2_2.out","g_2_n21");
    aproksymacja(51, value_f2, value_g2,"g_2_3.out", "G_2_3.out","g_2_n51");
    aproksymacja(101, value_f2, value_g2,"g_2_4.out", "G_2_4.out","g_2_n101");

    return 0;
}