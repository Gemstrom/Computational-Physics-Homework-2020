#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define F(x) sqrt(x+sqrt(x))
int main() {
	double x,y;/*Schrage���������������*/ 
	int a,b,m,r,q,N,seed;/*Schrage������������*/
	int Q;/*���ں����·��ĵ���*/
	int n;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
    
    
	a=16807;               /*����Schrage������������*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &N) ;

    
    I = seed; /*������ֵ����I0*/
    
    for(n=0;n<N;n++) {                      /*�� Schrage������I��Ȼ��õ�x,y*/ 
		
		if(n == 0) 
		x = (double)I/m;                    /*����xn*/ 
		else
		x = y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
		
		y = (double)I/m;                   /*����x(n+1)=yn*/
	
	
		if(F(2.0)*y <= F(2*x))
		Q++;
		
	}
    
    printf("%f",2*F(2.0)*(double)Q/N);
    
    return 0; 
	
}
