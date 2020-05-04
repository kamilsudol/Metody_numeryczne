#include <stdio.h>
#include </usr/include/gsl/gsl_linalg.h>

int main(){
	
	int sigma = 2;	
	int n = 4;

	float det_A;
	
    gsl_matrix *A = gsl_matrix_calloc(n, n);
	gsl_matrix *B= gsl_matrix_calloc(n, n);
	
	gsl_permutation *p = gsl_permutation_alloc(n);

    FILE *fileptr;
    fileptr = fopen("out", "w");
    fprintf(fileptr, "Macierz A:\n");

    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            gsl_matrix_set(A,i,j,1.0/(i+j+sigma));
            gsl_matrix_set(B,i,j,gsl_matrix_get(A,i,j));
            fprintf(fileptr, "%f ", gsl_matrix_get(A, i, j));
        }
        fprintf(fileptr,"\n");
    }
    fprintf(fileptr,"\n");

    gsl_linalg_LU_decomp(A,p,&sigma);

    

    for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			printf("%f ", gsl_matrix_get(A, i, j));
		}
		printf("\n");
	}
	
	printf("\nElementy diagonalne U\n");
	fprintf(fileptr, "Elementy diagonalne U\n");

    det_A = 1;
	
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			if(i == j) {
				fprintf(fileptr, "%f ", gsl_matrix_get(A, i, j));
				det_A *= gsl_matrix_get(A, i, j);
                printf("%f\n",det_A);
			}
		}
	}
    fprintf(fileptr,"\n");
	
	printf("\nWyznacznik Macierzy a: %g\n", det_A);
	fprintf(fileptr, "\nWyznacznik Macierzy a: %g\n", det_A);

    gsl_vector *D = gsl_vector_calloc(n);
	
	gsl_vector *x1 = gsl_vector_calloc(n);
	gsl_vector *x2 = gsl_vector_calloc(n);
	gsl_vector *x3 = gsl_vector_calloc(n);
	gsl_vector *x4 = gsl_vector_calloc(n);

    gsl_vector_set_zero(D);
	gsl_vector_set(D, 0, 1);
	gsl_linalg_LU_solve(A ,p, D, x1);
	
	gsl_vector_set_zero(D);
	gsl_vector_set(D, 1, 1);
	gsl_linalg_LU_solve(A ,p, D, x2);
	
	gsl_vector_set_zero(D);
	gsl_vector_set(D, 2, 1);
	gsl_linalg_LU_solve(A ,p, D, x3);
	
	gsl_vector_set_zero(D);
	gsl_vector_set(D, 3, 1);
	gsl_linalg_LU_solve(A ,p, D, x4);

    fprintf(fileptr,"\n");
    printf("Macierz odwrotna A^-1:\n");
    fprintf(fileptr,"Macierz odwrotna A^-1:\n");

    for(i = 0; i < n; i++) {
		printf("%f	  ",gsl_vector_get(x1, i));
		fprintf(fileptr, "%f	",gsl_vector_get(x1, i));
		
		printf("%f	  ",gsl_vector_get(x2, i));
		fprintf(fileptr, "%f	", gsl_vector_get(x2, i));
		
		printf("%f	  ",gsl_vector_get(x3, i));
		fprintf(fileptr, "%f	", gsl_vector_get(x3, i));
		
		printf("%f   \n",gsl_vector_get(x4, i));
		fprintf(fileptr, "%f\n", gsl_vector_get(x4, i));
	}

    gsl_matrix *A_odwrotna = gsl_matrix_calloc(n, n);
	
	for(i = 0; i < n; i++) {
		gsl_matrix_set(A_odwrotna, 0, i, gsl_vector_get(x1, i));
		gsl_matrix_set(A_odwrotna, 1, i, gsl_vector_get(x2, i));
		gsl_matrix_set(A_odwrotna, 2, i, gsl_vector_get(x3, i));
		gsl_matrix_set(A_odwrotna, 3, i, gsl_vector_get(x4, i));
	}
	
    gsl_matrix *C = gsl_matrix_calloc(n, n);

    int k;
    printf("\nIloczyn AA^-1:\n");
    fprintf(fileptr,"\nIloczyn AA^-1:\n");


    for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			for(k = 0; k < n; k++) {
				gsl_matrix_set(C, i, j, gsl_matrix_get(C, i, j) + gsl_matrix_get(B, i, k) * gsl_matrix_get(A_odwrotna, k, j));
			}
			fprintf(fileptr, "%g	", gsl_matrix_get(C, i, j));
			printf("%g	  ", gsl_matrix_get(C, i, j));
		}
		printf("\n");
		fprintf(fileptr, "\n");
	}

    gsl_matrix_free(A);
    gsl_matrix_free(B); 
    gsl_matrix_free(C); 
    gsl_matrix_free(A_odwrotna); 

    gsl_vector_free(D);
    gsl_vector_free(x1);
    gsl_vector_free(x2);
    gsl_vector_free(x3);
    gsl_vector_free(x4);
    
    gsl_permutation_free(p);


	
	return 0;
}
