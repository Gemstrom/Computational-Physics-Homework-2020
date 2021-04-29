#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

int RandomNumber( int N,int seed,int a,int m,int r,int q){/*Schrage�������������������������Ϊ�������ֵ*/
    FILE *fp;/*��������*/
    double x,y;/*��x,y�������������*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
    double X,Y;/*�������ֵ*/
    
    fp = fopen("sampling.txt","a+") ;
    fprintf(fp,"seed=%d\nx\n",seed);/*��ͷ*/
    
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
		
		X = -5 + 10*x;/*���ɶ�Ӧ��(X,Y)*/ 
		Y = (double) 3/310 + (double) 54 * y / 155;
		 
		if( Y <= ((double)3/310 * ( pow(x,(double)2) + 2 *x + 2)) )
		fprintf(fp,"%f\n",X) ;       /*�����ɵĳ��������Xд���ļ�*/ 
		
	}
    
    fclose(fp);                          /*�ر��ļ�*/ 
    
    return 0; 
} 

int main() {
	int a,b,m,r,q,N,seed;/*Schrage������������*/
	int n,h;/*n��ѭ������õ��ı�����h�Ǳ����õı���*/
	
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &N) ;
	
	a=16807;               /*����Schrage������������*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	h = RandomNumber(N,seed,a,m,r,q);/*����N�������������*/
    if( h != 0 )/*�Զ�����*/
    printf("Failed to create random number.");
    
    return 0; 
}
