#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
double w;/*正弦力场频率*/
double E;/*随机行走概率中场的影响大小*/
int seedx;/*种子值*/

int OnedimensionRW( int a, int m, int r, int q, int N){   /*粒子的一维随机行走*/ 
	double x;/*x是随机数*/ 
    int n;/*循环变量*/ 
    int I;/*随机数生成的In*/
    int S;/*向力场方向行走步数*/ 

	S = 0;/*初始化S*/
    I = seedx;/*将种子值赋给I0*/
    
    for( n = 0; n < N; n ++) {                   /*用In求出xn、行走方向,然后用 Schrage方法求In+1*/ 
	
	x = (double)I/m;
	
	if(0 < x && x < (1-E*sin(w*n))*0.5)            /*判断行走方向,更新位置，报错*/
	S --;
	else if(x > (1-E*sin(w*n))*0.5 && x<1 )
	S++;
	else{
		printf("Error.\n");
		return -1;
	}

	I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
	
	}
    seedx = I;
	return S;
}
int main() {
	int a,b,m,r,q,N,seed,NN;/*Schrage方法所需数据*//*N是粒子步数，NN是粒子*/ 
	int n;/*n是循环语句用到的变量，h是报错用的变量*/
	int x,S,T;/*x是一次随机行走的位移量，S是多个粒子的x之和，T是粒子的位移平方之和*/ 
	
	printf("Please input seed x.");/*输入种子值*/
	scanf("%d", &seedx) ;
	
	printf("Please input the step of each particle.");/*输入单粒子步数*/
	scanf("%d", &N) ;
	
	printf("Please input frequency.");/*输入力场频率*/
	scanf("%f", &w) ;
	
	printf("Please input the value of e.");/*输入力场频率*/
	scanf("%f", &E) ;
	
	printf("Please input the number of particle.");/*输入粒子数*/
	scanf("%d", &NN) ;
	
    a=16807;               /*生成Schrage方法所需数据*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	for(n=0; n < NN; n ++) {
		x = OnedimensionRW(a,m,r,q,N);/*进行NN个粒子的N步一维随机行走*/
		S += x;
		T += x*x;
	}
    
    printf("<x>=%f\n<x^2>=%f\n<Δx^2>=%f\n",(double)S/NN,(double)T/NN,(double)T/NN-pow((double)S/NN,2.0));
    
	return 0; 
}
