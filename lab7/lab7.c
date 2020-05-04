#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
Tym razem postarałem się posprawdzać wszystko po pięć razy, 
żeby zapobiec głupim błędom takich, jak na przykład złe dane 
na wejściu w moim ostatnim kodzie :)

Wesołych Świąt! ^^
*/

double wielomian(int n, double x, double *A, double **B){
    double suma = 0;
    int i, j;
    for(i=0;i<n+1;i++){
        double iloczyn = 1;
        for(j=0;j<=i-1;j++){
            iloczyn*=(x-*(A+j));
        }
        suma+=*(*(B+i)+i)*iloczyn;
    }
    return suma;
}

void interpolacja_row(int n, const char * plik){

    FILE *file_ptr = fopen(plik,"a");

    double x_min = -5, x_max = 5;
    double *A = (double *)malloc((n+1)*sizeof(double));
    double **B = (double **)malloc((n+1)*sizeof(double*));
    int i, j;

    for(i=0;i<n+1;i++){
        *(B+i) = (double *)malloc((n+1)*sizeof(double));
    }

    *(A+0) = x_min;

    for(i=1;i<n+1;i++){
        *(A+i) = *(A+i-1)+(x_max-x_min)/n;
        *(*(B+i)+0) = 1/(1+pow(*(A+i),2));
    }

    for(i=1;i<n+1;i++){
        for(j=i;j<n+1;j++){
            *(*(B+j)+i)=(*(*(B+j)+i-1)-*(*(B+j-1)+i-1))/(*(A+j)-*(A+j-i));
        }
    }

    double k;

    for(k=x_min;k<=x_max;k = k + 0.01){
        fprintf(file_ptr,"%f %f\n",k,wielomian(n,k,A,B));
    }

    fprintf(file_ptr,"\n\n");

    free(A);

    for(i=0;i<n+1;i++){
        free(*(B+i));
    }

    free(B);
    fclose(file_ptr);
}

void interpolacja_opt(int n, const char * plik){

    FILE *file_ptr = fopen(plik,"a");

    double x_min = -5, x_max = 5;
    double *A = (double *)malloc((n+1)*sizeof(double));
    double **B = (double **)malloc((n+1)*sizeof(double*));
    int i, j;

    for(i=0;i<n+1;i++){
        *(B+i) = (double *)malloc((n+1)*sizeof(double));
    }

    for(i=0;i<n+1;i++){
        *(A+i) = 0.5*((x_min-x_max)*cos(M_PI*(2*i+1)/(2*n+2))+(x_min+x_max));
        *(*(B+i)+0) = 1/(1+pow(*(A+i),2));
    }

    for(i=1;i<n+1;i++){
        for(j=i;j<n+1;j++){
            *(*(B+j)+i)=(*(*(B+j)+i-1)-*(*(B+j-1)+i-1))/(*(A+j)-*(A+j-i));
        }
    }

    double k;

    for(k=x_min;k<=x_max;k = k + 0.01){
        fprintf(file_ptr,"%f %f\n",k,wielomian(n,k,A,B));
    }

    fprintf(file_ptr,"\n\n");

    free(A);

    for(i=0;i<n+1;i++){
        free(*(B+i));
    }

    free(B);
    fclose(file_ptr);
}

int main(){

    interpolacja_row(5,"rownolegle1.out");
    interpolacja_row(10,"rownolegle2.out");
    interpolacja_row(15,"rownolegle3.out");
    interpolacja_row(20,"rownolegle4.out");

    interpolacja_opt(5,"optymalizacja1.out");
    interpolacja_opt(10,"optymalizacja2.out");
    interpolacja_opt(15,"optymalizacja3.out");
    interpolacja_opt(20,"optymalizacja4.out");

    return 0;
}