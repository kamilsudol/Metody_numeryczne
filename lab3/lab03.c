#include <stdio.h>
#include <math.h>

void jakobi(float beta, float F0, float Omeg,const char *x){
    FILE *fileptr;
    fileptr=fopen(x,"w");

    float h=0.02;
    int omega=1;
    int N=2000;
    float d0[N],d1[N-1],d2[N-2];
    float V0=1;
    float B[N];
    B[0]=V0;
    B[1]=0;


    int i;


    for(i=2;i<N;i++){
        B[i]=F0*h*h*sin(Omeg*h*i);
    }

    
    float a1=1,a2=omega*omega*h*h-2-beta*h,a3= 1+beta*h;
    for(i=0;i<N;i++){
        if(i<2){
            d0[i]=a1;
        }else{
            d0[i]=a3;
        }
        if(i==0){
            d1[i]=0;
        }else if(i==1){
            d1[i]=-1;
        }else if(i>1){
            d1[i]=a2;
        }
        
        if(i>1){
            d2[i]=a1;
        }else{
            d2[i]=0;
        }
    }
    
    for(i=0;i<N;i++){
        printf("%f %f %f %f\n",d0[i],d1[i],d2[i],B[i]);
    }
    float xs[N],xn[N];
    for(i=-2;i<N-2;i++){
        xs[i]=1;
    }
    int j=0;

    for(j=0;j<4000;j++){
        for(i=0;i<N;i++){
            xn[i]=(1/d0[i])*(B[i]-d1[i]*xs[i-1]-d2[i]*xs[i-2]);
        }
        for(i=0;i<N;i++){
            xs[i]=xn[i];
        }
    }
    

    for(i=0;i<N;i++){
        //printf("%d %f\n",i,xn[i]);
        fprintf(fileptr,"%d %f\n",i,xn[i]);
    }
    
    fclose(fileptr);

}

int main(){
    jakobi(0.0,0,0.8,"out1");
    jakobi(0.4,0,0.8,"out2");
    jakobi(0.4,0.1,0.8,"out3");
}