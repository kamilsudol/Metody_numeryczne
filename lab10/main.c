#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float function1(float x){
    return log(pow(x,5)+3*pow(x,2)+x + 9);
}

float function2(float x){
    return pow(x,6);
}

float iloraz_roz_1(float (*fun)(float), float x1, float x2){
    return (fun(x2)-fun(x1))/(x2-x1);
}

float iloraz_roz_2(float (*fun)(float), float x1, float x2, float x3){
    return (iloraz_roz_1(fun,x2,x3)-iloraz_roz_1(fun,x1,x2))/(x3-x1);
}

float x_m(float (*fun)(float x), float x1, float x2, float x3){
    return (((x2+x1)/2)- (iloraz_roz_1(fun, x1, x2)/(2*iloraz_roz_2(fun,x1,x2,x3))));
}

void zamien(float *x1, float *x2, float *x3, float xm){
    float dl1, dl2, dl3;
    dl1 = pow(pow(*x1,2)+pow(xm,2),0.5);
    dl2 = pow(pow(*x2,2)+pow(xm,2),0.5);
    dl3 = pow(pow(*x3,2)+pow(xm,2),0.5);

    if(dl1>dl2){
        if(dl1>dl3){
            *x1=xm;
        }else{
            *x3=xm;
        }
    }else{
        if(dl2>dl3){
            *x2=xm;
        }else{
            *x3=xm;
        }
    }
}

void rysuj_wykres(float xp, float xk, const char* plik, float (*fun)(float)){
    FILE *file_ptr = fopen(plik, "w");
    float i;
    for(i = xp; i <= xk; i+=0.01){
        fprintf(file_ptr,"%f %f\n", i, fun(i));
    }

    fclose(file_ptr);
}

void powell(float x1, int n,float (*fun)(float), const char* plik){

    FILE *file_ptr = fopen(plik, "w");

    float h = 0.01;
    float x2=x1+h;
    float x3=x1+2*h;
    float xm;
    int i;

    for(i=0;i<n;i++){
        xm=x_m(fun,x1,x2,x3);
        //printf("%f %f %f %f %f %f\n",x1,x2,x3,xm, iloraz_roz_1(fun,x1,x2),iloraz_roz_2(fun,x1,x2,x3));
        fprintf(file_ptr, "%f %f %f %f %f %f\n",x1,x2,x3,xm, iloraz_roz_1(fun,x1,x2),iloraz_roz_2(fun,x1,x2,x3));
        zamien(&x1,&x2,&x3,xm);
    }
    fclose(file_ptr);
}

int main(){
    rysuj_wykres(-1.5, 1, "logarytm.out", function1);
    rysuj_wykres(0, 5, "jednomian.out", function2);
    powell(-0.5, 10, function1, "1.out");
    powell(-0.9, 10, function1, "2.out");
    powell(1.5, 100, function2, "3.out");

    return 0;
}