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

int MH(double gamma, FILE *fp) {
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
		/*printf("R=%f\tQ=%f\tr0=%f\tx'=%f\tx%d=%f\tIntegrate=%f\n",R,Q,r0,X,i+n,xi,Integrate);*/
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
    }
	
	delta =  ((double)Integrate/N - alpha * pow(beta, 2.0))/(alpha * pow(beta, 2.0));
	
	fprintf(fp, "%f %f %f %f\n", gamma, (double)Integrate/N, delta, (double)T/N ) ;
	
	return 0;
}
int main(){
	int seed;/*seed������ֵ*/
	int i,h;/*ѭ���������������*/ 
	double gamma;/*M-H�����Ĳ���*/ 
	double max, min, s;/*����gamma�ķ�Χ������*/
	FILE *fp;/*�洢����*/ 
	 
	printf("Please input seed.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the step of heating process.");/*�����Ȼ�������Ŀ*/
	scanf("%d", &n) ;
	
	printf("Please input the step of sampling.");/*�������������*/
	scanf("%d", &N) ;
	 
	printf("Please input gamma max.");/*����gammaֵ*/
	scanf("%lf", &max);
	printf("Please input gamma min.");
	scanf("%lf", &min);
	
	fp = fopen("Metropolis-Hasting Sampling.txt","a+") ;
    fprintf(fp, "gamma I delta eta\n");/*��ͷ*/
	
	s = (double) ( max - min ) / 100;/*100�ȷ�����(min,max),���㲽��*/
	
	for( i = 0; i <= 100; i++){
	  I = seed;
	  gamma = min + i * s;/*����gammaֵ*/ 
	  
	  h = MH(gamma,fp) ;/*���֣����������Ƿ����*/
	  if(h != 0 ) /*����*/
	  printf("Error.\n");
	 
	}
	
	fclose(fp) ;
}
