#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
double w;/*��������Ƶ��*/
double E;/*������߸����г���Ӱ���С*/
int seedx;/*����ֵ*/

int OnedimensionRW( int a, int m, int r, int q, int N){   /*���ӵ�һά�������*/ 
	double x;/*x�������*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
    int S;/*�������������߲���*/ 

	S = 0;/*��ʼ��S*/
    I = seedx;/*������ֵ����I0*/
    
    for( n = 0; n < N; n ++) {                   /*��In���xn�����߷���,Ȼ���� Schrage������In+1*/ 
	
	x = (double)I/m;
	
	if(0 < x && x < (1-E*sin(w*n))*0.5)            /*�ж����߷���,����λ�ã�����*/
	S --;
	else if(x > (1-E*sin(w*n))*0.5 && x<1 )
	S++;
	else{
		printf("Error.\n");
		return -1;
	}

	I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
	
	}
    seedx = I;
	return S;
}
int main() {
	int a,b,m,r,q,N,seed,NN;/*Schrage������������*//*N�����Ӳ�����NN������*/ 
	int n;/*n��ѭ������õ��ı�����h�Ǳ����õı���*/
	int x,S,T;/*x��һ��������ߵ�λ������S�Ƕ�����ӵ�x֮�ͣ�T�����ӵ�λ��ƽ��֮��*/ 
	
	printf("Please input seed x.");/*��������ֵ*/
	scanf("%d", &seedx) ;
	
	printf("Please input the step of each particle.");/*���뵥���Ӳ���*/
	scanf("%d", &N) ;
	
	printf("Please input frequency.");/*��������Ƶ��*/
	scanf("%f", &w) ;
	
	printf("Please input the value of e.");/*��������Ƶ��*/
	scanf("%f", &E) ;
	
	printf("Please input the number of particle.");/*����������*/
	scanf("%d", &NN) ;
	
    a=16807;               /*����Schrage������������*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	for(n=0; n < NN; n ++) {
		x = OnedimensionRW(a,m,r,q,N);/*����NN�����ӵ�N��һά�������*/
		S += x;
		T += x*x;
	}
    
    printf("<x>=%f\n<x^2>=%f\n<��x^2>=%f\n",(double)S/NN,(double)T/NN,(double)T/NN-pow((double)S/NN,2.0));
    
	return 0; 
}
