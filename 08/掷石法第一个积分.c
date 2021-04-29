#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define F(x) sqrt(x+sqrt(x))
int main() {
	double x,y;/*Schrage方法生成随机数对*/ 
	int a,b,m,r,q,N,seed;/*Schrage方法所需数据*/
	int Q;/*落在函数下方的点数*/
	int n;/*循环变量*/ 
    int I;/*随机数生成的In*/
    
    
	a=16807;               /*生成Schrage方法所需数据*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*输入数据量*/
	scanf("%d", &N) ;

    
    I = seed; /*将种子值赋给I0*/
    
    for(n=0;n<N;n++) {                      /*用 Schrage方法求I，然后得到x,y*/ 
		
		if(n == 0) 
		x = (double)I/m;                    /*生成xn*/ 
		else
		x = y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
		
		y = (double)I/m;                   /*生成x(n+1)=yn*/
	
	
		if(F(2.0)*y <= F(2*x))
		Q++;
		
	}
    
    printf("%f",2*F(2.0)*(double)Q/N);
    
    return 0; 
	
}
