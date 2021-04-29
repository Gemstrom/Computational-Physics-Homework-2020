#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define alpha 1.0/*积分参数alpha,beta*/
#define beta 2.0
#define a 16807/*Schrage方法数据*/
#define m 2147483647
#define r 2836
#define q 127773
int I;/*Schrage方法生成的随机数*/ 
int n;/*n是热化步骤数*/
int N;/*N是抽样步骤*/

int MH(double gamma) {
	double Integrate = 0;/*存储积分值*/ 
	int T = 0;/*选取步数计数*/
	double R,Q;/*Schrage方法生成的随机数*/
	double xi, X;/*随机取样点xi,x'*/ 
	double r0;/*MH抽样中是否行走的判据*/ 
	int i;/*循环变量*/
	double delta;/*误差*/
	
	xi = 1;/*x0=1*/
	
	for(i = 0; i< n; i++ ){/*热化,舍去x0到xn*/
	    do{
			R = (double)I/m;/*Schrage方法生成R,保证R在lnx定义域*/ 
			I= a * (I%q)- r*((I-(I%q))/q); 
	     	if( I < 0 )
		    I = I + m ;
		} 
		while (R == 0);
	    
	    X = - gamma * log(R);
	    r0 = pow( (X/xi) , alpha - 1 ) * exp(-(X - xi)/ beta)*exp((X-xi)/gamma);
	    
		Q = (double)I/m;/*生成Q*/
		
		if (Q < 1 && Q < r0 ){
	    	xi = X;/*当R<min(1,r0)时移动一步否则xi不变*/
		}
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*生成新的随机数I*/ 
		if( I < 0 )
		I = I + m ;
    }
    
    
    for(i = 0; i< N; i++ ){/*抽样*/
	    
		do{
			R = (double)I/m;/*Schrage方法生成R,保证R在lnx定义域*/ 
			I= a * (I%q)- r*((I-(I%q))/q); 
	     	if( I < 0 )
		    I = I + m ;
		} 
		while (R == 0 );
		
	    X = - gamma * log(R);
	    r0 = pow( (X/xi) , alpha - 1 ) * exp(-(X - xi)/ beta)*exp((X-xi)/gamma);
	    
		Q = (double)I/m;/*生成Q*/
		
		if (Q < 1 && Q < r0 ){
	    	xi = X;/*当R<min(1,r0)时移动一步否则xi不变*/
		    T ++;
		}
		
		Integrate +=  pow((xi - alpha * beta ), 2.0);/*xn+1到xn+N用于抽样所以是N个数*/
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
    }
	
	delta =  ((double)Integrate/N - alpha * pow(beta, 2.0))/(alpha * pow(beta, 2.0));
	
	printf("I = %f\ndelta = %f\neta = %f\n", (double)Integrate/N, delta, (double)T/N ) ;
	
	return 0;
}
int main(){
	int seed;/*seed是种子值*/
	int h;/*报错变量*/ 
	double gamma;/*M-H抽样的参数*/ 
	
	printf("Please input seed.");/*输入种子值*/
	scanf("%d", &I) ;
	
	printf("Please input the step of heating process.");/*输入热化步骤数目*/
	scanf("%d", &n) ;
	
	printf("Please input the step of sampling.");/*输入抽样步骤数*/
	scanf("%d", &N) ;
	 
	 
	printf("Please input gamma.");/*输入gamma值*/
	scanf("%lf", &gamma) ;
	
	h = MH(gamma) ;/*积分，输出，检查是否错误*/
	if(h != 0 ) /*报错*/
	printf("Error.\n");
}
