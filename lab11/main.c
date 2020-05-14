#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nr.h"
#include "nrutil.h"

float losuj_x(){
    return rand()/(RAND_MAX+1.0);
}

float losuj_y(){
    return rand()/(RAND_MAX+1.0);
}

int sign(){
    if(losuj_y()>0.5){
        return 1;
    }else{
        return -1;
    }
}

float a_szum(){
    return 2*sign()*losuj_x();
}

float omega(int n){
    return 4*M_PI/n;
}

float y_0(int i, int n){
    return sin(omega(n)*i) + sin(2*omega(n)*i) + sin(3*omega(n)*i);
}

float y_0_do_wykresow(int i, int n, const char *plik){
    return sin(omega(n)*i) + sin(2*omega(n)*i) + sin(3*omega(n)*i);
}

float y_i(int i, int n, FILE *file){
    float y = y_0(i, n);
    fprintf(file,"%d %f\n", i, y);
    return y + a_szum();
}

float znajdz_max(float *data, int n){
    int i;
    float tmp = data[1];
    for(int i= 1;i<n+1;i++){
        if(tmp <= data[i]){
            tmp = data[i];
        }
    }
    return tmp;
}

void transformata_sin(int k, const char *plik1, const char *plik2, const char *plik3, const char *plik4){

    FILE *file_ptr1 = fopen(plik1, "w");
    FILE *file_ptr2 = fopen(plik2, "w");
    FILE *file_ptr3 = fopen(plik3, "w");
    FILE *file_ptr4 = fopen(plik4, "w");

    int n=pow(2,k);
    float data[n];
    int i;
    for(i = 1; i < n + 1; i++){
        data[i]=y_i(i, n, file_ptr4);
    }

    for(i = 1; i < n + 1; i++){
        fprintf(file_ptr1, "%d %f\n", i, data[i]);
    }

    sinft(data, n);

    for(i = 1; i < n + 1; i++){
        fprintf(file_ptr2, "%d %f\n", i, data[i]);
    }

    float max = znajdz_max(data, n);

    //printf("%f\n", max);

    for(i = 1; i < n + 1; i++){
        if(fabs(data[i]) < max/4){
            data[i] = 0;
        }
        //printf("%d %f\n", i, data[i]);
    }

    sinft(data, n);
    //printf("%f\n",2/n);
    for(i = 1; i < n + 1; i++){
        //printf("%d %f\n", i, data[i]);
        data[i] *= 2.0/n;
    }

    for(i = 1; i < n + 1; i++){
        fprintf(file_ptr3, "%d %f\n", i, data[i]);
    }

    fclose(file_ptr1);
    fclose(file_ptr2);
    fclose(file_ptr3);
    fclose(file_ptr4);
}

int main(){

    transformata_sin(10, "1_1.out", "2_1.out", "3_1.out", "niezaszumiony1.out");
    transformata_sin(6, "1_2.out", "2_2.out", "3_2.out", "niezaszumiony2.out");
    transformata_sin(8, "1_3.out", "2_3.out", "3_3.out", "niezaszumiony3.out");

    return 0;
}