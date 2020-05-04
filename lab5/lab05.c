#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double **maker(double **A,int n){
    A=(double**)malloc(n*sizeof(double*));
    int i,j;
    for(i=0;i<n;i++){
        *(A+i) = (double*)malloc(n*sizeof(double));
        for(j=0;j<n;j++){
            A[i][j]=0;
        }
    }
    return A;
}

double *multi1(double **A, double *B, double *C, int n){
    int i,j;
    for(i=0;i<n;i++){
        C[i]=0;
        for(j=0;j<n;j++){
            C[i] += A[i][j]*B[j];
        }
    }
    return C;
}

double multi2(double *A, double *B, int n){
    double res=0;
    int i;
    for(i = 0;i<n;i++){
        res += A[i]*B[i];
    }
    return res;
}

double **multi3(double **A, double **B, double **C, int n){
    int i,j,k;
    double sum=0;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            sum=0;
            for(k=0;k<n;k++){
                sum+=A[i][k]*B[k][j];
            }
            C[i][j]=sum;
        }
    }
    return C;
}

double normal(double *A, int n){
    double res=0;
    int i;
    for(i = 0;i<n;i++){
        res += pow(A[i],2);
    }
    return sqrt(res);
}

double *divider(double *A, double x, double *B, int n){
    int i;
    for(i=0;i<n;i++){
        B[i]=A[i]/x;
    }
    return B;
}

double **tensor(double **A, double lambd, double *B, double **C, int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            C[i][j] = A[i][j] - (lambd*B[i]*B[j]);
        }
    }
    return C;
}

double **filler(double **A, double *B, int j, int n){
    int i;
    for(i=0;i<n;i++){
        A[i][j] = B[i];
    }
    return A;
}

double **transpose(double **A, double **B, int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            B[j][i]=A[i][j];
        }
    }
    return B;
}

void destroyer(double **A, int n){
    int i, j;
    for(i=0;i<n;i++){
        free(*(A+i));
    }
    free(A);
}

void met_pot(FILE *fp1, FILE *fp2, FILE *fp3){

    int n = 7, IT_MAX = 12;
    double **A=NULL;
    A=maker(A,n);
    int i,j,k,l=1;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            A[i][j]= 1/sqrt(2+fabs(i-j));
        }
    }
    /*
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%f ",A[i][j]);
        }
        printf("\n");
    }*/
    
    double **W=NULL;
    W=maker(W,n);

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            W[i][j]=A[i][j];
        }
    }

    double **Wn=NULL;
    Wn=maker(Wn,n);
    double **X=NULL;
    X=maker(X,n);
    double **AX=NULL;
    AX=maker(AX,n);
    double **XT=NULL;
    XT=maker(XT,n);
    double **D=NULL;
    D=maker(D,n);

    double *Xk0 = malloc(n*sizeof(double));
    double *Xn = malloc(n*sizeof(double));

    for(i=0;i<n;i++){
        
        for(j=0;j<n;j++){
            Xk0[i]=1;
        }
        double lambd=0;
        
        for(j=0;j<IT_MAX;j++){
            
            for(k=0;k<n;k++){
                Xn[k]=0;
            }
            Xn=multi1(W,Xk0,Xn,n);
            lambd = multi2(Xn,Xk0,n)/normal(Xk0,n);
            fprintf(fp3,"%d %f\n",l,lambd);
            Xk0=divider(Xn,normal(Xn,n),Xk0,n);
            l++;
        }
        l=1;
        fprintf(fp3,"\n\n");
        printf("lambd[%d]: %f\n",i,lambd);
        fprintf(fp1,"lambd[%d]: %f\n",i,lambd);
        Wn = tensor(W,lambd, Xk0,Wn,n);
        
        for(j=0;j<n;j++){
            for(k=0;k<n;k++){
                W[j][k]=Wn[j][k];
            }
        }
        X=filler(X,Xk0,i,n);
    }

    AX=multi3(A,X,AX,n);
    XT=transpose(X,XT,n);
    D=multi3(XT,AX,D,n);

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%f ",D[i][j]);
            fprintf(fp2,"%f ",D[i][j]);
        }
        printf("\n");
        fprintf(fp2,"\n");
    }

    destroyer(A,n);
    destroyer(W,n);
    destroyer(Wn,n);
    destroyer(X,n);
    destroyer(XT,n);
    destroyer(D,n);
    destroyer(AX,n);

    free(Xk0);
    free(Xn);
}

int main(){

    FILE *lamb = fopen("lambdy.out","w"), *matrix = fopen("macierz.out","w"), *iter=fopen("iteracje.out","w");
    met_pot(lamb,matrix,iter);
    fclose(lamb);
    fclose(matrix);
    fclose(iter);

    return 0;
}