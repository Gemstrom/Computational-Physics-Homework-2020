#include<stdio.h> 
#include<math.h>

double lagrange( double y){/*ͨ������lagrange��x(��)|��=y����ֵ*/
    double ksai[11] = {0,0.12903,0.2,0.23226,0.24516,0.25806,0.29032,0.36129,0.49032,0.69677,1};/*���ڴ�ŷ�������ֵ���Ա�����*/
	int n, i, j;/*ѭ����*/
	double l, S = 0 ;/*l���li(��)��ֵ��S���L10(��)*/ 
		
	for( i = 0; i <11; i ++){
		l = 1; 
		for( j = 0 ; j < 10; j ++ ) {   /*����li(y)��ֵ*/
		    if( j == i )
		    continue;
		    
		    l *=  y - ksai[j] ;
		    l /=  ksai[i] - ksai[j] ;
		    
		} 
		
	    S += l * ( i - 5 ); /*��li��y)��Ӧϵ��xi= i-5*/
	
    }
    
    return S;
}

int main(){
	double x, y;/*y��(0,1)�Ͼ��ȷֲ������x�ǳ���*/
	int a,m,r,q,N,seed;/*Schrage������������*/
	int I;/*��������ɵ�In*/
	FILE* fp;/*�洢���������*/ 
    int n;/*ѭ������*/ 
	double test;/*��(L(x)),��x�Աȿ��Եõ���ֵ��׼ȷ��*/ 
	
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &N) ;
	
	a=16807;               /*����Schrage������������*/
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	I = seed; 
	
	fp = fopen("sample2.txt","a+") ;
    fprintf(fp,"seed=%d\n�� x ��(x)\n",seed);/*��ͷ*/
	
	for( n = 0; n < N; n ++) {  /*��In���yn,����xnд���ļ�Ȼ���� Schrage������In+1*/ 
	
	y = (double)I/m;
	
	x = lagrange( y );
	
	test =(double) ( pow(x,3) +3*pow(x,2) +6 * x +80 )/310;
	
	fprintf(fp,"%f %f %f\n", y, x, test) ; 
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
	
	}
	
	fclose(fp);                          /*�ر��ļ�*/ 
    
    return 0; 
}
