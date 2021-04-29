#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

int Marsaglia(int N,int seed,int a,int m,int r,int q){/*Schrage����������������������������ͱ任����Ϊ��ͶӰ������ֵ*/
    FILE *fp;/*��������*/
    double X,Y,x,y;/*X,Y��(0,1)�Ͼ��ȷֲ��������(x,y)�����ͶӰ����*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
    
    fp = fopen("MarsagliaSampling.txt","a+") ;
    fprintf(fp,"seed=%d\nx y\n",seed);/*��ͷ*/
    
    I = seed; /*������ֵ����I0*/
    
    for(n=0;n<N;n++) {                      /*�� Schrage������I��Ȼ��õ�x,y*/ 
		
		if(n == 0) 
		X = (double)I/m;                    /*����xn*/ 
		else
		X = Y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
		
		Y = (double)I/m;                   /*����x(n+1)=yn*/
		
		if( pow((2*X-1),(double)2) + pow((2*Y-1),(double)2) <= 1 ){/*��ѡ���ж�*/
			x = 2 * ( 2 * X - 1 ) * sqrt( 1- pow((2*X-1),(double)2) - pow((2*Y-1),(double)2) );/*����*/ 
			y = 2 * ( 2 * Y - 1 ) * sqrt( 1- pow((2*X-1),(double)2) - pow((2*Y-1),(double)2) );
			fprintf(fp,"%f %f\n",x,y) ;       /*д���ļ�*/ 
		} 				
		
	}
    
    fclose(fp);                          /*�ر��ļ�*/ 
    
    return 0; 
} 

int main() {
	int a,m,r,q,N,seed;/*Schrage������������*/
	int n,h;/*n��ѭ������õ��ı�����h�Ǳ����õı���*/
	
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &N) ;
	
    a=16807;               /*����Schrage������������*/
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
    h = Marsaglia(N,seed,a,m,r,q);/*����N�������������*/
    if( h != 0 )/*�Զ�����*/
    printf("Failed to create random number.");
    
	return 0; 
}
