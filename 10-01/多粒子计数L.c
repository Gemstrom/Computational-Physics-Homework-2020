#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
#define f(N) F0/M/(1+1/(pow(M*w*B,2.0)))*((1-cos((double)N))/(pow(w,3.0)*M*B)-sin((double)N*w)/pow(w,2.0)-(exp(-(double)N/M/B)-1)/(w*M*B))
double M,B,w,F0,Fr;/*粒子质量，粘滞系数相关的常数，正弦力场频率，正弦力场振幅，涨落力的振幅*/

int seedx,seedy;/*x,y种子值*/

float Langevin( int a, int m, int r, int q, int N){   /*粒子的一维随机行走*/ 
    double x,y,X,Y,xx;/*用于Box-Muller抽样的数*/ 
    int n;/*循环变量*/ 
    int Ix, Iy;/*随机数生成的In*/
    float S,v;/*位移,速度*/
    
    S = 0;/*初始化位置*/ 
    v = 0;/*初始化速度*/
    Ix = seedx; /*将种子值赋给I0*/
    Iy = seedy;
    
    for(n=0;n<N;n++) {                      /*用 Schrage方法求Ix,Iy，然后得到x,y*/ 
		
		x = (double)Ix/m;                    /*生成xn*/ 
		y = (double)Iy/m;                   /*生成yn*/
		
		Ix= a * (Ix%q)- r*((Ix-(Ix%q))/q);      /*生成In+1*/ 
		if( Ix < 0 )
		Ix += m ;
		
		Iy= a * (Iy%q)- r*((Iy-(Iy%q))/q);      /*生成In+1*/ 
		if( Iy < 0 )
		Iy += m ;
		
		X = 2*x -1;/*Box-Muller抽样*/
		Y = 2*y -1;
		
		if(pow(X,2.0)+pow(Y,2.0) > 1){
			n--;
			continue;
		}
		
		xx = X * sqrt(-2*log(pow(X,2.0)+pow(Y,2.0))/(pow(X,2.0)+pow(Y,2.0)));
		
		S += v; /*更新位移*/
		v = (1-1.0/M/B)*v + Fr * xx /M;/*更新速度*/ 
		
	}
    
    return S; 
}
int main() {
	int a,b,m,r,q,N,NN;/*Schrage方法所需数据;*N是粒子步数，NN是粒子*/ 
	int n;/*n是循环语句用到的变量*/
	float x,S,T;/*x是一次随机行走的位移量，S是多个粒子的x之和，T是粒子的位移平方之和*/ 
	
	printf("Please input seed x.");/*输入种子值*/
	scanf("%d", &seedx) ;
	printf("Please input seed y.");
	scanf("%d", &seedy) ;
	
	printf("Please input the step.");/*输入数据量*/
	scanf("%d", &N) ;
	
	printf("Please input frequency.");/*输入力场频率*/
	scanf("%lf", &w) ;
	
	printf("Please input m.");/*输入粒子质量*/
	scanf("%lf", &M) ;
	
	printf("Please input F0（force field）.");/*输入正弦力大小*/
	scanf("%lf", &F0) ;
	
	printf("Please input Fr（random force）.");/*输入随机力大小*/
	scanf("%lf", &Fr) ;
	
	printf("Please input B.");/*输入粘滞系数项*/
	scanf("%lf", &B) ;
	
	printf("Please input the number of particle.");/*输入单粒子步数*/
	scanf("%d", &NN) ;
	
	
    a=16807;               /*生成Schrage方法所需数据*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	
    for(n=0; n < NN; n ++) {
		x = Langevin(a,m,r,q,N);/*进行NN个粒子的N步一维随机行走*/
		S += x;
		T += x*x;
	}
	
	printf("<x>=%f\n<x^2>=%f\n<Δx^2>=%f\n",S/NN,T/NN,T/NN-pow((double)S/NN,2.0));
	
	return 0; 
}
