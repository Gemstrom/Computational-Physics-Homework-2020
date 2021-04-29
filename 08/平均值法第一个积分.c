#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define f(x) sqrt( x+sqrt(x))

void avr( int a, int m, int r, int q, int seed, int N){  /*������ֺͱ�׼��*/ 
	double x, S=0, T = 0;/*x�������,yָf(x)��S=y0^2+y1^2+����+yN-1^2��T=y0+y1+����+yN-1����S��T�õ���׼��*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
    
    I = seed;/*������ֵ����I0*/
    
    for( n = 0; n < N; n ++) {                   /*��In���xn,Ȼ���� Schrage������In+1*/ 
	
	x = (double)I/m;
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
	
	S += pow( f(2*x), 2.0 ); 
	T += f(2*x);
	}
    
    printf("integer=%f\n sigma = %f\n",(double)T/N*2,sqrt((double)S/N-pow((double)T/N,2.0))*2/sqrt((double)N)) ;/*ͨ�����鷵�ر�׼��*/
    
	return;
}

int main(){
	int a,b,m,r,q,N,seed;/*Schrage������������*/ 
	int n;/*n��ѭ������õ��ı���*/
	
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &N) ;
	
    a=16807;               /*����Schrage������������*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	 
    avr(a,m,r,q,seed,N);
	
	return 0; 
}
