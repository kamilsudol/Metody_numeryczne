#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

double complex reszta(double complex *A, double complex * B, int l, double complex zj){
    *(B+l) = 0;
    int i;
    for(i = l-1; i>=0 ;i--){
        *(B+i) = *(A+i+1) + (*(B+i+1))*zj;
    }
    return *(A+0)+(*(B+0))*zj;
}

void znajdz_zera(double complex *a, int itermax, double complex z0, FILE *file_ptr){

    double complex zj = 0.0+0.I;
    double complex rj = 0.0+0.I;
    double complex rj_p = 0.0+0.I;
    double complex *tabB;
    tabB = (double complex *)malloc(5*sizeof(double complex));
    double complex *tabC;
    tabC = (double complex *)malloc(5*sizeof(double complex));
    int i,j,stopien_wielomianu = 4;

    for(i = stopien_wielomianu; i >= 1; i--){
        zj = z0;
        fprintf(file_ptr, "%f  %f\n", creal(zj), cimag(zj));
        for(j=0; j<itermax; j++){
            rj = reszta(a, tabB, i, zj);
            rj_p = reszta(tabB, tabC, i-1, zj);
            zj = zj - (rj/rj_p);
            fprintf(file_ptr, "%f  %f\n", creal(zj), cimag(zj));
            //printf("%f  %f\n", creal(zj), cimag(zj));
        }
        fprintf(file_ptr, "\n");
        
        for(j=0; j<stopien_wielomianu; j++){
            *(a+j)=(*(tabB+j));
        }
    }

    free(tabB);
    free(tabC);
}

int main(){

    int it_max = 20;
    FILE *file_ptr1 = fopen("out1","w");
    FILE *file_ptr2 = fopen("out2","w");
    double complex * tabA;
    tabA= (double complex *)malloc(5*sizeof(double complex));
    *(tabA+0)=16.0+8.I;
    *(tabA+1)=-20.0 +14.I;
    *(tabA+2)=4.0 - 8.I;
    *(tabA+3)=-4.0+1.I;
    *(tabA+4)=1.0 +0.I;

    double complex z01 = 0.0+0.I;
    double complex z02 = -10.0-10.I;
    
    znajdz_zera(tabA, it_max, z01, file_ptr1);

    *(tabA+0)=16.0+8.I;
    *(tabA+1)=-20.0 +14.I;
    *(tabA+2)=4.0 - 8.I;
    *(tabA+3)=-4.0+1.I;
    *(tabA+4)=1.0 +0.I;

    znajdz_zera(tabA, it_max, z02, file_ptr2);

    fclose(file_ptr1);
    fclose(file_ptr2);
    free(tabA);

    return 0;
}