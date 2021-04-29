#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define alpha 1.0/*���ֲ���alpha,beta*/
#define beta 2.0
#define a 16807/*Schrage��������*/
#define m 2147483647
#define r 2836
#define q 127773
int I;/*Schrage�������ɵ������*/ 
int n;/*n���Ȼ�������*/
int N;/*N�ǳ�������*/

int MH(double gamma) {
	double Integrate = 0;/*�洢����ֵ*/ 
	int T = 0;/*ѡȡ��������*/
	double R,Q;/*Schrage�������ɵ������*/
	double xi, X;/*���ȡ����xi,x'*/ 
	double r0;/*MH�������Ƿ����ߵ��о�*/ 
	int i;/*ѭ������*/
	double delta;/*���*/
	
	xi = 1;/*x0=1*/
	
	for(i = 0; i< n; i++ ){/*�Ȼ�,��ȥx0��xn*/
	    do{
			R = (double)I/m;/*Schrage��������R,��֤R��lnx������*/ 
			I= a * (I%q)- r*((I-(I%q))/q); 
	     	if( I < 0 )
		    I = I + m ;
		} 
		while (R == 0);
	    
	    X = - gamma * log(R);
	    r0 = pow( (X/xi) , alpha - 1 ) * exp(-(X - xi)/ beta)*exp((X-xi)/gamma);
	    
		Q = (double)I/m;/*����Q*/
		
		if (Q < 1 && Q < r0 ){
	    	xi = X;/*��R<min(1,r0)ʱ�ƶ�һ������xi����*/
		}
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*�����µ������I*/ 
		if( I < 0 )
		I = I + m ;
    }
    
    
    for(i = 0; i< N; i++ ){/*����*/
	    
		do{
			R = (double)I/m;/*Schrage��������R,��֤R��lnx������*/ 
			I= a * (I%q)- r*((I-(I%q))/q); 
	     	if( I < 0 )
		    I = I + m ;
		} 
		while (R == 0 );
		
	    X = - gamma * log(R);
	    r0 = pow( (X/xi) , alpha - 1 ) * exp(-(X - xi)/ beta)*exp((X-xi)/gamma);
	    
		Q = (double)I/m;/*����Q*/
		
		if (Q < 1 && Q < r0 ){
	    	xi = X;/*��R<min(1,r0)ʱ�ƶ�һ������xi����*/
		    T ++;
		}
		
		Integrate +=  pow((xi - alpha * beta ), 2.0);/*xn+1��xn+N���ڳ���������N����*/
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
    }
	
	delta =  ((double)Integrate/N - alpha * pow(beta, 2.0))/(alpha * pow(beta, 2.0));
	
	printf("I = %f\ndelta = %f\neta = %f\n", (double)Integrate/N, delta, (double)T/N ) ;
	
	return 0;
}
int main(){
	int seed;/*seed������ֵ*/
	int h;/*�������*/ 
	double gamma;/*M-H�����Ĳ���*/ 
	
	printf("Please input seed.");/*��������ֵ*/
	scanf("%d", &I) ;
	
	printf("Please input the step of heating process.");/*�����Ȼ�������Ŀ*/
	scanf("%d", &n) ;
	
	printf("Please input the step of sampling.");/*�������������*/
	scanf("%d", &N) ;
	 
	 
	printf("Please input gamma.");/*����gammaֵ*/
	scanf("%lf", &gamma) ;
	
	h = MH(gamma) ;/*���֣����������Ƿ����*/
	if(h != 0 ) /*����*/
	printf("Error.\n");
}
