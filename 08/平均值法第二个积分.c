#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define F(x,y,z,u,v)  6-pow((x),2.0)-pow((y),2.0)-pow((z),2.0)-pow((u),2.0)-pow((v),2.0)

void arrange( double x, double*p, int l){/*����l>1�Ķ�̬����,��(p+l-2)��p��ָ����������θ���(p+l-1)����p+1����ָ������ݣ�Ȼ��x����p��ַ*/
	int j;/*ѭ������*/
	
	for( j = l-1; j > 0; j--) {
		* (p + j) = *(p + j - 1);
	}
	
	*p = x ; 
	
	return;
}

void avr( int a, int m, int r, int q, int seed, int N){ /*ƽ��ֵ������ֺͱ�׼��*/ 
    double *p,x, test, S, T;/*p���ڱ������ڵ�l=5��xn��x�������,test=F(x,y,z,u,v),S,T�ֱ�洢��������ƽ���͡���*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�Ij*/
    int l = 5;/*�������ĳ�*/
    
    I = seed;/*������ֵ����I0*/
    
    p = (double*) malloc( l * sizeof(double));/*����ͷָ��Ϊp�Ķ�̬���飬���ڱ������ڵ�5��xn*/ 
    if(p == NULL){/*����*/ 
    	printf("memory allocation error\n");
    	return;
	}
	
	for( n = 0 ; n < l ; n++ ){/*��䶯̬����*/
	   x = (double)I/m;/*��xn*/ 
	
	   I= a * (I%q)- r*((I-(I%q))/q);      /*��Schrage��������In+1��ѭ������ʱI=Il*/ 
		if( I < 0 )
				I = I + m ;
		
		*( p + l - 1 - n )=x;/*��x0��xl-1���θ���p+l-1��pָ����ڴ�*/
	}
    /*����Ϊl�Ķ�̬��������������ֹ��̿�ʼ*/
    
    for( n = l; n < N + l; n ++){             /*��Schrage��������xl��xN+l-1����S��T*/ 
    	x = (double)I/m;
    	
    	test = F(0.9*(*(p+4)),0.8*(*(p+3)),0.9*(*(p+2)),2.0*(*(p+1)),1.3*(*(p)));
		
		T += test;
		S += test*test;
		 
    	arrange( x, p, l);/*���¶�̬����*/
    	
    	I= a * (I%q)- r*((I-(I%q))/q);      /*��Schrage��������In+1*/ 
		if( I < 0 )
		I = I + m ;
	}
    
    free(p);/*�ͷŶ�̬�����ڴ�*/
    
    printf("integer=%f\nsigma=%f\n",1.6848*(double)T/N,1.6848*((double)S/N-pow((double)T/N,2.0))/sqrt((double)N)) ;/*������*/ 
    
    return; 
} 

int main() {
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
