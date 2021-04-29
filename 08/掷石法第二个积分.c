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

void stone( int a, int m, int r, int q, int seed, int N){  
    double *p,x, test,X;/*p���ڱ������ڵ�l=6��xn��x�������,test=F(x,y,z,u,v),X��Xp*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�Ij*/
    int l = 6;/*�������ĳ�*/
    int Q = 0;/*�ɹ���������*/
    
    I = seed;/*������ֵ����I0*/
    
    p = (double*) malloc( 6 * sizeof(double));/*����ͷָ��Ϊp�Ķ�̬���飬���ڱ������ڵ�l��xn*/ 
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
    
    
    for( n = l; n < N + l; n ++){             /*��Schrage��������xl��xN+l-1��������ʯ������*/ 
    	x = (double)I/m;
    	
    	X = -1.95 + 7.95 * (*p);
    	test = F(0.9*(*(p+5)),0.8*(*(p+4)),0.9*(*(p+3)),2.0*(*(p+3)),1.3*(*(p+1)));
		
		if(test > X && X > 0 )
		{  Q++;
		  
		}
		
    	else if(test < X && X< 0)
    	{   Q--;
         
		}
		 
    	arrange( x, p, l);/*���¶�̬����*/
    	
    	I= a * (I%q)- r*((I-(I%q))/q);      /*��Schrage��������In+1*/ 
		if( I < 0 )
		I = I + m ;
	}
    
    free(p);/*�ͷŶ�̬�����ڴ�*/
    
    printf("%f",13.39416*(double)Q/N) ;/*�������ֵ*/ 
    
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
	
	stone(a,m,r,q,seed,N);
	
	return 0; 
}
