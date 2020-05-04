#include <stdio.h>
#include</usr/include/gsl/gsl_eigen.h>
#include</usr/include/gsl/gsl_complex.h>
#include</usr/include/gsl/gsl_complex_math.h>
#include <math.h>

/*
    Odnośnie wykresów wektorów własnych zdaję sobie sprawę, że nie pokrywaja się 
    z tymi z wyniki.pdf, nie do końca wiem dlaczego niektóre struny wyświetlane 
    są w sposób poprawny, a niektóre wyglądają, jakby gdzieś przed nimi zakradł 
    się minus. A wykres wektorów własnych dla alfa = 0 już w ogóle wygląda, jakby
    był odwrócony do góry nogami.

*/

double x_i(int i, int L, float dx){
    return (-L/2. +dx*(i + 1.0));
}

double rho(double x, double alpha){
    return 1+4*alpha*x*x;
}

void struna(int alpha, FILE *file_ptr, int flag){
    int n = 200, L = 10, N = 1;
    double dx = (double)L/(n + 1);

    
    gsl_matrix *A = gsl_matrix_calloc(n,n);
    gsl_vector_complex *eval = gsl_vector_complex_calloc(n);
    gsl_matrix_complex *evec = gsl_matrix_complex_calloc(n,n);
    gsl_eigen_nonsymmv_workspace *w = gsl_eigen_nonsymmv_alloc(n);

    int i, j;

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i==j){
                gsl_matrix_set(A,i,j,2*(double)N/(dx*dx*rho(x_i(i,L,dx),alpha)));
            }else if(i == j + 1 || i == j - 1){
                gsl_matrix_set(A,i,j,-(double)N/(dx*dx*rho(x_i(i,L,dx),alpha)));
            }else{
                gsl_matrix_set(A,i,j,0);
            }
        }
    }
/*
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%f ",gsl_matrix_get(A, i, j));
        }
        printf("\n");
    }
    */
    gsl_eigen_nonsymmv(A, eval, evec, w);
    gsl_eigen_nonsymmv_sort(eval,evec,GSL_EIGEN_SORT_ABS_ASC);

    
    if(flag){
        int nr;
        for(i=0; i<n; i++){
            fprintf(file_ptr,"%f\t",x_i(i,L,dx));
            for(nr=0;nr<6;nr++){
                gsl_complex cv = gsl_matrix_complex_get(evec, i, nr);
                if(nr==5){
                    fprintf(file_ptr,"%f\n",-GSL_REAL(cv));
                }else if(nr==2){ 
                    fprintf(file_ptr,"%f\t",-GSL_REAL(cv));
                }else{
                    fprintf(file_ptr,"%f\t",GSL_REAL(cv));
                }
            }
            
        }

    }else{
        double val;
        for(i=0;i<6;i++){
        gsl_complex cval = gsl_vector_complex_get(eval,i);
        val = GSL_REAL(cval);
        //printf("%f\n",sqrt(val));
        if(i==5){
            fprintf(file_ptr,"%f\n",sqrt(val));
        }else{
            fprintf(file_ptr,"%f\t",sqrt(val));
        }
    }
    }
    
    gsl_vector_complex_free(eval);
    gsl_matrix_complex_free(evec);
    gsl_eigen_nonsymmv_free(w);
    gsl_matrix_free(A);
}

int main(){
    int i;
    FILE *file_ptr=fopen("out1.txt","a");
    //fprintf(file_ptr,"Alpha\tw0\tw1\tw2\tw3\tw4\tw5\n");
    for(i=0;i<=100; i+=2){
        fprintf(file_ptr,"%d\t",i);
        struna(i,file_ptr,0);
    }

    fclose(file_ptr);

    file_ptr=fopen("out2.txt","a");
    struna(0,file_ptr,1);
    fclose(file_ptr);

    file_ptr=fopen("out3.txt","a");
    struna(100,file_ptr,1);
    fclose(file_ptr);

    return 0;
}