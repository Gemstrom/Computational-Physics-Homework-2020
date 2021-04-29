#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

int RandomNumber( int N,int seed,int a,int m,int r,int q,char *string ){/*Schrage�������������������������Ϊ�������ֵ*/
    FILE *fp;/*��������*/
    double x,y;/*��x,y�������������*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
    
    fp = fopen(string,"a+") ;
    fprintf(fp,"seed=%d\nx y\n",seed);/*��ͷ*/
    
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
		
		fprintf(fp,"%f %f\n",x,y) ;       /*д���ļ�*/ 
		
	}
    
    fclose(fp);                          /*�ر��ļ�*/ 
    
    return 0; 
} 

void kTest( int k, int a, int m, int r, int q, int seed, int N){   /*�Ը�����k��<xk>���Ծ�����*/ 
	double x, S=0, test;/*x�������,S=x0^k+x1^k+����+xN-1^k��test���ڼ���|<x^k>-1/(k+1)|*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
    FILE *fp;/*�������ɵ�k,|<x^k>-1/(k+1)|*/
    
    I = seed;/*������ֵ����I0*/
    
    for( n = 0; n < N; n ++) {                   /*��In���xn,Ȼ���� Schrage������In+1,��xn^k��n=0��N-1���ΪS*/ 
	
	x = (double)I/m;
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
	
	S = S + pow( x, (double)k ); 
	}

    test =  (double)S/N - (double)1/(k+1) ;       /*����|<x^k>-1/(k+1)|*/
	if( test<0 )
	test = - test;
	
	fp=fopen("k-square test.txt","a+") ;     /*�洢Ϊ�ؼ����ļ�*/
	fprintf(fp,"%d %f\n", k, test) ;
	fclose(fp);  
	return;
}

int main() {
	int a,b,m,r,q,N,seed;/*Schrage������������*/
	int k[5];/*<x^k>����֧������5�������Ե�k*/ 
	char string[] = "data000";/*�����ļ�������*/ 
	int n,h;/*n��ѭ������õ��ı�����h�Ǳ����õı���*/
	
	printf("Please input the number of your test.");/*����ʵ�����*/ 
	scanf("%s",string+4);
	
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &N) ;
	
	printf("Please input 5 k-values you would like to test.\n");/*����5��k*/ 
	for( n=0; n<5; n++) {
	   scanf( "%d" , k+n );
	}
	
    a=16807;               /*����Schrage������������*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
    h = RandomNumber(N,seed,a,m,r,q,string);/*����N�������������*/
    if( h != 0 )/*�Զ�����*/
    printf("Failed to create random number.");
    
    for( n = 0; n < 5; n++ )/*���ν���5��k�ľؼ���*/ 
    kTest(k[n],a,m,r,q,seed,N) ;
	
	return 0; 
}
